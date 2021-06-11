#ifndef _GCD_GF2NX_H
#define _GCD_GF2NX_H

#include "prefix_name.h"
#include "arch.h"
#include "gf2nx.h"


unsigned int PREFIX_NAME(gcd_gf2nx)(unsigned int* b, gf2nx A, unsigned int da,
                                                     gf2nx B, unsigned int db);
unsigned int PREFIX_NAME(gcdES_gf2nx)(unsigned int *b,gf2nx A,unsigned int da,
                                                      gf2nx B,unsigned int db);
unsigned int PREFIX_NAME(gcdES_cst_gf2nx)(gf2nx A, unsigned int da,
                                          gf2nx B, unsigned int db);
#define gcd_gf2nx PREFIX_NAME(gcd_gf2nx)
#define gcdES_gf2nx PREFIX_NAME(gcdES_gf2nx)
#define gcdES_cst_gf2nx PREFIX_NAME(gcdES_cst_gf2nx)


#define gcd_cst_HFE_gf2nx(A,da,B) gcdES_cst_gf2nx(A,da,B,HFEDeg)


#endif

