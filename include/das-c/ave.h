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

#ifndef DASC_AVE_H
#define DASC_AVE_H

#include "das-c/clargs.h"
#include <stddef.h>

//! Struct holding the result of `ave`.
typedef struct ave_results
{
  //! Total number of rows.
  size_t rows;

  //! Number of rows kept for analysis.
  size_t kept;

  //! Number of analyzed columns.
  size_t cols;

  //! Number of considered bin sizes.
  size_t nsizes;

  //! Column indices (in the file).
  size_t *fields;

  //! Bin numbers, nbins[i] <-> ave[i][...]
  size_t *nbins;

  //! Bin sizes, bsize[i] <-> ave[i][...]
  size_t *bsizes;

  //! Column averages, 2nd index runs on columns.
  double **ave;

  //! Column SEMs, 2nd index runs on columns.
  double **sem;
} ave_results;

//! Performs bin-based averaging of a file based on the passed CL arguments.
/*!
 * Fields will be passed and parsed as 0-based.
 *
 * Exits on file opening, parsing, and allocation errors.
 *
 * @param args The CL arguments specifying the protocol.
 *
 * @return Pointer to `ave_results` object containing the results.
 */
ave_results *ave(const clargs *args);

//! Frees memory associated to an `ave_results` object.
/*!
 * @param res The `ave_results` to clear.
 */
void clear_ave_results(ave_results *res);

#endif
