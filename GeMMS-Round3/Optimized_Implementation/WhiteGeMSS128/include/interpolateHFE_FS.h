#ifndef _INTERPOLATEHFE_FS_H
#define _INTERPOLATEHFE_FS_H


#include "prefix_name.h"
#include "arch.h"
#include "MQS_gf2.h"
#include "gf2nx.h"
#include "matrix_gf2.h"


int PREFIX_NAME(interpolateHFE_FS_ref)(mqsnv_gf2n MQS, cst_sparse_monic_gf2nx F,
                                                       cst_GLnv_gf2 S);
#define interpolateHFE_FS_ref PREFIX_NAME(interpolateHFE_FS_ref)

#define interpolateHFE_FS interpolateHFE_FS_ref


#endif

