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

/**
 * @file common.h
 *
 * Common utilities used across the codebase.
 */
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

//! `assert`-like macro, prints a message and aborts if the condition FAILS.
/*!
 * A leading `error ::` and a trailing newline will be automatically added.
 *
 * @param condition The condition to verify.
 * @param ... Printout arguments (same syntax as `printf`).
 */
#define ensure(condition, ...)                                                \
  {                                                                           \
    if (!(condition))                                                         \
    {                                                                         \
      fprintf(stderr, "error :: ");                                           \
      fprintf(stderr, __VA_ARGS__);                                           \
      fprintf(stderr, "\n");                                                  \
      exit(EXIT_FAILURE);                                                     \
    }                                                                         \
  }

//! Counts the number of fields.
/*!
 * @param row The string to count the fields of. Will be overwritten.
 * @param sep String of separator characters.
 *
 * @return The number of fields.
 */
size_t count_fields(char *row, const char *sep);

//! Counts the fields in the first non-comment line in the passed file.
/*!
 * @param file Handle to the file to analyze. Rewound on return.
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
 * @param buffer The string to parse. Will be overwritten.
 * @param size Number of fields in the string.
 *
 * @return The parsed array on success, `NULL` on failure.
 */
size_t *parse_sizet_array(char *buffer, const size_t size);

#endif
