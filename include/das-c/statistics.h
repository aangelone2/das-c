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

#ifndef DASC_STATISTICS_H
#define DASC_STATISTICS_H

#include "das-c/vector.h"
#include <stdlib.h>

//! Computes the average of the passed `vector`.
/*!
 * @param vec Data `vector`.
 * @param skip Number of rows to skip from the beginning.
 *
 * @return The computed average, 0.0 if `skip >= vec.size`.
 */
double average(const vector *vec, const size_t skip);

//! Computes the SEM of the passed `vector`.
/*!
 * Pre-calculation of the average allows to use a two-pass algorithm, which
 * ensures high accuracy.
 *
 * @param vec Data `vector`.
 * @param skip Number of rows to skip from the beginning.
 * @param average The pre-computed average of the array.
 *
 * @return The computed SEM, 0.0 if `skip >= vec.size`.
 */
double sem(const vector *vec, const size_t skip, const double average);

//! Rebins the passed array.
/*!
 * Bin averages are written at the beginning of the `vector` without overlap
 * with previous content. The `vector` is then resized to only contain bin
 * averages.
 *
 * Data and size are left unchanged in case of invalid arguments.
 *
 * @param vec Data `vector`.
 * @param skip Number of rows to skip from the beginning.
 * @param nbins The number of desired bins.
 *
 * @return Status code:
 *   - 0 on success
 *   - 1 on failure (invalid arguments, reallocation failure).
 */
int rebin(vector *vec, const size_t skip, const size_t nbins);

#endif
