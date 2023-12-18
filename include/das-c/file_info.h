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

#include "das-c/mask.h"
#include <stdbool.h>
#include <stdio.h>

#define DASC_MAX_LINE_LENGTH 65536
#define DASC_SEPARATOR " "

//! Checks if a string is commented.
/*!
 * @param row The string to check.
 *
 * @return Whether or not the string is commented.
 */
inline bool is_comment(const char *row) { return row[0] == '#'; }

//! Counts the number of fields separated by DASC_SEPARATOR.
/*!
 * @param row The string to count the fields of.
 *
 * @return The number of fields.
 */
size_t count_fields(char *row);

//! Struct containing information about datafile.
typedef struct file_info
{
  //! File stream to read from.
  FILE *file;
  //! Mask for field parsing.
  mask msk;
  //! Number of rows, set to `0` on construction.
  size_t rows;
  //! Number of valid data rows, set to `0` on construction.
  size_t data_rows;
} file_info;

//! Initializes a `file_info` with the specified values.
/*!
 * @param info Pointer to the empty memory region to init. Failure on `NULL`.
 * @param filename The file to characterize.
 * @param fields The fields to parse.
 * @param nfields The number of fields to parse.
 *
 * @return 0 on success, 1 on `NULL` input, 2 on member allocation failure.
 */
int init_file_info(
    file_info *info,
    const char *filename,
    const size_t *fields,
    const size_t nfields
);

//! Frees dynamic memory associated to a `file_info` object.
/*!
 * @param tab The `file_info` to cleanup.
 */
void deinit_file_info(file_info *info);

#endif
