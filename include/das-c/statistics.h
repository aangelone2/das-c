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
 * @file statistics.h
 *
 * Statistical and data-related functions to be called on `table` objects.
 */
#ifndef DASC_STATISTICS_H
#define DASC_STATISTICS_H

#include "das-c/table.h"

//! Computes the average of the columns of the passed `table`.
/*!
 * Exits if `skip` is too large.
 *
 * @param tab Data `table`.
 * @param skip Number of rows to skip from the beginning.
 *
 * @return The computed averages.
 */
double *average(const table *tab, const size_t skip);

//! Computes the SEM of the columns of the passed `table`.
/*!
 * Pre-calculation of the average allows to use a two-pass algorithm, which
 * ensures high accuracy.
 *
 * Exits if `skip` is too large.
 *
 * @param tab Data `vector`.
 * @param skip Number of rows to skip from the beginning.
 * @param average The pre-computed average of the array.
 *
 * @return The computed SEMs.
 */
double *sem(const table *tab, const size_t skip, const double *average);

//! Rebins the passed `table`.
/*!
 * Bin averages are written in the first rows, without overlap with previous
 * content. The `table` is then resized to only contain bin averages.
 *
 * Exits if `skip` or `nbins` is too large.
 *
 * No-op if `nbins` is equal to the current size.
 *
 * @param tab Data `table`.
 * @param skip Number of rows to skip from the beginning.
 * @param nbins The number of desired bins.
 */
void rebin(table *tab, const size_t skip, const size_t nbins);

#endif
