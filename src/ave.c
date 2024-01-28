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

#include "das-c/ave.h"
#include "das-c/common.h"
#include "das-c/mask.h"
#include "das-c/statistics.h"
#include "das-c/table.h"
#include <stdlib.h>

#define MIN_BINS 64
#define MAX_BINS 1024
#define SIZES 5

// Allocates 2d vector, no cleanup on failure.
// Returns the allocated 2d array, `NULL` on failure.
double **alloc_2d(const size_t n1, const size_t n2)
{
  double **buffer = malloc(n1 * sizeof(double *));
  if (!buffer)
    return NULL;

  for (size_t is = 0; is < SIZES; ++is)
  {
    buffer[is] = malloc(n2 * sizeof(double));
    if (buffer[is])
      return NULL;
  }

  return buffer;
}

// Frees 2d vector.
void free_2d(double **arr, const size_t n1)
{
  for (size_t i = 0; i < n1; ++i)
    free(arr[i]);
  free(arr);
}

ave_results *ave(const clargs *args)
{
  ave_results *res = malloc(sizeof(ave_results));
  check(res, "allocation failure in ave()");

  FILE *file = fopen(args->filename, "r");
  check(file, "unreachable file in ave()");

  const size_t cols = count_fields_file(file);
  check(cols, "field count error in ave()");

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
  check(!parse(tab, file, msk), "parsing error in ave()");

  res->cols = tab->size;

  res->fields = malloc(res->cols * sizeof(size_t));
  check(res->fields, "allocation failure in ave()");

  res->nbins = malloc(SIZES * sizeof(size_t));
  check(res->nbins, "allocation failure in ave()");

  res->ave = alloc_2d(SIZES, res->cols);
  check(res->ave, "allocation failure in ave()");

  res->sem = alloc_2d(SIZES, res->cols);
  check(res->sem, "allocation failure in ave()");

  // All columns will be the same size
  res->rows = tab->columns[0]->size;

  const double perc = (double)(args->skip) / 100.0;
  size_t skip = (size_t)(perc * (double)(res->rows));

  size_t nbins = MAX_BINS;
  // Keeps into account additional skipping in rebin()
  res->kept = ((res->rows - skip) / nbins) * nbins;

  for (size_t is = 0; is < SIZES; ++is)
  {
    const size_t skip_s = (is ? 0 : skip);

    // All columns will have the same bin size
    for (size_t ic = 0; ic < tab->size; ++ic)
    {
      // Only the last write is used
      rebin(tab->columns[ic], skip_s, nbins);
      res->nbins[is] = nbins;
      res->ave[is][ic] = average(tab->columns[ic], 0);
      res->sem[is][ic] = sem(tab->columns[ic], 0, res->ave[is][ic]);
    }

    nbins /= 2;
  }

  clear_table(tab);
  clear_mask(msk);
  fclose(file);

  return res;
}

void clear_ave_results(ave_results *res)
{
  free(res->fields);
  free(res->nbins);
  free_2d(res->ave, SIZES);
  free_2d(res->sem, SIZES);
  free(res);
}
