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

#include "das-c/parse_info.h"

//! Struct for a dataset.
typedef struct
{
  //! Number of rows (outer index).
  size_t rows;
  //! Number of columns (inner index).
  size_t cols;

  //! 2D data pointer.
  double **data;
} table;

//! Fills an uninitialized `table` with the content of a file.
/*!
 * Exits if file cannot be opened.
 *
 * In case of multiple errors in the file, the error determining the return
 * value is 1) the first in single-threaded execution, 2) undefined in
 * multithreaded execution.
 *
 * Exits on allocation or thread creation error.
 *
 * @param tab Pointer to the `table` to fill.
 * @param info Parsing info struct.
 *
 * @return 0 on success, row where error occurred (indexed from 1) on failure.
 */
size_t parse(table *tab, const parse_info *info);

//! Removes rows from the end of a `table`.
/*!
 * Exits on invalid parameters or reallocation failure.
 *
 * @param tab The `table` object to contract.
 * @param size The new number of rows the `table` should have.
 */
void shed_rows(table *tab, const size_t size);

//! Frees memory associated to a `table` object.
/*!
 * @param tab The `table` to clear.
 */
void deinit_table(table *tab);

#endif
