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

#ifndef DASC_COMMON_H
#define DASC_COMMON_H

#include <stdbool.h>
#include <stdlib.h>

#define DASC_SEPARATOR ' '
#define DASC_MAX_LINE_LENGTH 65536

//! Checks if a string is commented.
/*!
 * @param row The string to check.
 *
 * @return Whether or not the string is commented.
 */
inline bool is_comment(const char *row) { return row[0] == '#'; }

//! Counts the number of fields in the passed string.
/*!
 * The string is assumed to be null-terminated (`strlen()` is used).
 *
 * @param row The string to count the fields of.
 * @param sep The character to use as separator.
 *
 * @return The number of fields found in the string.
 */
size_t count_fields(const char *row, const char sep);

#endif
