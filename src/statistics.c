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
#include <assert.h>
#include <math.h>

double average(const vector *vec, const size_t skip)
{
  assert(skip < vec->size && "skip too large in average()");

  double buffer = 0.0;
  for (size_t i = skip; i < vec->size; ++i)
    buffer += vec->data[i];

  const double size = (double)(vec->size - skip);
  return buffer / size;
}

double sem(const vector *vec, const size_t skip, const double average)
{
  assert(skip < vec->size && "skip too large in sem()");

  double buffer = 0.0;
  for (size_t i = skip; i < vec->size; ++i)
  {
    const double deviation = average - vec->data[i];
    buffer += deviation * deviation;
  }

  const double size = (double)(vec->size - skip);
  return sqrt(buffer / (size * (size - 1.0)));
}

void rebin(vector *vec, const size_t skip, const size_t nbins)
{
  assert(skip < vec->size && "skip too large in rebin()");

  const size_t keep = vec->size - skip;
  assert(nbins <= keep && "nbins too large in rebin()");

  if (nbins == keep)
    return;

  const size_t bsize = keep / nbins;
  const size_t skip2 = skip + (keep % nbins);

  for (size_t ib = 0; ib < nbins; ++ib)
  {
    double buffer = 0.0;

    // Beginning and end of current bin, considering skipped rows
    const size_t begin = skip2 + (ib * bsize);
    const size_t end = skip2 + ((ib + 1) * bsize);

    for (size_t i = begin; i < end; ++i)
      buffer += vec->data[i];

    // Bin number `ib` will never contain components with index `i` < `ib`
    // (not possible if binsize is at least 1).
    vec->data[ib] = buffer / (double)(bsize);
  }

  resize(vec, nbins);
}
