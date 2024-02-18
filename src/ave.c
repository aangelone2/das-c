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
#include "das-c/parse.h"
#include "das-c/statistics.h"
#include <stdlib.h>

#define MIN_BINS 64
#define MAX_BINS 1024
#define SIZES 5

ave_results *ave(const clargs *args)
{
  ave_results *res = malloc(sizeof(ave_results));
  check(res, "allocation failure in ave()");

  parse_info *info = alloc_parse_info(args);
  table tab;

  int pres;
  if (args->mode == DASC_PARALLEL_MODE_THR)
    pres = parse_threads(&tab, info);
  else // if (args->mode == DASC_PARALLEL_MODE_OMP)
    pres = parse_openmp(&tab, info);
  check(!pres, "parsing error in ave()");

  res->cols = tab.cols;
  res->nsizes = SIZES;

  res->fields = malloc(res->cols * sizeof(size_t));
  check(res->fields, "allocation failure in ave()");

  // Selected VS all fields
  for (size_t ic = 0; ic < res->cols; ++ic)
    res->fields[ic] = (args->fields ? args->fields[ic] : ic);

  res->nbins = malloc(res->nsizes * sizeof(size_t));
  check(res->nbins, "allocation failure in ave()");

  res->bsizes = malloc(res->nsizes * sizeof(size_t));
  check(res->bsizes, "allocation failure in ave()");

  res->ave = malloc(res->nsizes * sizeof(double *));
  check(res->ave, "allocation failure in ave()");

  res->sem = malloc(res->nsizes * sizeof(double *));
  check(res->sem, "allocation failure in ave()");

  // All columns will be the same size
  res->rows = tab.rows;

  const double perc = (double)(args->skip) / 100.0;
  size_t skip = (size_t)(perc * (double)(res->rows));

  size_t nbins = MAX_BINS;
  // Keeps into account additional skipping in rebin()
  size_t bsize = (res->rows - skip) / nbins;
  res->kept = bsize * nbins;

  for (size_t is = 0; is < res->nsizes; ++is)
  {
    // No skip after the first rebinning
    const size_t skip_s = (is ? 0 : skip);

    rebin(&tab, skip_s, nbins);
    res->nbins[is] = nbins;
    res->bsizes[is] = bsize;

    // After the rebinning, nothing needs to ever be skipped
    res->ave[is] = average(&tab, 0);
    res->sem[is] = sem(&tab, 0, res->ave[is]);

    nbins /= 2;
    bsize *= 2;
  }

  deinit_table(&tab);
  free_parse_info(info);
  return res;
}

void clear_ave_results(ave_results *res)
{
  free(res->fields);
  free(res->nbins);
  free(res->bsizes);

  for (size_t is = 0; is < res->nsizes; ++is)
  {
    free(res->ave[is]);
    free(res->sem[is]);
  }
  free(res->ave);
  free(res->sem);

  free(res);
}
