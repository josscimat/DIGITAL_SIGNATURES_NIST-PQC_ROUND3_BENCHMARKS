#ifndef _EVALHFE_GF2NX_H
#define _EVALHFE_GF2NX_H


#include "prefix_name.h"
#include "tools_gf2n.h"
#include "gf2nx.h"
#include "matrix_gf2.h"


void PREFIX_NAME(evalHFEv_gf2nx)(gf2n Fxv, cst_sparse_monic_gf2nx F,
                                           cst_vecnv_gf2 xv);
#define evalHFEv_gf2nx PREFIX_NAME(evalHFEv_gf2nx)


#endif

