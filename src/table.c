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

table *init_table(const size_t size)
{
  table *tab = malloc(sizeof(table));
  check(tab, "failed allocation in init_table()");

  tab->size = size;
  tab->columns = malloc(size * sizeof(vector *));
  check(tab->columns, "failed allocation in init_table()");

  // Default values, to prevent problems in case of partial deallocation
  for (size_t ic = 0; ic < size; ++ic)
    tab->columns[ic] = NULL;

  for (size_t ic = 0; ic < size; ++ic)
    tab->columns[ic] = init_vector();

  return tab;
}

void clear_table(table *tab)
{
  for (size_t ic = 0; ic < tab->size; ++ic)
    clear_vector(tab->columns[ic]);
  free(tab->columns);
  free(tab);
}
