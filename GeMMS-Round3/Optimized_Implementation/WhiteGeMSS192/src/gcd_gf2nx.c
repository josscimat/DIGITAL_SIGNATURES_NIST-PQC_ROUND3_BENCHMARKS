#include "gcd_gf2nx.h"
#include "add_gf2nx.h"
#include "div_gf2nx.h"
#include "tools_gf2n.h"
#include "inv_gf2n.h"
#include "add_gf2n.h"
#include "mul_gf2n.h"
#include "init.h"


/**
 * @brief   Gcd in GF(2^n)[X], in-place.
 * @details Variable-time Euclid–Stevin.
 * @param[in,out]   A   An element of GF(2^n)[X].
 * @param[in]   da  The degree of A.
 * @param[in,out]   B   An element of GF(2^n)[X].
 * @param[in]   db  The degree of B.
 * @return  The degree of the last remainder R which is strictly greater than 0.
 * At the end of the algorithm, R=(1-(*b))*A + (*b)*B, R2=(*b)*A + (1-(*b))*B,
 * degree(R) = returned value, degree(R2)=0.
 * If R2==0, then R=GCD(A,B). Else, R2=GCD(A,B) and its degree is 0.
 * @remark  Requirement: da>db.
 * @remark  This implementation is not in constant-time.
 * @remark  Complexity: In the worst case,
 *                      (da+db)*db - 1 + (da*(da+1)-db*(db-1))/2
 *                      multiplications in GF(2^n).
 *                      da*db additions in GF(2^n).
 */
unsigned int PREFIX_NAME(gcdES_gf2nx)(unsigned int *b,gf2nx A,unsigned int da,
                                                      gf2nx B,unsigned int db)
{
    static_gf2n inv[NB_WORD_GFqn];
    gf2nx tmp;
    unsigned int i;

    /* *b = 0: B is the last remainder
       *b = 1: A is the last remainder */
    *b=0;

    while(db)
    {
        /* Compute A = LT(B)*A - LT(A)*B until to have da < db */
        /* Do not compute an inverse in GF(2^n) */
        while(da>=db)
        {
            /* LT(B)*A */
            for(i=0;i<da;++i)
            {
                mul_gf2n(A+i*NB_WORD_GFqn,A+i*NB_WORD_GFqn,
                                          B+db*NB_WORD_GFqn);
            }

            /* - LT(A)*B */
            for(i=0;i<db;++i)
            {
                mul_gf2n(inv,B+i*NB_WORD_GFqn,A+da*NB_WORD_GFqn);
                add2_gf2n(A+(da-db+i)*NB_WORD_GFqn,inv);
            }

            --da;
            /* Search the current degree of A */
            while(is0_gf2n(A+da*NB_WORD_GFqn)&&(da>0))
            {
                --da;
            }
        }

        /* Swaps A and B */
        tmp=A;
        A=B;
        B=tmp;
        /* Swaps da and db */
        SWAP_WORD(da,db);
        /* 0 becomes 1 and 1 becomes 0 */
        *b=(1-(*b));
    }

    return da;
}


/**
 * @brief   Gcd in GF(2^n)[X], in-place.
 * @param[in,out]   A   An element of GF(2^n)[X].
 * @param[in]   da  The degree of A.
 * @param[in,out]   B   An element of GF(2^n)[X].
 * @param[in]   db  The degree of B.
 * @return  The degree of the last remainder R which is strictly greater than 0.
 * At the end of the algorithm, R=(1-(*b))*A + (*b)*B, R2=(*b)*A + (1-(*b))*B,
 * degree(R) = returned value, degree(R2)=0.
 * If R2==0, then R=GCD(A,B). Else, R2=GCD(A,B) and its degree is 0.
 * @remark  Requirement: da>db.
 * @remark  This implementation is not in constant-time.
 */
unsigned int PREFIX_NAME(gcd_gf2nx)(unsigned int* b, gf2nx A, unsigned int da,
                                                     gf2nx B, unsigned int db)
{
    static_gf2n inv[NB_WORD_GFqn];
    gf2nx tmp;
    unsigned int i;

    /* *b = 0: B is the last remainder
       *b = 1: A is the last remainder */
    *b=0;

    while(db)
    {
        /* Computation of A = A mod B, of degree da */

        /* Minimizes the number of multiplications by an inverse */
        /* 2db > da */
        if( (db<<1) > da )
        {
            /* At most da-db+1 multiplications by an inverse */
            da=div_r_gf2nx(A,da,B,db);
        } else
        {
            /* B becomes monic: db multiplications by an inverse */
            inv_gf2n(inv,B+db*NB_WORD_GFqn);
            set1_gf2n(B+db*NB_WORD_GFqn);
            for(i=db-1;i!=(unsigned int)(-1);--i)
            {
                mul_gf2n(B+i*NB_WORD_GFqn,B+i*NB_WORD_GFqn,inv);
            }
            da=div_r_monic_gf2nx(A,da,B,db);
        }

        /* Swaps A and B */
        tmp=A;
        A=B;
        B=tmp;
        /* Swaps da and db */
        SWAP_WORD(da,db);
        /* 0 becomes 1 and 1 becomes 0 */
        *b=(1-(*b));
    }

    return da;
}


