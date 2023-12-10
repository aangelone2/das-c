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

#ifndef DASC_TABLE_H
#define DASC_TABLE_H

#include <stdlib.h>

//! Struct for resizable 2-dimensional float arrays.
typedef struct table
{
  //! Outer data array size.
  size_t l1;
  //! Inner data array size.
  size_t l2;
  //! Data array.
  double **data;
} table;

//! Allocates a `table` with the specified sizes.
/*!
 * Returns `NULL` if allocation of outer/inner data array fails.
 *
 * Inner arrays are allocated to `NULL` if `l2` is set to `0`, useful for
 * `resize_back()` later.
 *
 * @param l1 Outer array size.
 * @param l2 Inner array size.
 *
 * @return The allocated `table`, `NULL` on failure.
 */
table *alloc_table(const size_t l1, const size_t l2);

//! Change inner size of `table` data array.
/*!
 * Calls `realloc()` on inner data array of passed `table` and updates `l2`,
 * removing/adding components at the end.
 *
 * Returns `NULL` if any reallocations fail.
 *
 * @param tab The `table` object to modify.
 * @param l2 The new inner size.
 *
 * @return The reallocated `table`, `NULL` on failure.
 */
table *resize_back(table *tab, const size_t l2);

//! Discards a specified number of inner-array elements from the front.
/*!
 * Reallocates the inner arrays to the remaining size and updates `tab->l2`.
 *
 * Returns `NULL` if any reallocations fail.
 *
 * @param tab The table to modify.
 * @param skip The number of lines to skip.
 *
 * @return The modified table, `NULL` on failure.
 */
table *discard_front(table *tab, const size_t skip);

//! Replace array components along the inner direction with rebinned ones.
/*!
 * The final component `ib` along the inner axis will contain the bin number
 * `ib`. `l2` is updated to `nbins`.
 *
 * Returns `NULL` if any reallocations fail, or if `nbins > tab->l2`.
 *
 * @param tab The table to rebin.
 * @param nbins The desired number of bins.
 *
 * @return The rebinned table, `NULL` on failure.
 */
table *rebin(table *tab, const size_t nbins);

//! Frees all memory associated to a `table` object.
/*!
 * @param tab The `table` to free.
 */
void free_table(table *tab);

#endif
