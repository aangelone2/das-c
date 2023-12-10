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
#include <string.h>

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

table *resize_back(table *tab, const size_t l2)
{
  tab->l2 = l2;
  for (size_t i1 = 0; i1 < tab->l1; ++i1)
  {
    tab->data[i1] = (double *)realloc(tab->data[i1], l2 * sizeof(double));
    if (tab->data[i1] == NULL)
      return NULL;
  }

  return tab;
}

table *discard_front(table *tab, const size_t skip)
{
  const size_t remaining = tab->l2 - skip;

  for (size_t i1 = 0; i1 < tab->l1; ++i1)
  {
    memmove(tab->data[i1] + skip, tab->data[i1], remaining * sizeof(double));

    tab->data[i1] = realloc(tab->data[i1], remaining * sizeof(double));
    if (tab->data[i1] == NULL)
      return NULL;
  }

  tab->l2 = remaining;
  return tab;
}

table *rebin(table *tab, const size_t nbins)
{
  const size_t bsize = tab->l2 / nbins;
  const size_t keep = bsize * nbins;
  tab = discard_front(tab, tab->l2 - keep);

  for (size_t i1 = 0; i1 < tab->l1; ++i1)
  {
    for (size_t ib = 0; ib < nbins; ++ib)
    {
      double buffer = 0.0;
      for (size_t i2 = ib * bsize; i2 < (ib + 1) * bsize; ++i2)
        buffer += tab->data[i1][i2];

      // Bin number `ib` will never contain components with inner index `i2`
      // less than `ib` (not possible if binsize is at least 1).
      tab->data[i1][ib] = buffer;
    }
  }

  tab = resize_back(tab, nbins);
  return tab;
}

void free_table(table *tab)
{
  for (size_t i1 = 0; i1 < tab->l1; ++i1)
    free(tab->data[i1]);
  free(tab->data);
  free(tab);
}
