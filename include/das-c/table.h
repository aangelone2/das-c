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

#include "das-c/mask.h"
#include "das-c/vector.h"
#include <stdio.h>

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
 * Exits on allocation failure.
 *
 * @param tab Pointer to the memory region to init.
 * @param size Desired number of columns.
 */
void init_table(table *tab, const size_t size);

//! Fills an initialized empty `table` with the content of a file.
/*!
 * Exits if table size is incompatible with passed mask.
 *
 * @param tab Pointer to the `table` to fill.
 * @param file File handle pointing to the file to parse.
 * @param msk `mask` object, filtering fields to access.
 *
 * @return Status code:
 * - 0 on success
 * - 1 if too many fields found in line (compared to `msk`)
 * - 2 if invalid fields found in line
 * - 3 if too few fields found in line (compared to `msk`)
 */
int parse(table *tab, FILE *file, const mask *msk);

//! Frees dynamic memory associated to a `table` object.
/*!
 * @param tab The `table` to cleanup.
 */
void deinit_table(table *tab);

#endif
