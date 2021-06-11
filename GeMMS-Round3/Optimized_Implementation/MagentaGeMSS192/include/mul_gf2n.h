#ifndef _MUL_GF2N_H
#define _MUL_GF2N_H

#include "mul_gf2x.h"
/* Really important include for the definition of 
   __TRINOMIAL_GF2N__ and __PENTANOMIAL_GF2N__ */
#include "rem_gf2n.h"
#include "prefix_name.h"
#include "arch.h"
#include "parameters_HFE.h"
#include "tools_gf2n.h"
#include "macro.h"


/***********************************************************************/
/***********************************************************************/
/****** Mul in GF(2)[x] specialized in n-coefficients polynomials ******/
/***********************************************************************/
/***********************************************************************/


void PREFIX_NAME(mul_no_simd_gf2x_ref)(uint64_t C[NB_WORD_MUL],
                                       const uint64_t A[NB_WORD_GFqn],
                                       const uint64_t B[NB_WORD_GFqn]);
#define mul_no_simd_gf2x_ref PREFIX_NAME(mul_no_simd_gf2x_ref)


/***********************************************************************/
/***********************************************************************/
/********************** Choice of mul in GF(2)[x] **********************/
/***********************************************************************/
/***********************************************************************/


#define mul_no_simd_gf2x CONCAT(CONCAT_NB_BITS_MMUL_SUP(mul),_no_simd_gf2x)
#define pmul_gf2x CONCAT(CONCAT_NB_BITS_MMUL_SUP(pmul),_gf2x)

#if (NB_WORD_GFqn==1)
    #define pclmul_gf2x CONCAT(CONCAT_NB_BITS_MMUL_SUP(pclmul),_inlined_gf2x)
#else
    #define pclmul_gf2x CONCAT(CONCAT_NB_BITS_MMUL_SUP(pclmul),_gf2x)
#endif

/* This macro is used only in inv_gf2n.c */
#define MUL_GF2X CONCAT(CONCAT_NB_BITS_MUL_SUP(PCLMUL),_GF2X)


/* Choice of the multiplication in GF(2)[x] for the arithmetic in GF(2^n). */
#if (HFEn<33)
    /* The gf2x library has the priority when enabled. */
    #if ENABLED_GF2X&&defined(MODE_32_BITS)
        #define mul_gf2x(C,A,B) best_mul32_gf2x(C,A,B);
    #elif ENABLED_GF2X
        #define mul_gf2x(C,A,B) (*(C))=best_mul32_gf2x(*(A),*(B));
    #elif defined(MQSOFT_REF)
        #define mul_gf2x mul_no_simd_gf2x_ref
    #elif (!ENABLED_GF2X)&&(defined(ENABLED_PCLMUL))
        #define mul_gf2x(C,A,B) best_mul32_gf2x(*(C),*(A),*(B));
    #else
        #define mul_gf2x(C,A,B) (*(C))=best_mul32_gf2x(*(A),*(B));
    #endif
#else
    /* The gf2x library has the priority when enabled. */
    #if ENABLED_GF2X
        #define mul_gf2x CONCAT(CONCAT_NB_BITS_MUL_SUP(best_mul),_gf2x)
    #elif defined(MQSOFT_REF)
        #define mul_gf2x mul_no_simd_gf2x_ref
    #else
        #define mul_gf2x CONCAT(CONCAT_NB_BITS_MUL_SUP(best_mul),_gf2x)
    #endif
#endif


/***********************************************************************/
/***********************************************************************/
/************************* mul then rem version ************************/
/***********************************************************************/
/***********************************************************************/


/* Function mul in GF(2^x), then modular reduction */
#define MUL_THEN_REM_GF2N void \
            PREFIX_NAME(mul_then_rem_gf2n)(uint64_t res[NB_WORD_GFqn], \
                                    const uint64_t A[NB_WORD_GFqn], \
                                    const uint64_t B[NB_WORD_GFqn])
MUL_THEN_REM_GF2N;
#define mul_then_rem_gf2n PREFIX_NAME(mul_then_rem_gf2n)


/***********************************************************************/
/***********************************************************************/
/********************** Choice of mul in GF(2^n) ***********************/
/***********************************************************************/
/***********************************************************************/


/* Choice the best mul_gf2n */
#if (ENABLED_GF2X||defined(MQSOFT_REF))
    /* The gf2x library has the priority when enabled.
       In this case, the chosen muliplication is not necessarily the fastest. */
    #define mul_gf2n mul_then_rem_gf2n
#elif (HFEn<33)
    #define mul_gf2n mul_then_rem_gf2n
#else
    #define mul_gf2n mul_then_rem_gf2n
#endif



#endif

