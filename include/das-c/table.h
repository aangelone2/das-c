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

#include "das-c/file_info.h"
#include "das-c/mask.h"
#include "das-c/vector.h"

//! Struct for a set of data vectors.
typedef struct table
{
  //! Number of contained `vector`s.
  size_t size;

  //! `vector` array.
  vector *columns;
} table;

//! Initializes an empty `table`.
/*!
 * Internal `vector`s are left at size 0.
 *
 * @param tab Pointer to the memory region to init. Failure on `NULL`.
 * @param size Desired number of columns.
 *
 * @return 0 on success, 1 on `NULL` input, 2 on member allocation failure.
 */
int init_table_empty(table *tab, const size_t size);

//! Initializes a `table` with the content of a passed file.
/*!
 * `info` will be updated with the number of total and data rows.
 *
 * @param tab Pointer to the memory region to init. Failure on `NULL`.
 * @param info `file_info` object containing information about the file.
 * @param msk `mask` object, filtering fields to access.
 *
 * @return Status code:
 *   - 0 on success
 *   - 1 on `NULL` input
 *   - 2 on allocation failure
 *   - 3 on line with too many fields
 *   - 4 on line with too many active fields
 *   - 5 on line with invalid field
 *   - 6 on line with too few fields
 *   - 7 on line with too few active fields
 */
int init_table_parse(table *tab, file_info *info, const mask *msk);

//! Frees dynamic memory associated to a `table` object.
/*!
 * @param tab The `table` to cleanup.
 */
void deinit_table(table *tab);

#endif
