#include "interpolateHFE_FS.h"
#include <stdlib.h>

#include "add_gf2n.h"
#include "sqr_gf2n.h"
#include "mul_gf2n.h"
#include "rem_gf2n.h"
#include "tools_gf2n.h"
#include "tools_gf2nv.h"
#include "tools_gf2v.h"
#include "gf2nx.h"
#include "evalHFE_gf2nx.h"

#if HFEv
    #include "vecMatProduct_gf2.h"
#endif


/**
 * @brief   Computation of the multivariate representation of a HFEv
 * polynomial, then a change of variables is applied.
 * @details Computation of the multivariate representation of F(XS),
 * by evaluation/interpolation. We take the following N points in GF(2)^(n+v) :
 * n0=(0 ... 0),
 * e1,e2,...,e_(n+v) with ei the i-th row of the identity matrix,
 * all ei+ej, with i<j.
 * Let p be a MQS, we have:
 * p(n0) = cst,
 * p(ei) = cst + p_i,
 * p(ei+ej) = cst + p_i + p_j + p_i,j.
 * So, these N evaluations give directly p. The interpolation is trivial.
 * @param[in]   F   A monic HFEv polynomial in GF(2^n)[X,x_(n+1),...,x_(n+v)]
 * stored with a sparse representation.
 * @param[in]   S   A matrix (n+v)*(n+v) in GF(2). S should be invertible
 * (by definition of a change of variables).
 * @param[out]  MQS A MQS in GF(2^n)[x1,...,x_(n+v)] (n equations,
 * n+v variables). MQS is stored as one equation in GF(2^n)[x1,...,x_(n+v)]
 * (monomial representation + quadratic form cst||Q).
 * @return   0 if the result is correct, ERROR_ALLOC for error from
 * malloc/calloc functions.
 * @remark  Requires to allocate MQnv_GFqn_SIZE words for MQS.
 * @remark  Requirement: F is monic.
 * @remark  Constant-time implementation.
 */
int PREFIX_NAME(interpolateHFE_FS_ref)(mqsnv_gf2n MQS, cst_sparse_monic_gf2nx F,
                                                       cst_GLnv_gf2 S)
{
    static_gf2nv e_ijS[NB_WORD_GF2nv];
    vec_gf2n tab_eval,tab_eval_i,tab_eval_i2;
    cst_gf2n e_iS,e_i2S;
    unsigned int i,i2;

    /* Let e_i be the i-th row of the identity matrix */
    /* We compute all F(e_i*S), then all F((e_i+e_j)S) */


    /* Table of the F(e_i*S) */
    tab_eval=(UINT*)malloc(HFEnv*NB_WORD_GFqn*sizeof(UINT));
    VERIFY_ALLOC_RET(tab_eval);


    /* Constant: copy the first coefficient of F in MQS */
    copy_gf2n(MQS,F);


    /* e_i*S corresponds to the i-th row of S */
    e_iS=S;
    tab_eval_i=tab_eval;
    for(i=0;i<HFEnv;++i)
    {
        /* F(e_i*S) = cst + p_i */
        evalHFEv_gf2nx(tab_eval_i,F,e_iS);

        tab_eval_i+=NB_WORD_GFqn;
        /* Next e_i */
        e_iS+=NB_WORD_GF2nv;
    }


    e_iS=S;
    tab_eval_i=tab_eval;
    for(i=0;i<HFEnv;++i)
    {
        /* Update of MQS with F(e_i*S) from tab_eval */
        MQS+=NB_WORD_GFqn;

        /* p_i = F(e_i*S) + cst */
        add2_gf2n(tab_eval_i,F);
        copy_gf2n(MQS,tab_eval_i);

        /* Computation of p_i,i2 by computing F((e_i+e_i2)*S) */
        tab_eval_i2=tab_eval_i;
        e_i2S=e_iS;
        for(i2=i+1;i2<HFEnv;++i2)
        {
            MQS+=NB_WORD_GFqn;
            tab_eval_i2+=NB_WORD_GFqn;
            e_i2S+=NB_WORD_GF2nv;

            /* F((e_i+e_i2)*S) = cst + p_i + p_i2 + p_i,i2 */

            /* F((e_i+e_i2)*S) */
            add_gf2nv(e_ijS,e_iS,e_i2S);
            evalHFEv_gf2nx(MQS,F,e_ijS);

            /* + p_i */
            add2_gf2n(MQS,tab_eval_i);
            /* + p_i2 + cst */
            add2_gf2n(MQS,tab_eval_i2);
        }

        tab_eval_i+=NB_WORD_GFqn;
        e_iS+=NB_WORD_GF2nv;
    }

    free(tab_eval);

    return 0;
}




