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

#ifndef DASC_FILE_INFO_H
#define DASC_FILE_INFO_H

#include <stdbool.h>
#include <stdio.h>

#define DASC_MAX_LINE_LENGTH 65536

//! Struct containing information about datafile.
typedef struct file_info
{
  //! File stream to read from.
  FILE *file;
  //! Number of columns.
  size_t cols;
  //! Number of rows, set to `0` on construction.
  size_t rows;
  //! Number of valid data rows, set to `0` on construction.
  size_t data_rows;
} file_info;

//! Initializes a `file_info` with the specified values.
/*!
 * On allocation failure, `file` will be closed and set to `NULL`.
 *
 * @param info Pointer to the empty memory region to init. Failure on `NULL`.
 * @param filename The file to characterize.
 *
 * @return Status code:
 *   - 0 on success
 *   - 1 on `NULL` input
 *   - 2 on file opening failure
 *   - 3 on empty file
 *   - 4 on invalid first row in file
 */
int init_file_info(file_info *info, const char *filename);

//! Frees dynamic memory associated to a `file_info` object.
/*!
 * Can be called (no-op) if initialization fails.
 *
 * Closes the file pointer and sets it to `NULL`.
 *
 * Undefined behavior if called on non-initialized `file_info`.
 *
 * @param tab The `file_info` to cleanup.
 */
void deinit_file_info(file_info *info);

#endif
