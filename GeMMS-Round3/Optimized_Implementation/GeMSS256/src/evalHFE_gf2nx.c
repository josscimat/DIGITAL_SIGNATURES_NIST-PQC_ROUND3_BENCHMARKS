#include "evalHFE_gf2nx.h"

#include "add_gf2n.h"
#include "sqr_gf2n.h"
#include "mul_gf2n.h"
#include "rem_gf2n.h"
#include "tools_gf2n.h"
#include "tools_gf2nv.h"
#include "tools_gf2v.h"
#include "gf2nx.h"

#if HFEv
    #include "vecMatProduct_gf2.h"
    #include "evalMQSv_gf2.h"
#endif


/**
 * @brief   Evaluation of F in (X,v), with F a HFEv polynomial.
 * @details Firstly, we compute X^(q^j) for j=0 to HFEDegI.
 * Then, we compute, sum_j of X^(q^j)*(Bi + sum_k=0_to_(j-1) A_j,k X^(q^k)).
 * When D is a power of two, we add X^(D/2) to the last sum_k (to obtain the
 * monic term X^D). Each sum is computed in GF(2)[x], and the modular reduction
 * is computed at the end.
 * @param[out]  Fxv The evaluation of F in xv, in GF(2^n).
 * @param[in]   F   A monic HFEv polynomial in GF(2^n)[X] stored with a sparse
 * representation.
 * @param[in]   xv  A vector of n+v elements in GF(2).
 * @remark  Requirement: F is monic.
 * @remark  Constant-time implementation.
 * @remark  Complexity: (#F-2) multiplications in GF(2)[x],
 *                      Ceil(Log_2(D))+1 modular reductions,
 *                      Ceil(Log_2(D))-1 squares in GF(2^n).
 * We can compare to the complexity of the Horner method:
 *                      (#F-2) multiplications in GF(2^n),
 *                      Floor(Log_2(D))-2 squares in GF(2^n).
 */
