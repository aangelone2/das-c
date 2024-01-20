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

#ifndef DASC_DRIVERS_H
#define DASC_DRIVERS_H

#include <stddef.h>

//! Struct holding the result of `avs` on a single column.
typedef struct avs_results
{
  //! Number of analyzed columns.
  size_t size;

  //! The index of the analyzed field in the file.
  size_t *fields;
  //! The average of the column.
  double *ave;
  //! The SEM of the column.
  double *sem;
} avs_results;

//! Performs simple averaging on a file based on the passed CL arguments.
/*!
 * @param res The `avs_results` object to initialize.
 * @param argc The number of CL arguments passed to `main()`.
 * @param argv The CL arguments passed to `main()`.
 *
 * @return Status code:
 *   - 0 on success
 *   - 1 on `NULL` input
 *   - 2 for other failures
 */
int avs(avs_results *res, int argc, char *argv[]);

#endif
