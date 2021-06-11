#ifndef _RANDOMBYTES_H
#define _RANDOMBYTES_H

#include "debug.h"


#if DEBUG
    /* Set all to zero */
    #define ENABLED_OPENSSL_FIPS 0
    #define ENABLED_OPENSSL_NORMAL 0
#else
    /* The user can modify the value of the following macros */

    /* Set to 1 to enable the FIPS module from OpenSSL */
    #define ENABLED_OPENSSL_FIPS 0
    /* Set to 1 to use the standard RNG of OpenSSL */
    #define ENABLED_OPENSSL_NORMAL 1
#endif


#ifdef __cplusplus
    extern "C" {
#endif
extern int randombytes_NIST(unsigned char *x, unsigned long long xlen);
extern int randombytes_FIPS(unsigned char *x, unsigned long long xlen);
#ifdef __cplusplus
    }
#endif


#if DEBUG
    #define randombytes randombytes_NIST
#elif ENABLED_OPENSSL_FIPS
    #define randombytes randombytes_FIPS
#elif ENABLED_OPENSSL_NORMAL
    #include <openssl/rand.h>
    #define randombytes(x,xlen) RAND_bytes(x,(int)xlen)
#else
    #define randombytes randombytes_NIST
#endif


#endif

