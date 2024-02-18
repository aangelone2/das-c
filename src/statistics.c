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

#include "das-c/statistics.h"
#include "das-c/common.h"
#include <math.h>

double *average(const table *tab, const size_t skip)
{
  ensure(skip < tab->rows, "skip too large in average()");

  double *res = calloc(tab->cols, sizeof(double));
  ensure(res, "failed allocation in average()");

  for (size_t ir = skip; ir < tab->rows; ++ir)
    for (size_t ic = 0; ic < tab->cols; ++ic)
      res[ic] += tab->data[ir][ic];

  const double size = (double)(tab->rows - skip);
  for (size_t ic = 0; ic < tab->cols; ++ic)
    res[ic] /= size;

  return res;
}

double *sem(const table *tab, const size_t skip, const double *average)
{
  ensure(skip < tab->rows, "skip too large in sem()");

  double *res = calloc(tab->cols, sizeof(double));
  ensure(res, "failed allocation in average()");

  for (size_t ir = skip; ir < tab->rows; ++ir)
  {
    for (size_t ic = 0; ic < tab->cols; ++ic)
    {
      const double deviation = average[ic] - tab->data[ir][ic];
      res[ic] += deviation * deviation;
    }
  }

  const double size = (double)(tab->rows - skip);
  for (size_t ic = 0; ic < tab->cols; ++ic)
    res[ic] = sqrt(res[ic] / (size * (size - 1.0)));

  return res;
}

void rebin(table *tab, const size_t skip, const size_t nbins)
{
  ensure(skip < tab->rows, "skip too large in rebin()");

  const size_t keep = tab->rows - skip;
  ensure(nbins <= keep, "nbins too large in rebin()");

  if (nbins == keep)
    return;

  const size_t bsize = keep / nbins;
  const size_t skip2 = skip + (keep % nbins);

  for (size_t ib = 0; ib < nbins; ++ib)
  {
    double *buffer = calloc(tab->cols, sizeof(double));

    // Beginning and end of current bin, considering skipped rows
    const size_t begin = skip2 + (ib * bsize);
    const size_t end = skip2 + ((ib + 1) * bsize);

    for (size_t ir = begin; ir < end; ++ir)
      for (size_t ic = 0; ic < tab->cols; ++ic)
        buffer[ic] += tab->data[ir][ic];

    // Bin number `ib` will never contain components with index `i` < `ib`
    // (not possible if binsize is at least 1).
    for (size_t ic = 0; ic < tab->cols; ++ic)
      tab->data[ib][ic] = buffer[ic] / (double)(bsize);

    free(buffer);
  }

  shed_rows(tab, nbins);
}
