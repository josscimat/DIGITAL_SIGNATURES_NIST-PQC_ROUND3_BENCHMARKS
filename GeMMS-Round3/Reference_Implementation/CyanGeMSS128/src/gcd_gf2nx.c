#include "gcd_gf2nx.h"
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