void PREFIX_NAME(evalHFEv_gf2nx)(gf2n Fxv, cst_sparse_monic_gf2nx F,
                                           cst_vecnv_gf2 xv)
{
    static_gf2n cur_acc[NB_WORD_MUL];
    #if (HFEDeg>1)
        static_gf2n prod[NB_WORD_MUL],acc[NB_WORD_MUL];
    #endif
    static_gf2n tab_Xqj[(HFEDegI+1)*NB_WORD_GFqn];

    #if (HFEDeg>2)
        vec_gf2n tab_Xqj_cp,tab_Xqj_cp2;
        unsigned int j,k;
    #else
        vec_gf2n tab_Xqj_cp;
        unsigned int j;
    #endif

    #if HFEv
        static_vecv_gf2 V[NB_WORD_GFqv];
    #endif


    tab_Xqj_cp=tab_Xqj;

    /* j=0: X^(2^0) */
    copy_gf2n(tab_Xqj,xv);
    #if (HFEv&&HFEnr)
        tab_Xqj[NB_WORD_GFqn-1]&=MASK_GF2n;
    #endif
    tab_Xqj_cp+=NB_WORD_GFqn;
    /* Compute X^(2^j) */
    for(j=1;j<=HFEDegI;++j)
    {
        sqr_gf2n(tab_Xqj_cp,tab_Xqj_cp-NB_WORD_GFqn);
        tab_Xqj_cp+=NB_WORD_GFqn;
    }


    /* Evaluation of the constant, quadratic in the vinegars */

    #if HFEv
        #if HFEnr
            #if ((NB_WORD_GFqn+NB_WORD_GFqv) == NB_WORD_GF2nv)
            for(j=0;j<NB_WORD_GFqv;++j)
            #else
            for(j=0;j<(NB_WORD_GFqv-1);++j)
            #endif
            {
                V[j]=(xv[NB_WORD_GFqn-1+j]>>HFEnr)
                    ^(xv[NB_WORD_GFqn+j]<<(64-HFEnr));
            }
            #if ((NB_WORD_GFqn+NB_WORD_GFqv) != NB_WORD_GF2nv)
                V[j]=xv[NB_WORD_GFqn-1+j]>>HFEnr;
            #endif
        #else
            for(j=0;j<NB_WORD_GFqv;++j)
            {
                V[j]=xv[NB_WORD_GFqn+j];
            }
        #endif

        /* Evaluation of the vinegar constant */
        evalMQSv_gf2(cur_acc,V,F);

        set0_high_product_gf2n(cur_acc);
    #else
        copy_gf2n(cur_acc,F);
    #endif

    F+=MQv_GFqn_SIZE;


    /* Evaluation of the linear terms in the vinegars */
    /* + evaluation of the linear and quadratic terms in X */

    #if (HFEDeg==1)
        /* Monic case */
        add_gf2n(Fxv,cur_acc,tab_Xqj);
    #else
        /* j=0 */

        /* Degree 1 term */

        /* Linear term */
        #if HFEv
            vecMatProductv_gf2(acc,V,F+NB_WORD_GFqn);
            add2_gf2n(acc,F);
        #else
            copy_gf2n(acc,F);
        #endif

        tab_Xqj_cp=tab_Xqj;
        #if (HFEDeg==2)
            /* Monic case */
            add2_gf2n(acc,tab_Xqj);
        #else
            /* mul by X */
            mul_gf2x(prod,tab_Xqj_cp,acc);
            add2_product_gf2n(cur_acc,prod);

            F+=MLv_GFqn_SIZE;
            /* X^(q^j) * (sum a_j,k X^q^k) */

            #if (ENABLED_REMOVE_ODD_DEGREE&&HFEs)
            for(j=1;j<=LOG_odd_degree;++j)
            #else
            for(j=1;j<HFEDegI;++j)
            #endif
            {
                /* Linear term */
                #if HFEv
                    vecMatProductv_gf2(acc,V,F+NB_WORD_GFqn);
                    add2_gf2n(acc,F);
                #else
                    copy_gf2n(acc,F);
                #endif
                set0_high_product_gf2n(acc);
                F+=MLv_GFqn_SIZE;

                /* Quadratic terms */
                tab_Xqj_cp2=tab_Xqj_cp;
                for(k=0;k<j;++k)
                {
                    mul_gf2x(prod,F,tab_Xqj_cp2);
                    add2_product_gf2n(acc,prod);
                    F+=NB_WORD_GFqn;
                    tab_Xqj_cp2+=NB_WORD_GFqn;
                }
                rem_gf2n(acc,acc);

                mul_gf2x(prod,tab_Xqj_cp2,acc);
                add2_product_gf2n(cur_acc,prod);
            }


            #if (ENABLED_REMOVE_ODD_DEGREE&&HFEs)
            for(;j<HFEDegI;++j)
            {
                /* Linear term */
                #if HFEv
                    vecMatProductv_gf2(acc,V,F+NB_WORD_GFqn);
                    add2_gf2n(acc,F);
                #else
                    copy_gf2n(acc,F);
                #endif
                set0_high_product_gf2n(acc);
                F+=MLv_GFqn_SIZE;

                /* Quadratic terms */
                tab_Xqj_cp2=tab_Xqj_cp+NB_WORD_GFqn;
                for(k=1;k<j;++k)
                {
                    mul_gf2x(prod,F,tab_Xqj_cp2);
                    add2_product_gf2n(acc,prod);
                    F+=NB_WORD_GFqn;
                    tab_Xqj_cp2+=NB_WORD_GFqn;
                }
                rem_gf2n(acc,acc);

                mul_gf2x(prod,tab_Xqj_cp2,acc);
                add2_product_gf2n(cur_acc,prod);
            }
            #endif

            /* j=HFEDegI */

            /* Linear term */
            #if HFEv
                vecMatProductv_gf2(acc,V,F+NB_WORD_GFqn);
                add2_gf2n(acc,F);
            #else
                copy_gf2n(acc,F);
            #endif
            #if HFEDegJ
                set0_high_product_gf2n(acc);
            #endif
            F+=MLv_GFqn_SIZE;

            /* Quadratic terms */
            tab_Xqj_cp2=tab_Xqj_cp;
            #if HFEDegJ
                #if (ENABLED_REMOVE_ODD_DEGREE&&HFEs)
                tab_Xqj_cp2+=NB_WORD_GFqn;
                for(k=1;k<HFEDegJ;++k)
                #else
                for(k=0;k<HFEDegJ;++k)
                #endif
                {
                    mul_gf2x(prod,F,tab_Xqj_cp2);
                    add2_product_gf2n(acc,prod);
                    F+=NB_WORD_GFqn;
                    tab_Xqj_cp2+=NB_WORD_GFqn;
                }

                /* k=HFEDegJ : monic case */
                add2_gf2n(acc,tab_Xqj_cp2);
                rem_gf2n(acc,acc);
            #else
                /* k=HFEDegJ : monic case */
                add_gf2n(acc,acc,tab_Xqj_cp2);
            #endif

            tab_Xqj_cp+=HFEDegI*NB_WORD_GFqn;
        #endif
        mul_gf2x(prod,tab_Xqj_cp,acc);
        add2_product_gf2n(cur_acc,prod);

        /* Final reduction of F(xv) */
        rem_gf2n(Fxv,cur_acc);
    #endif
}


