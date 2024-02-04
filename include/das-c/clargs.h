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

#ifndef DASC_CLARGS_H
#define DASC_CLARGS_H

#include <stdbool.h>
#include <stddef.h>

//! Struct storing command line arguments.
typedef struct clargs
{
  //! Number of fields to be parsed (default: 0 -> all).
  size_t n_fields;

  //! Array of fields to parse (default: NULL -> all).
  size_t *fields;

  //! Percentage (1-100) of rows to skip (default: 0).
  size_t skip;

  //! Number of threads for the parsing process (default: 1).
  size_t n_threads;

  //! Prints additional information (default: false).
  bool verbose;

  //! Datafile to access.
  char *filename;
} clargs;

//! Initializes a `clargs` object from command-line arguments.
/*!
 * Cleanup is performed on failure.
 *
 * @param args Pointer to the empty memory region to init.
 * @param argc Number of command-line arguments (from main).
 * @param argv Command-line argument string list (from main).
 *
 * @return Status code:
 *   - 0 on success
 *   - 1 on invalid field value
 *   - 2 on invalid skip value
 *   - 3 on invalid option or value
 *   - 4 on missing or multiple filename
 */
int init_clargs(clargs *args, int argc, char *argv[]);

//! Frees dynamic memory associated to a `file_info` object.
/*!
 * Undefined behavior if called on a `clargs` with missing or failed init.
 *
 * @param args The `clargs` to cleanup.
 */
void deinit_clargs(clargs *args);

#endif
