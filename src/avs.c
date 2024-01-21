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
#include "das-c/drivers.h"
#include "das-c/file_info.h"
#include "das-c/mask.h"
#include "das-c/statistics.h"
#include "das-c/table.h"
#include <stdlib.h>

int avs(avs_results *res, int argc, char *argv[])
{
  // NULL input
  if (!res)
    return 1;

  clargs args;
  if (init_clargs(&args, argc, argv))
    return 2;

  file_info info;
  if (init_file_info(&info, args.filename))
    return 2;

  mask msk;
  if (init_mask(&msk, info.cols))
    return 2;
  for (size_t f_idx = 0; f_idx < args.n_fields; ++f_idx)
    set_field(&msk, args.fields[f_idx]);

  table tab;
  if (init_table_parse(&tab, &info, &msk))
    return 2;

  res->size = tab.size;

  res->fields = malloc(res->size * sizeof(size_t));
  if (!res->fields)
    return 2;

  res->ave = malloc(res->size * sizeof(double));
  if (!res->ave)
  {
    free(res->fields);
    return 2;
  }

  res->sem = malloc(res->size * sizeof(double));
  if (!res->sem)
  {
    free(res->fields);
    free(res->ave);
    return 2;
  }

  // Computing average and SEM of every column
  for (size_t ic = 0; ic < tab.size; ++ic)
  {
    const size_t rows = tab.columns[ic].size;
    const double perc = (double)(args.skip) / 100.0;
    const size_t skip = (size_t)(perc * (double)(rows));

    res->fields[ic] = args.fields[ic];
    res->ave[ic] = average(&tab.columns[ic], skip);
    res->sem[ic] = sem(&tab.columns[ic], skip, res->ave[ic]);
  }

  deinit_table(&tab);
  deinit_mask(&msk);
  deinit_file_info(&info);
  deinit_clargs(&args);

  return 0;
}
