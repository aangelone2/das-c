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

#ifndef DASC_PARSE_H
#define DASC_PARSE_H

#include "das-c/mask.h"
#include "das-c/parse_info.h"
#include "das-c/table.h"

//! Creates an array from the floating-points fields parsed in a string.
/*!
 * Exits on allocation failure.
 *
 * @param line The string to parse. Will be overwritten.
 * @param msk `mask` object holding parsing information.
 *
 * @return The parsed array on success, `NULL` on failure.
 */
double *parse_line(char *line, const mask *msk);

//! Fills uninitialized `table` with the content of a file using C11 threads.
/*!
 * Exits if file cannot be opened.
 *
 * In case of multiple errors in the file, the error determining the return
 * value is the one at the earliest row in the file.
 *
 * Exits on allocation or thread creation error.
 *
 * @param tab Pointer to the `table` to fill.
 * @param info Parsing info struct.
 *
 * @return 0 on success, row where error occurred (indexed from 1) on failure.
 */
size_t parse_threads(table *tab, const parse_info *info);

#endif
