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
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define DASC_MAX_LINE_LENGTH 65536
// Placing '\n' here works like newline trimming.
#define DASC_SEPARATORS " \n"
#define DASC_COMMENT '#'

//! Checks if a string is commented.
/*!
 * @param row The string to check.
 *
 * @return Whether or not the string is commented.
 */
static inline bool is_comment(const char *row)
{
  return row[0] == DASC_COMMENT;
}

//! `assert`-like macro, prints a message and aborts if the condition fails.
/*!
 * @param condition The condition to check.
 * @param msg String to print before terminating.
 */
#define check(condition, msg)                                                 \
  {                                                                           \
    if (!(condition))                                                         \
    {                                                                         \
      fprintf(stderr, "error :: %s\n", msg);                                  \
      exit(EXIT_FAILURE);                                                     \
    }                                                                         \
  }

//! Counts the number of fields separated by DASC_SEPARATOR.
/*!
 * @param row The string to count the fields of.
 *
 * @return The number of fields.
 */
size_t count_fields(char *row);

//! Counts the fields in the first non-comment line in the passed file.
/*!
 * @param file Handle to the file to analyze.
 *
 * @return The number of fields, 0 on error.
 */
size_t count_fields_file(FILE *file);

//! Parses a comma-separated list of size_t in an array.
/*!
 * Missing values will be silently skipped ("1,,3" -> {1,3}).
 * Trailing comma is accepted.
 *
 * Exits on allocation failure.
 * Fails (with cleanup) on invalid value.
 *
 * @param buffer The string to parse.
 * @param size Inout parameter, the size of the parsed array.
 *
 * @return The parsed array on success, `NULL` on failure.
 */
size_t *parse_sizet_array(char *buffer, size_t *size);

#endif
