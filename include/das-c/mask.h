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
#include <stddef.h>

//! Struct for mask to select which fields to parse.
typedef struct
{
  //! Number of fields in the mask.
  size_t size;

  //! Number of `true` fields in the mask.
  size_t n_active;

  //! Mask array, true (false) to parse (ignore) field of each index.
  bool *bits;
} mask;

//! Initializes `mask` of specified size.
/*!
 * All fields will be set as `false` by default.
 *
 * Exits on allocation failure.
 *
 * @param size The overall size of the mask to build.
 *
 * @return Pointer to the allocated `mask`.
 */
mask *alloc_mask(const size_t size);

//! Set a field as "active" in a mask.
/*!
 * `n_active` is increased, unless the field is already set.
 *
 * Exits if field outside of size mask.
 *
 * @param msk Pointer to the mask to modify.
 * @param field The index of the field to set as "active".
 */
void set_field(mask *msk, const size_t field);

//! Set all fields as "active" in a mask.
/*!
 * @param msk Mask to modify.
 */
void set_all(mask *msk);

//! Frees memory associated to a `mask` object.
/*!
 * @param msk The `mask` to clear.
 */
void free_mask(mask *msk);

#endif
