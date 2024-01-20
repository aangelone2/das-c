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

//! Counts the number of fields separated by DASC_SEPARATOR.
/*!
 * @param row The string to count the fields of.
 *
 * @return The number of fields.
 */
size_t count_fields(char *row);

//! Parses a comma-separated list of size_t in an array.
/*!
 * Missing values will be silently skipped ("1,,3" -> {1,3}).
 *
 * @param buffer The string to parse.
 * @param array Inout parameter, the array to fill.
 * @param size Inout parameter, the size of the parsed array.
 *
 * @return Status code:
 *   - 0 on success
 *   - 1 on reallocation failure
 *   - 2 for invalid value
 */
int parse_sizet_array(char *buffer, size_t **array, size_t *size);

#endif
