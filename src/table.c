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

#include "das-c/table.h"
#include "das-c/common.h"
#include <stdlib.h>

table *init_table(const size_t cols)
{
  table *tab = malloc(sizeof(table));
  check(tab, "failed allocation in init_table()");

  tab->rows = 0;
  tab->cols = cols;
  tab->data = NULL;

  return tab;
}

void add_row(table *tab)
{
  double **data = realloc(tab->data, (tab->rows + 1) * sizeof(double *));
  check(data, "failed reallocation in add_row()");

  tab->data = data;
  tab->data[tab->rows] = malloc(tab->cols * sizeof(double));
  check(data[tab->rows], "failed allocation in add_row()");

  ++tab->rows;
}

void shed_rows(table *tab, const size_t size)
{
  check(size < tab->rows && size > 0, "new size too large in shed_rows()");

  for (size_t ir = size; ir < tab->rows; ++ir)
    free(tab->data[ir]);

  double **data = realloc(tab->data, size * sizeof(double *));
  check(data, "failed reallocation in shed_rows()");

  tab->data = data;
  tab->rows = size;
}

void clear_table(table *tab)
{
  for (size_t ir = 0; ir < tab->rows; ++ir)
    free(tab->data[ir]);
  free(tab->data);
  free(tab);
}
