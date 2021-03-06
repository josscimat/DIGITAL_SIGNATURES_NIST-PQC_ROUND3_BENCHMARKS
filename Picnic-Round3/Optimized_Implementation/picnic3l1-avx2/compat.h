/*
 *  This file is part of the optimized implementation of the Picnic signature scheme.
 *  See the accompanying documentation for complete details.
 *
 *  The code is provided under the MIT license, see LICENSE for
 *  more details.
 *  SPDX-License-Identifier: MIT
 */

#ifndef PICNIC_COMPAT_H
#define PICNIC_COMPAT_H

/* in case cmake checks were not run, define HAVE_* for known good configurations */

#include "macros.h"
#if defined(__OpenBSD__)
#include <sys/param.h>
#endif /* __OpenBSD__ */

#if !defined(HAVE_ALIGNED_ALLOC) && !defined(__APPLE__) && !defined(__MINGW32__) &&                \
    !defined(__MINGW64__) &&                                                                       \
    (defined(_ISOC11_SOURCE) || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L))
/* aligned_alloc was introduced in ISO C 2011 */
#define HAVE_ALIGNED_ALLOC
#endif /* HAVE_ALIGNED_ALLOC */

#if !defined(HAVE_EXPLICIT_BZERO) &&                                                               \
    (GLIBC_CHECK(2, 25) || (defined(__OpenBSD__) && OpenBSD >= 201405) || FREEBSD_CHECK(11, 0) ||  \
     NETBSD_CHECK(8, 0))
/* explicit_bzero was introduced in glibc 2.35, OpenBSD 5.5, FreeBSD 11.0 and NetBSD 8.0 */
#define HAVE_EXPLICIT_BZERO
#endif /* HAVE_EXPLICIT_BZERO */

#if !defined(HAVE_CONSTTIME_MEMEQUAL) && NETBSD_CHECK(7, 0)
/* consttime_memequal was introduced in NetBSD 7.0 */
#define HAVE_CONSTTIME_MEMEQUAL
#endif /* HAVE_CONSTTIME_MEMEQUAL */

#if !defined(HAVE_TIMINGSAFE_BCMP) && ((defined(__OpenBSD__) && OpenBSD >= 201105) ||              \
                                       FREEBSD_CHECK(12, 0) || MACOSX_CHECK(10, 12, 1))
/* timingsafe_bcmp was introduced in OpenBSD 4.9, FreeBSD 12.0, and MacOS X 10.12 */
#define HAVE_TIMINGSAFE_BCMP
#endif /* HAVE_TIMINGSAFE_BCMP */

#if defined(HAVE_ALIGNED_ALLOC)
#include <stdlib.h>

#define aligned_free(ptr) free((ptr))
#else
#include <stddef.h>

/**
 * Compatibility implementation of aligned_alloc from ISO C 2011.
 */
void* aligned_alloc(size_t alignment, size_t size);
/**
 * Some aligned_alloc compatbility implementations require custom free
 * functions, so we provide one too.
 */
void aligned_free(void* ptr);
#endif /* HAVE_ALIGNED_ALLOC */

#include "endian_compat.h"

#if !defined(HAVE_TIMINGSAFE_BCMP)
/**
 * Compatibility implementation of timingsafe_bcmp from OpenBSD 4.9 and FreeBSD 12.0.
 */
static inline int timingsafe_bcmp(const void* a, const void* b, size_t len) {
#if defined(HAVE_CONSTTIME_MEMEQUAL)
  return !consttime_memequal(a, b, len);
#else
  const unsigned char* p1 = a;
  const unsigned char* p2 = b;

  unsigned int res = 0;
  for (; len; --len, ++p1, ++p2) {
    res |= *p1 ^ *p2;
  }
  return res;
#endif
}
#endif /* HAVE_TIMINGSAFE_BCMP */

#if !defined(HAVE_EXPLICIT_BZERO)
#if defined(_WIN32)
#include <windows.h>
#endif
/**
 * Compatibility implementation of explicit_bzero
 */
static inline void explicit_bzero(void* a, size_t len) {
#if defined(_WIN32)
  SecureZeroMemory(a, len);
#else
  volatile char* p = a;
  for (; len; ++a, --len) {
    *p = 0;
  }
#endif
}
#endif /* HAVE_EXPLICIT_BZERO */

#endif
