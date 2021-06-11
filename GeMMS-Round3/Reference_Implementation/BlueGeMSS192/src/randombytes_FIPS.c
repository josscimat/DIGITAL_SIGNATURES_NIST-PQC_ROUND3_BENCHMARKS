#include "randombytes_FIPS.h"

#include <openssl/err.h>
#include <openssl/crypto.h>
#include <openssl/rand.h>

int randombytes_FIPS(unsigned char *x, unsigned long long xlen)
{
    if(!FIPS_mode())
    {
        if(FIPS_mode_set(1)!=1)
        {
            exit(ERR_get_error());
        }
    }

    if(!RAND_bytes(x,(int)xlen)) 
    {
        exit(6);
    }

    return 0;
}

