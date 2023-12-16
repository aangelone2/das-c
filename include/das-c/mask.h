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

#ifndef DASC_MASK_H
#define DASC_MASK_H

#include <stdbool.h>
#include <stdlib.h>

//! Struct for size-aware `bool` array.
typedef struct mask
{
  //! Number of fields in the mask.
  size_t l;
  //! Number of `true` fields in the mask.
  size_t n;
  //! Mask array, true (false) to parse (ignore) field of each index.
  bool *bits;
} mask;

//! Initializes mask with specified values.
/*!
 * @param msk Pointer to the empty memory region to init. Failure on `NULL`.
 * @param fields Contains the fields which should be set as active.
 * @param nfields The number of fields to set as active.
 * @param size The overall size of the mask to build.
 *
 * @return 0 on success, 1 on `NULL` input, 2 on member allocation failure.
 */
int init_mask(
    mask *msk, const size_t *fields, const size_t nfields, const size_t size
);

//! Frees dynamic memory associated to a `mask` object.
/*!
 * @param msk The `mask` to cleanup.
 */
void deinit_mask(mask *msk);

#endif
