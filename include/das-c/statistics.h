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

#include <stdlib.h>

//! Computes the average of the passed array.
/*!
 * @param data Data array.
 * @param size The array size.
 *
 * @return The computed average.
 */
double average(const double *data, const size_t size);

//! Computes the SEM of the passed array.
/*!
 * Pre-calculation of the average allows to use a two-pass algorithm, which
 * ensures high accuracy (the second pass can be amortized by parallelizing).
 *
 * @param data Data array.
 * @param size The array size.
 * @param average The pre-computed average of the array.
 *
 * @return The computed SEM.
 */
double sem(const double *data, const size_t size, const double average);

#endif
