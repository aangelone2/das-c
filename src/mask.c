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

#include "das-c/mask.h"

mask *build_mask(const size_t *fields, const size_t nfields, const size_t size)
{
  mask *msk = (mask *)malloc(sizeof(mask));
  if (msk == NULL)
    return NULL;

  msk->l = size;
  msk->n = nfields;

  msk->bits = (bool *)malloc(size * sizeof(bool));
  if (msk->bits == NULL)
    return NULL;

  for (size_t f = 0; f < size; ++f)
    msk->bits[f] = false;

  for (size_t f = 0; f < nfields; ++f)
  {
    if (fields[f] > size)
      return NULL;
    msk->bits[fields[f] - 1] = true;
  }

  return msk;
}

void free_mask(mask *msk)
{
  free(msk->bits);
  free(msk);
}
