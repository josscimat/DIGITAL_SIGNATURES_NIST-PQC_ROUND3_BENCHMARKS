#ifndef _FINDROOTSSPLIT_GF2NX_H
#define _FINDROOTSSPLIT_GF2NX_H


#include "prefix_name.h"
#include "parameters_HFE.h"
#include "matrix_gf2n.h"
#include "gf2nx.h"


#if (HFEn&1)
    #include "tools_gf2n.h"
    void PREFIX_NAME(findRootsSplit_x2_x_c_HT_gf2nx)(gf2n root, gf2n c);
    void PREFIX_NAME(findRootsSplit2_HT_gf2nx)(vec_gf2n roots, gf2nx f);
    #define findRootsSplit_x2_x_c_HT_gf2nx \
                PREFIX_NAME(findRootsSplit_x2_x_c_HT_gf2nx)
    #define findRootsSplit2_HT_gf2nx PREFIX_NAME(findRootsSplit2_HT_gf2nx)
#endif


void PREFIX_NAME(findRootsSplit_gf2nx)(vec_gf2n roots, gf2nx f,
                                       unsigned int deg);
#define findRootsSplit_gf2nx PREFIX_NAME(findRootsSplit_gf2nx)


#endif

