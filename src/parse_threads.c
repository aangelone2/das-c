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

#include "das-c/common.h"
#include "das-c/parse.h"
#include <threads.h>

// Throwaway struct to hold `parse_chunk()` arguments.
typedef struct
{
  table *tab;
  const parse_info *info;
  size_t idx_thread;
  size_t invalid_row;
} parse_chunk_args;

// Casts input pointer as `parse_chunk_args *`, then parses its `idx_thread`-th
// chunk form the file `info` refers to, placing the parsed arrays in `tab`.
// On error, sets `invalid_row` to the first invalid row (indexed from 1).
//
// Returns EXIT_SUCCESS on success, EXIT_FAILURE otherwise (cannot directly
// return row number due to `int` <-> `size_t` casting).
int parse_chunk(void *args)
{
  parse_chunk_args *a = (parse_chunk_args *)(args);
  a->invalid_row = 0;

  int retval = EXIT_SUCCESS;

  FILE *file = fopen(a->info->filename, "r");
  fseek(file, a->info->pos[a->idx_thread], 0);

  // Calculation of starting index
  size_t start = 0;
  for (size_t it = 0; it < a->idx_thread; ++it)
    start += a->info->chunks[it];

  char line[DASC_MAX_LINE_LENGTH];

  size_t ir = 0;
  do
  {
    const size_t row = start + ir;

    fgets(line, DASC_MAX_LINE_LENGTH, file);
    if (is_comment(line))
      continue;

    if (parse_line(a->tab->data[row], line, a->info->msk) == EXIT_FAILURE)
    {
      a->invalid_row = row + 1;
      retval = EXIT_FAILURE;
      break;
    }

    ++ir;
  } while (ir < a->info->chunks[a->idx_thread]);

  fclose(file);
  return retval;
}

size_t parse_threads(table *tab, const parse_info *info)
{
  init_table(tab, info->rows, info->msk->n_active);

  size_t retval = 0;

  thrd_t *threads = malloc(info->n_threads * sizeof(thrd_t));
  parse_chunk_args *args = malloc(info->n_threads * sizeof(parse_chunk_args));
  int *res = malloc(info->n_threads * sizeof(int));

  for (size_t it = 0; it < info->n_threads; ++it)
  {
    args[it].tab = tab;
    args[it].info = info;
    args[it].idx_thread = it;

    const int r = thrd_create(
        &threads[it], (thrd_start_t)(parse_chunk), (void *)(&args[it])
    );
    check(r == thrd_success, "thread creation failure in parse()");
  }

  // Return values can be freely ignored, invalid_row will hold the info
  for (size_t it = 0; it < info->n_threads; ++it)
    thrd_join(threads[it], NULL);

  for (size_t it = 0; it < info->n_threads; ++it)
  {
    if (args[it].invalid_row)
    {
      retval = args[it].invalid_row;
      break;
    }
  }

  free(res);
  free(args);
  free(threads);
  return retval;
}
