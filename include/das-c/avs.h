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

#include "das-c/clargs.h"
#include <stddef.h>

//! Struct holding the result of `avs` on a single column.
typedef struct avs_results
{
  //! Total number of rows.
  size_t rows;

  //! Number of rows kept for analysis.
  size_t kept;

  //! Number of analyzed columns.
  size_t cols;

  //! Column indices (in the file).
  size_t *fields;

  //! Column averages.
  double *ave;

  //! Column SEMs.
  double *sem;
} avs_results;

//! Performs simple averaging on a file based on the passed CL arguments.
/*!
 * Fields will be passed and parsed as 0-based.
 *
 * @param res The `avs_results` object to initialize.
 * @param args The CL arguments specifying the protocol.
 *
 * @return Status code:
 *   - 0 on success
 *   - 1 on `NULL` input
 *   - 2 on internal allocation failures
 */
int avs(avs_results *res, const clargs *args);

//! Frees dynamic memory associated to an `avs_results` object.
/*!
 * Undefined behavior if the `avs_results` has not been init-ed via `avs()`.
 *
 * @param res The `avs_results` to cleanup.
 */
void deinit_avs_results(avs_results *res);

#endif
