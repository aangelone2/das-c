/* Copyright (c) 2023 Adriano Angelone
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * This file is part of das-c.
 *
 * This file may be used under the terms of the GNU General Public License
 * version 3.0 as published by the Free Software Foundation and appearing in
 * the file LICENSE included in the packaging of this file. Please review the
 * following information to ensure the GNU General Public License version 3.0
 * requirements will be met:
 * http://www.gnu.org/copyleft/gpl.html.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE. */

#include "das-c/clargs.h"
#include "das-c/common.h"
#include "das-c/mask.h"
#include "das-c/table.h"
#include <stdlib.h>
#include <string.h>

// Counts the number of non-commented rows in the file.
// Resets the file on return.
size_t count_rows(FILE *file)
{
  size_t rows = 0;
  char line[DASC_MAX_LINE_LENGTH];

  while (fgets(line, DASC_MAX_LINE_LENGTH, file))
    if (!is_comment(line))
      ++rows;

  rewind(file);
  return rows;
}

// Returns an array of size_t, each containing the number of rows
// that each thread should parse. Last chunk will contain excess rows.
size_t *get_chunk_sizes(const size_t rows, const size_t nthreads)
{
  size_t *res = malloc(nthreads * sizeof(size_t));

  for (size_t it = 0; it < nthreads; ++it)
    res[it] = rows / nthreads;
  // Excess rows
  res[nthreads - 1] += rows % nthreads;

  return res;
}

// Returns an array of `long int` variables, which can be used as second
// arguments to `fseek(<FILE *>, _, 0)` to move to chunk starting lines.
// The 0th component is always set to 0.
// Resets the file on return.
long int *get_pos(FILE *file, const size_t *chunk_sizes, const size_t nthreads)
{
  long int *pos = malloc(nthreads * sizeof(long int));
  pos[0] = 0;

  char line[DASC_MAX_LINE_LENGTH];

  for (size_t it = 1; it < nthreads; ++it)
  {
    size_t ir = 0;
    do
    {
      // This will consume the newline as well,
      // leaving the file pointer at the beginning of the next line
      fgets(line, DASC_MAX_LINE_LENGTH, file);
      if (is_comment(line))
        continue;

      ++ir;
    } while (ir < chunk_sizes[it - 1]);

    pos[it] = ftell(file);
  }

  rewind(file);
  return pos;
}

// Writes the contents of the fields of `line`, filtered by `msk`,
// to the components of `data`.
// Returns:
// - 0 if successful
// - 1 if too many fields (compared to `msk`)
// - 2 if invalid fields found
// - 3 if too few fields (compared to `msk`)
int parse_line(double *data, char *line, const mask *msk)
{
  size_t field = 0, active_field = 0;

  char *tok = strtok(line, DASC_SEPARATORS);
  while (tok)
  {
    // Too many fields
    if (field >= msk->size)
      return 1;

    if (msk->bits[field])
    {
      char *end;
      const double buffer = strtod(tok, &end);

      // Invalid field found
      if (end == tok)
        return 2;

      data[active_field] = buffer;
      ++active_field;
    }

    tok = strtok(NULL, DASC_SEPARATORS);
    ++field;
  }

  // Too few fields
  if (field != msk->size)
    return 3;

  return 0;
}

// Parses a chunk of size `size` from `file` according to `msk`,
// placing the results in `tab` starting from the component `start`.
int parse_chunk(
    table *tab,
    FILE *file,
    const mask *msk,
    const size_t start,
    const size_t size
)
{
  char line[DASC_MAX_LINE_LENGTH];

  size_t ir = 0;
  do
  {
    fgets(line, DASC_MAX_LINE_LENGTH, file);
    if (is_comment(line))
      continue;

    const int res = parse_line(tab->data[start + ir], line, msk);
    // Failure in parse_line()
    if (res)
      return res;

    ++ir;
  } while (ir < size);

  return 0;
}

int parse(table *tab, const clargs *args)
{
  FILE *file = fopen(args->filename, "r");
  check(file, "unreachable file in parse()");

  const size_t cols = count_fields_file(file);
  check(cols, "field count error in parse()");

  mask *msk = alloc_mask(cols);

  // Selected fields
  if (args->fields)
  {
    for (size_t f_idx = 0; f_idx < args->n_fields; ++f_idx)
      set_field(msk, args->fields[f_idx]);
  }
  // All fields
  else
    set_all(msk);

  const size_t rows = count_rows(file);
  init_table(tab, rows, msk->n_active);

  size_t *chunk_sizes = get_chunk_sizes(rows, args->n_threads);
  long int *pos = get_pos(file, chunk_sizes, args->n_threads);

  size_t start = 0;
  for (size_t it = 0; it < args->n_threads; ++it)
  {
    FILE *file_it = fopen(args->filename, "r");
    fseek(file_it, pos[it], 0);

    const int res = parse_chunk(tab, file_it, msk, start, chunk_sizes[it]);
    if (res)
      return res;

    start += chunk_sizes[it];

    fclose(file_it);
  }

  free(pos);
  free(chunk_sizes);
  free_mask(msk);
  fclose(file);

  return 0;
}
