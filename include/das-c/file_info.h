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

//! Struct containing information about datafile.
typedef struct file_info
{
  //! File stream to read from.
  FILE *file;
  //! Mask for field parsing.
  mask *msk;
  //! Number of rows, set to `0` on construction.
  size_t rows;
  //! Number of valid data rows, set to `0` on construction.
  size_t data_rows;
} file_info;

//! Allocates a `file_info` from the specified filename.
/*!
 * Returns `NULL` if:
 * - Any allocations fail;
 * - File not found;
 * - No fields found in file;
 * - Error encountered in mask creation.
 *
 * @param filename The file to characterize.
 * @param fields The fields to parse.
 * @param nfields The number of fields to parse.
 *
 * @return The allocated `file_info`, `NULL` on failure.
 */
file_info *build_file_info(
    const char *filename, const size_t *fields, const size_t nfields
);

//! Frees all memory associated to a `file_info` object.
/*!
 * @param tab The `file_info` object to free.
 */
void free_file_info(file_info *finfo);

#endif
