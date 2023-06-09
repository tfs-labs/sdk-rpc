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

#include <string.h>
#include "pbkdf2.h"
#include "hmac.h"

void pbkdf2_hmac_sha256(const uint8_t *pass, int passlen, uint8_t *salt, int saltlen, uint32_t iterations, uint8_t *key, int keylen, void (*progress_callback)(uint32_t current, uint32_t total))
{
	#define HMACLEN_256  (256/8)

	uint32_t i, j, k;
	uint8_t f[HMACLEN_256], g[HMACLEN_256];
	uint32_t blocks = keylen / HMACLEN_256;
	if (keylen & (HMACLEN_256 - 1)) {
		blocks++;
	}
	for (i = 1; i <= blocks; i++) {
		salt[saltlen    ] = (i >> 24) & 0xFF;
		salt[saltlen + 1] = (i >> 16) & 0xFF;
		salt[saltlen + 2] = (i >> 8) & 0xFF;
		salt[saltlen + 3] = i & 0xFF;
		hmac_sha256(pass, passlen, salt, saltlen + 4, g);
		memcpy(f, g, HMACLEN_256);
		for (j = 1; j < iterations; j++) {
			hmac_sha256(pass, passlen, g, HMACLEN_256, g);
			for (k = 0; k < HMACLEN_256; k++) {
				f[k] ^= g[k];
			}
			if (progress_callback && (j % 256 == 255)) {
				progress_callback(j + 1, iterations);
			}
		}
		if (i == blocks && (keylen & (HMACLEN_256 - 1))) {
			memcpy(key + HMACLEN_256 * (i - 1), f, keylen & (HMACLEN_256 - 1));
		} else {
			memcpy(key + HMACLEN_256 * (i - 1), f, HMACLEN_256);
		}
	}
}

void pbkdf2_hmac_sha512(const uint8_t *pass, int passlen, uint8_t *salt, int saltlen, uint32_t iterations, uint8_t *key, int keylen, void (*progress_callback)(uint32_t current, uint32_t total))
{
	#define HMACLEN_512  (512/8)
	uint32_t i, j, k;
	uint8_t f[HMACLEN_512], g[HMACLEN_512];
	uint32_t blocks = keylen / HMACLEN_512;
	if (keylen & (HMACLEN_512 - 1)) {
		blocks++;
	}
	for (i = 1; i <= blocks; i++) {
		salt[saltlen    ] = (i >> 24) & 0xFF;
		salt[saltlen + 1] = (i >> 16) & 0xFF;
		salt[saltlen + 2] = (i >> 8) & 0xFF;
		salt[saltlen + 3] = i & 0xFF;
		hmac_sha512(pass, passlen, salt, saltlen + 4, g);
		memcpy(f, g, HMACLEN_512);
		for (j = 1; j < iterations; j++) {
			hmac_sha512(pass, passlen, g, HMACLEN_512, g);
			for (k = 0; k < HMACLEN_512; k++) {
				f[k] ^= g[k];
			}
			if (progress_callback && (j % 256 == 255)) {
				progress_callback(j + 1, iterations);
			}
		}
		if (i == blocks && (keylen & (HMACLEN_512 - 1))) {
			memcpy(key + HMACLEN_512 * (i - 1), f, keylen & (HMACLEN_512 - 1));
		} else {
			memcpy(key + HMACLEN_512 * (i - 1), f, HMACLEN_512);
		}
	}
}
