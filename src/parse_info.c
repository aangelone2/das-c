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

#include "das-c/parse_info.h"
#include "das-c/common.h"
#include <stdlib.h>

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

// Generates thread load array. First thread will receive excess rows.
size_t *get_chunks(const size_t rows, const size_t n_threads)
{
  size_t *res = malloc(n_threads * sizeof(size_t));
  check(res, "failed allocation in get_chunks()");

  for (size_t it = 0; it < n_threads; ++it)
    res[it] = rows / n_threads;
  // Excess rows
  res[0] += rows % n_threads;

  return res;
}

// Generates thread file position array. Rewinds file on return.
long int *get_pos(FILE *file, const size_t *chunks, const size_t n_threads)
{
  long int *pos = malloc(n_threads * sizeof(long int));
  check(pos, "failed allocation in get_pos()");

  pos[0] = 0;

  char line[DASC_MAX_LINE_LENGTH];

  for (size_t it = 1; it < n_threads; ++it)
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
    } while (ir < chunks[it - 1]);

    pos[it] = ftell(file);
  }

  rewind(file);
  return pos;
}

parse_info *alloc_parse_info(const clargs *args)
{
  parse_info *info = malloc(sizeof(parse_info));
  check(info, "failed allocation in alloc_parse_info()");

  info->filename = args->filename;

  FILE *file = fopen(args->filename, "r");
  check(file, "unreachable file in parse()");

  const size_t cols = count_fields_file(file);
  check(cols, "field count error in parse()");

  info->msk = alloc_mask(cols);

  // Selected fields
  if (args->fields)
  {
    for (size_t f_idx = 0; f_idx < args->n_fields; ++f_idx)
      set_field(info->msk, args->fields[f_idx]);
  }
  // All fields
  else
    set_all(info->msk);

  info->rows = count_rows(file);

  info->mode = args->mode;
  info->n_threads = args->n_threads;
  info->chunks = get_chunks(info->rows, args->n_threads);
  info->pos = get_pos(file, info->chunks, args->n_threads);

  return info;
}

void free_parse_info(parse_info *info)
{
  free_mask(info->msk);
  free(info->chunks);
  free(info->pos);
  free(info);
}
