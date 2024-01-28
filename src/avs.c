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

#include "das-c/avs.h"
#include "das-c/common.h"
#include "das-c/mask.h"
#include "das-c/statistics.h"
#include "das-c/table.h"
#include <stdlib.h>

avs_results *avs(const clargs *args)
{
  avs_results *res = malloc(sizeof(avs_results));
  check(res, "allocation failure in avs()");

  FILE *file = fopen(args->filename, "r");
  check(file, "unreachable file in avs()");

  const size_t cols = count_fields_file(file);
  check(cols, "field count error in avs()");

  mask *msk = init_mask(cols);

  // Selected fields
  if (args->fields)
  {
    for (size_t f_idx = 0; f_idx < args->n_fields; ++f_idx)
      set_field(msk, args->fields[f_idx]);
  }
  // All fields
  else
    set_all(msk);

  table *tab = init_table(msk->n_active);
  check(!parse(tab, file, msk), "parsing error in avs()");

  res->cols = tab->size;

  res->fields = malloc(res->cols * sizeof(size_t));
  check(res->fields, "allocation error in avs()");

  res->ave = malloc(res->cols * sizeof(double));
  check(res->ave, "allocation error in avs()");

  res->sem = malloc(res->cols * sizeof(double));
  check(res->sem, "allocation error in avs()");

  // All columns will be the same size
  res->rows = tab->columns[0]->size;

  const double perc = (double)(args->skip) / 100.0;
  const size_t skip = (size_t)(perc * (double)(res->rows));
  res->kept = res->rows - skip;

  // Computing average and SEM of every column
  for (size_t ic = 0; ic < tab->size; ++ic)
  {
    // Selected VS all fields
    res->fields[ic] = (args->fields ? args->fields[ic] : ic);
    res->ave[ic] = average(tab->columns[ic], skip);
    res->sem[ic] = sem(tab->columns[ic], skip, res->ave[ic]);
  }

  clear_table(tab);
  clear_mask(msk);
  fclose(file);

  return res;
}

void clear_avs_results(avs_results *res)
{
  free(res->fields);
  free(res->ave);
  free(res->sem);
  free(res);
}
