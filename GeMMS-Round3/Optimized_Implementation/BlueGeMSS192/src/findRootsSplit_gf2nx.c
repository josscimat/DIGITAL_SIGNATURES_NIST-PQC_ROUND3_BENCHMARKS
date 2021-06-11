#include "findRootsSplit_gf2nx.h"
#include <stdlib.h>
#include "arch.h"
#include "rand_gf2n.h"
#include "add_gf2nx.h"
#include "sqr_gf2nx.h"
#include "gcd_gf2nx.h"
#include "inv_gf2n.h"
#include "tools_gf2n.h"
#include "sqr_gf2n.h"
#include "mul_gf2n.h"
#include "div_gf2nx.h"
#include <string.h>


/**
 * @brief   Computation of the sum from i=0 to n-1 of ((rX)^(2^i)) mod f
 * @param[in,out]    poly_trace  An element of GF(2^n)[X], initialized to rX
 * with r in GF(2^n). The ouput value is the sum from i=0 to n-1 of 
 * ((rX)^(2^i) mod f), in GF(2^n)[X].
 * @param[in]   poly_frob   An intermediate buffer, becomes (rX)^(2^(n-1)) mod f
 * @param[in]   f   A monic polynomial in GF(2^n)[X].
 * @param[in]   deg The degree of f.
 * @remark  Requires to allocate deg elements of GF(2^n) for poly_trace.
 * @remark  Requires to allocate ((deg<<1)-1)*NB_WORD_GFqn words for poly_frob,
 * initialized to zero.
 * @remark  Requirement: f is monic.
 * @remark  Requirement: deg>1.
 * @remark  Constant-time implementation when deg is not secret and when 
 * CONSTANT_TIME!=0.
 */
static void traceMap_gf2nx(gf2nx poly_trace, gf2nx poly_frob,
                           cst_gf2nx f, unsigned int deg)
{
    #if (!CONSTANT_TIME)
        /* d is the degree of poly_frob */
        unsigned int d;
    #endif
    unsigned int j,i;

    i=1;
    /* (2^i) < deg does not require modular reduction by f */
    #if(HFEn<33)
        const unsigned int min=(deg<(1U<<HFEn))?deg:HFEn;
        while((1U<<i)<min)
    #else
        while((1U<<i)<deg)
    #endif
    {
        /* poly_trace += ((rX)^(2^i)) mod f
           Here, ((rX)^(2^i)) mod f == (rX)^(2^i) since (2^i) < deg */
        sqr_gf2n(poly_trace+(NB_WORD_GFqn<<i),poly_trace+(NB_WORD_GFqn<<(i-1)));
        ++i;
    }

    /* Here, (rX)^(2^i) is the first time where we need modular reduction */
    if(i<HFEn)
    {
        /* poly_frob = (rX)^(2^i) = ((rX)^(2^(i-1)))^2 */
        sqr_gf2n(poly_frob+(NB_WORD_GFqn<<i),poly_trace+(NB_WORD_GFqn<<(i-1)));

        #if CONSTANT_TIME
            /* poly_frob = ((rX)^(2^i)) mod f */
            div_r_monic_cst_gf2nx(poly_frob,1U<<i,f,deg);
            /* poly_trace += ((rX)^(2^i)) mod f */
            add2_gf2nx(poly_trace,poly_frob,deg,j);
        #else
            /* poly_frob = ((rX)^(2^i)) mod f */
            d=div_r_monic_gf2nx(poly_frob,1U<<i,f,deg);
            /* poly_trace += ((rX)^(2^i)) mod f */
            add2_gf2nx(poly_trace,poly_frob,d+1,j);
        #endif
        ++i;

        for(;i<HFEn;++i)
        {
            #if CONSTANT_TIME
                /* poly_frob = (rX)^(2^i) = ((rX)^(2^(i-1)) mod f)^2 */
                sqr_gf2nx(poly_frob,deg-1);
                /* poly_frob = ((rX)^(2^i)) mod f */
                div_r_monic_cst_gf2nx(poly_frob,(deg-1)<<1U,f,deg);
                /* poly_trace += ((rX)^(2^i)) mod f */
                add2_gf2nx(poly_trace,poly_frob,deg,j);
            #else
                /* poly_frob = (rX)^(2^i) = ((rX)^(2^(i-1)) mod f)^2 */
                sqr_gf2nx(poly_frob,d);
                /* poly_frob = ((rX)^(2^i)) mod f */
                d=div_r_monic_gf2nx(poly_frob,d<<1U,f,deg);
                /* poly_trace += ((rX)^(2^i)) mod f */
                add2_gf2nx(poly_trace,poly_frob,d+1,j);
            #endif
        }
    }
}


#if (HFEn&1)
#include "add_gf2n.h"
/**
 * @brief   Computation of a root of x^2+x+c, when the latter is a split
 * polynomial. The second root is root+1. n has to be odd.
 * @details The half-trace is computed with the ITMIA strategy in base 4.
 * @param[out]  root    A root of x^2+x+c, in GF(2^n).
 * @param[in]   c   An element of GF(2^n).
 * @remark  Requirement: x^2+x+c is split.
 * @remark  Requirement: n is odd.
 * @remark  Constant-time implementation.
 */
void PREFIX_NAME(findRootsSplit_x2_x_c_HT_gf2nx)(gf2n root, gf2n c)
{
    static_gf2n alpha[NB_WORD_GFqn];
    const unsigned int e=(HFEn+1)>>1;
    unsigned int i,j,e2,pos;

    /* Search the position of the MSB of n-1 */
    pos=31;
    while(!(e>>pos))
    {
        --pos;
    }

    /* i=pos */
    copy_gf2n(root,c);
    e2=1;
    for(i=pos-1;i!=(unsigned int)(-1);--i)
    {
        e2<<=1;
        /* j=0 */
        sqr_gf2n(alpha,root);
        for(j=1;j<e2;++j)
        {
            sqr_gf2n(alpha,alpha);
        }
        add2_gf2n(root,alpha);

        e2=e>>i;
        if(e2&ONE32)
        {
            sqr_gf2n(alpha,root);
            sqr_gf2n(root,alpha);
            add2_gf2n(root,c);
        }
    }
}


