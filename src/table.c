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
  table *buffer = (table *)malloc(sizeof(table));
  if (buffer == NULL)
    return NULL;

  buffer->data = (double **)malloc(l1 * sizeof(double *));
  if (buffer->data == NULL)
    return NULL;

  for (size_t i1 = 0; i1 < l1; ++i1)
  {
    if (l2 != 0)
    {
      buffer->data[i1] = (double *)malloc(l2 * sizeof(double));
      if (buffer->data[i1] == NULL)
        return NULL;
    }
    else
      buffer->data[i1] = NULL;
  }

  return buffer;
}

table *change_l2(table *tab, const size_t l2)
{
  for (size_t i1 = 0; i1 < tab->l1; ++i1)
  {
    tab->data[i1] = (double *)realloc(tab->data[i1], l2);
    if (tab->data[i1] == NULL)
      return NULL;
  }

  tab->l2 = l2;
  return tab;
}

void free_table(table *buffer)
{
  for (size_t i1 = 0; i1 < buffer->l1; ++i1)
    free(buffer->data[i1]);
  free(buffer->data);
  free(buffer);
}
