/**
 * Copyright (c) 2013-2014 Tomas Dzetkulic
 * Copyright (c) 2013-2014 Pavol Rusnak
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __PBKDF2_H__
#define __PBKDF2_H__

#include <stdint.h>

# ifdef __cplusplus
extern "C" {
# endif
// salt needs to have 4 extra bytes available beyond saltlen
void pbkdf2_hmac_sha256(const uint8_t *pass, int passlen, uint8_t *salt, int saltlen, uint32_t iterations, uint8_t *key, int keylen, void (*progress_callback)(uint32_t current, uint32_t total));
// salt needs to have 4 extra bytes available beyond saltlen
void pbkdf2_hmac_sha512(const uint8_t *pass, int passlen, uint8_t *salt, int saltlen, uint32_t iterations, uint8_t *key, int keylen, void (*progress_callback)(uint32_t current, uint32_t total));

# ifdef __cplusplus
}
# endif
#endif
