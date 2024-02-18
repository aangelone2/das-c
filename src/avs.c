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
#include "das-c/parse.h"
#include "das-c/statistics.h"
#include <stdlib.h>

avs_results *avs(const clargs *args)
{
  avs_results *res = malloc(sizeof(avs_results));
  check(res, "allocation failure in avs()");

  parse_info *info = alloc_parse_info(args);
  table tab;

  int pres;
  if (args->mode == DASC_PARALLEL_MODE_THR)
    pres = parse_threads(&tab, info);
  else // if (args->mode == DASC_PARALLEL_MODE_OMP)
    pres = parse_openmp(&tab, info);
  check(!pres, "parsing error in avs()");

  res->cols = tab.cols;

  res->fields = malloc(res->cols * sizeof(size_t));
  check(res->fields, "allocation failure in avs()");

  // Selected VS all fields
  for (size_t ic = 0; ic < res->cols; ++ic)
    res->fields[ic] = (args->fields ? args->fields[ic] : ic);

  // All columns will be the same size
  res->rows = tab.rows;

  const double perc = (double)(args->skip) / 100.0;
  const size_t skip = (size_t)(perc * (double)(res->rows));
  res->kept = res->rows - skip;

  // Assigning statistical results
  res->ave = average(&tab, skip);
  res->sem = sem(&tab, skip, res->ave);

  deinit_table(&tab);
  free_parse_info(info);
  return res;
}

void clear_avs_results(avs_results *res)
{
  free(res->fields);
  free(res->ave);
  free(res->sem);
  free(res);
}