/**
 * @brief   Computation of the roots of f, when f is a split and monic degree
 * two polynomial. n has to be odd.
 * @details Change of variable to obtain x^2+x+c = 0, then the half-trace is
 * computed with the ITMIA strategy in base 4.
 * @param[out]  roots   The vector of the roots of f, in GF(2^n).
 * @param[in]   f   A monic and split degree two polynomial in GF(2^n)[X].
 * @remark  Requires to allocate two elements of GF(2^n) for roots.
 * @remark  Requirement: f is monic and split.
 * @remark  Requirement: n is odd.
 * @remark  Constant-time implementation.
 */
void PREFIX_NAME(findRootsSplit2_HT_gf2nx)(vec_gf2n roots, gf2nx f)
{
    static_gf2n c[NB_WORD_GFqn],alpha[NB_WORD_GFqn];

    /* f1^2 */
    sqr_gf2n(c,f+NB_WORD_GFqn);
    /* f1^-2 */
    inv_gf2n(roots,c);
    /* f0 * f1^-2 */
    mul_gf2n(c,f,roots);

    findRootsSplit_x2_x_c_HT_gf2nx(alpha,c);

    f+=NB_WORD_GFqn;
    /* alpha*f1 */
    mul_gf2n(roots,alpha,f);
    /* (alpha+1)*f1 */
    add_gf2n(roots+NB_WORD_GFqn,roots,f);
}
#endif


/**
 * @brief   Computation of the roots of f, when f is split and monic.
 * @param[out]  roots   The vector of the roots of f, in GF(2^n).
 * @param[in]   f   A monic and split polynomial in GF(2^n)[X].
 * @param[in]   deg The degree of f.
 * @remark  Requires to allocate deg elements of GF(2^n) for roots.
 * @remark  Requirement: f is monic and split.
 * @remark  Requirement: deg>0.
 * @remark  This implementation is not in constant-time.
 */
void PREFIX_NAME(findRootsSplit_gf2nx)(vec_gf2n roots, gf2nx f,
                                       unsigned int deg)
{
    gf2nx poly_trace,f_cp,tmp_p;
    gf2nx poly_frob;
    static_gf2n inv[NB_WORD_GFqn];
    unsigned int b,i,l,d;

    if(deg==1)
    {
        /* Extract the unique root which is the constant of f */
        copy_gf2n(roots,f);
        return;
    }
    #if (HFEn&1)
    if(deg==2)
    {
        findRootsSplit2_HT_gf2nx(roots,f);
        return;
    }
    #endif

    poly_frob=(UINT*)malloc(((deg<<1)-1)*NB_WORD_GFqn*sizeof(UINT));
    /* poly_trace is modulo f, this degree is strictly less than deg */
    poly_trace=(UINT*)malloc(deg*NB_WORD_GFqn*sizeof(UINT));
    /* f_cp a copy of f */
    f_cp=(UINT*)malloc((deg+1)*NB_WORD_GFqn*sizeof(UINT));
    do
    {
        /* Set poly_frob to zero */
        set0_gf2nx(poly_frob,(deg<<1)-1,l);
        /* Set poly_trace to zero */
        set0_gf2nx(poly_trace,deg,l);

        /* Initialization to rX */
        /* Probability 2^(-n) to find 0 with a correct RNG */
        do
        {
            rand_gf2n(poly_trace+NB_WORD_GFqn);
        } while(is0_gf2n(poly_trace+NB_WORD_GFqn));

        /* copy of f because the gcd modifies f */
        copy_gf2nx(f_cp,f,deg+1,l);

        traceMap_gf2nx(poly_trace,poly_frob,f_cp,deg);
        /* Degree of poly_trace */
        d=deg-1;
        while(is0_gf2n(poly_trace+d*NB_WORD_GFqn)&&d)
        {
            --d;
        }
        l=gcd_gf2nx(&b,f_cp,deg,poly_trace,d);

    } while((!l)||(l==deg));
    free(poly_frob);

    if(b)
    {
        tmp_p=poly_trace;
        poly_trace=f_cp;
        f_cp=tmp_p;
    }
    /* Here, f_cp is a non-trivial divisor of degree l */
    free(poly_trace);

    /* f_cp is the gcd */
    /* Here, it becomes monic */
    inv_gf2n(inv,f_cp+l*NB_WORD_GFqn);
    set1_gf2n(f_cp+l*NB_WORD_GFqn);
    for(i=l-1;i!=(unsigned int)(-1);--i)
    {
        mul_gf2n(f_cp+i*NB_WORD_GFqn,f_cp+i*NB_WORD_GFqn,inv);
    }


    /* f = f_cp * Q */
    /* This function destroyes f */
    div_q_monic_gf2nx(f,deg,f_cp,l);
    /* Necessarily, the polynomial f is null here */

    /* f_cp is monic */
    /* We can apply findRootsSplit_gf2nx recursively */
    findRootsSplit_gf2nx(roots,f_cp,l);
    free(f_cp);

    /* f is monic and f_cp is monic so Q is monic */
    /* We can apply findRootsSplit_gf2nx recursively */
    findRootsSplit_gf2nx(roots+l*NB_WORD_GFqn,f+l*NB_WORD_GFqn,deg-l);
}


