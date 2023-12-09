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

table *alloc_table(const size_t l1, const size_t l2)
{
  // Main allocation
  table *tab = (table *)malloc(sizeof(table));
  if (tab == NULL)
    return NULL;

  // Outer array
  tab->l1 = l1;
  tab->data = (double **)malloc(l1 * sizeof(double *));
  if (tab->data == NULL)
    return NULL;

  // Inner array
  tab->l2 = l2;
  for (size_t i1 = 0; i1 < l1; ++i1)
  {
    if (l2 != 0)
    {
      tab->data[i1] = (double *)malloc(l2 * sizeof(double));
      if (tab->data[i1] == NULL)
        return NULL;
    }
    else
      tab->data[i1] = NULL;
  }

  return tab;
}

table *change_l2(table *tab, const size_t l2)
{
  tab->l2 = l2;
  for (size_t i1 = 0; i1 < tab->l1; ++i1)
  {
    tab->data[i1] = (double *)realloc(tab->data[i1], l2);
    if (tab->data[i1] == NULL)
      return NULL;
  }

  return tab;
}

void free_table(table *tab)
{
  for (size_t i1 = 0; i1 < tab->l1; ++i1)
    free(tab->data[i1]);
  free(tab->data);
  free(tab);
}