#define MUL_CONST_GF2NX(res,A,na,cst,i) \
    for(i=0;i<(na);++i)\
    {\
        mul_gf2n((res)+NB_WORD_GFqn*i,(A)+NB_WORD_GFqn*i,cst);\
    }


#define cadd_gf2nx(C,A,B,M,l,i) \
    for(i=0;i<((l)*NB_WORD_GFqn);++i)\
    {\
        (C)[i]=((A)[i]^(B)[i])&(M);\
    }


/**
 * @brief   Gcd in GF(2^n)[X], in-place.
 * @details Constant-time Euclid–Stevin.
 * @param[in,out]   A   An element of GF(2^n)[X], will be modified in output.
 * @param[in]   da  The degree of A, or a upper bound on the degree of A.
 * @param[in,out]   B   An element of GF(2^n)[X], will be GCD(A,B) in output.
 * @param[in]   db  The degree of B.
 * @return  The degree of GCD(A,B).
 * @remark  Requires to allocate max(da,db)+1 elements of GF(2^n) for A and B.
 * @remark  A must be stored as x^(max(da,db)-da) A.
 * @remark  B must be stored as x^(max(da,db)-db) B.
 * @remark  Constant-time implementation when da and db are not secret.
 * @remark  Complexity: let dm = min(da,db) and dM = max(da,db), we have:
 *                      dM*(2dm+dM+1) multiplications in GF(2^n).
 *                      dm*(3*dM+2) + (3*(dM+1)*dM/2) additions in GF(2^n).
 *                      Total: ~ 3*dM^2 mul and (9/2)*dM^2 add in GF(2^n).
 *                      (2*dm+dM)*(dM+1) additions in GF(2^n).
 *                      (2*dm+dM+1)*dM/2 additions of products in GF(2)[x].
 */
unsigned int PREFIX_NAME(gcdES_cst_gf2nx)(gf2nx A, unsigned int da,
                                          gf2nx B, unsigned int db)
{
    unsigned int nmax;
    nmax=MAXI(da,db)+1;

    static_gf2nx AB[NB_WORD_GFqn*nmax],tmp[NB_WORD_GFqn*(nmax-1)+1];
    gf2nx lt_A,lt_B;
    UINT swap;
    unsigned int i,nb_step;
    int32_t delta;


    lt_A=A+NB_WORD_GFqn*(nmax-1);
    lt_B=B+NB_WORD_GFqn*(nmax-1);

    nb_step=da+db;
    delta=da-db;

    while(nb_step>=nmax)
    {
        --nb_step;

        /* We implement delta<0 by (delta>>31)&1 */
        swap=-(isNot0_gf2n(lt_A)&((delta>>31)&((int32_t)1)));

        delta^=(delta^(-delta))&swap;
        --delta;

        /* We swap A and B only if swap!=0 */
        /* In the binary fields, it is useless to compute A ^= (A^B)&swap,
           because A = (lt_B*A + lt_A*B)*X is symmetric in A and B.
           So, we will compute only B ^= (A^B)&swap. */
        cadd_gf2nx(AB,A,B,swap,nmax,i);

        /* Compute A = (lt_B*A - lt_A*B)*X */
        /* -1 because we know the leading term will be zero */
        MUL_CONST_GF2NX(tmp,A,nmax-1,lt_B,i);
        copy_gf2n(A,lt_A);
        MUL_CONST_GF2NX(A+NB_WORD_GFqn,B,nmax-1,A,i);
        add2_gf2nx(A+NB_WORD_GFqn,tmp,nmax-1,i);
        set0_gf2n(A);

        /* B=A only if swap!=0, else B=B */
        add2_gf2nx(B,AB,nmax,i);
    }

    /* Here, nmax=nb_step+1 */
    while(nmax>1)
    {
        /* max(da,db) will decrement necessarily, excepted if B is currently
           the GCD. If B is the GCD, A=0 and so swap=0. So, A and B will not
           be modified until the end of the algorithm. So we can decrement nmax.
        */
        --nmax;

        /* We implement delta<0 by (delta>>31)&1 */
        swap=-(isNot0_gf2n(lt_A)&((delta>>31)&((int32_t)1)));

        delta^=(delta^(-delta))&swap;
        --delta;

        /* We swap A and B only if swap!=0 */
        /* In the binary fields, it is useless to compute A ^= (A^B)&swap,
           because A = (lt_B*A + lt_A*B)*X is symmetric in A and B.
           So, we will compute only B ^= (A^B)&swap. */
        cadd_gf2nx(AB,A+NB_WORD_GFqn,B+NB_WORD_GFqn,swap,nmax,i);

        /* Compute A = (lt_B*A - lt_A*B)*X */
        /* nmax and not nmax+1 because we know the leading term will be zero */
        MUL_CONST_GF2NX(tmp,A,nmax,lt_B,i);
        copy_gf2n(A,lt_A);
        MUL_CONST_GF2NX(A+NB_WORD_GFqn,B,nmax,A,i);
        add2_gf2nx(A+NB_WORD_GFqn,tmp,nmax,i);

        /* These coefficients will not used anymore (we decrement nmax). */
        A+=NB_WORD_GFqn;
        B+=NB_WORD_GFqn;

        /* B=A only if swap!=0, else B=B */
        add2_gf2nx(B,AB,nmax,i);
    }

    /* B is the GCD */
    return (-delta)>>1;
}


#undef MUL_CONST_GF2NX
#undef cadd_gf2nx


