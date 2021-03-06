#ifndef _REM_GF2X_H
#define _REM_GF2X_H

#include <stdint.h>
#include "prefix_name.h"
#include "xor.h"


/* Macros to compute the modular reduction with words of 64 bits */
/* Modular reduction by trinomial or pentanomial */
/* Trinomial: x^k + x^k3 + 1 */
/* Pentanomial: x^k + x^k3 + x^k2 + x^k1 + 1 */

/* Look rem_gf2x.c to know requirements of the macros */

/* To compute the variable mask, use the macro: mask32(k) or mask64(k&63) */


/* Here, P is the result, Pol is the input */
/* Q and R are not initialised */
/* Look rem.c to look an example of how use these macros */


#define REM32_TRINOMIAL_GF2X(P,Pol,k,k3,Q,R,mask) \
    Q=(Pol)>>k; \
    P=(Pol)^Q; \
    R=Q<<k3; \
    P^=R; \
    R>>=k; \
    P^=R; \
    P^=R<<k3; \
    P&=mask;


#define REM32_TRINOMIAL_GF2X_OLD(P,Pol,k,k3,Q,R,mask) \
    Q=(Pol)>>k; \
    R=(Pol)>>((k<<1)-k3); \
    Q^=R; \
    P=Pol; \
    P^=Q; \
    P^=Q<<k3; \
    P&=mask;


/* For K3==1 */
#define REM32_TRINOMIAL_K31_GF2X(P,Pol,k,k3,Q,R,mask) \
    Q=(Pol)>>k; \
    P=((Pol)&mask)^Q^(Q<<1);


#define REM32_TRINOMIAL_K312_GF2X(P,Pol,k,k3,Q,R,mask) \
    Q=(Pol)>>k; \
    P=(Pol)&mask; \
    P^=Q; \
    P^=Q<<1;


#define REM32_TRINOMIAL_K3_1_GF2X(P,Pol,k,Q,mask) \
            REM32_TRINOMIAL_K31_GF2X(P,Pol,k,k3,Q,R,mask)


#define REM32_PENTANOMIAL_GF2X_OLD(P,Pol,k,k1,k2,k3,Q,R,mask) \
    Q=(Pol)>>k; \
    P=(Pol)&mask; \
    P^=Q; \
    P^=Q<<k1; \
    P^=Q<<k2; \
    P^=Q<<k3; \
    R=P>>k; \
    P^=R; \
    P^=R<<k1; \
    P^=R<<k2; \
    P^=R<<k3; \
    P&=mask;


#define REM32_PENTANOMIAL_GF2X(P,Pol,k,k1,k2,k3,Q,R,mask) \
    Q=(Pol)>>k; \
    R=(Pol)>>((k<<1)-k1); \
    R^=(Pol)>>((k<<1)-k2); \
    R^=(Pol)>>((k<<1)-k3); \
    Q^=R; \
    P=Pol; \
    P^=Q; \
    P^=Q<<k1; \
    P^=Q<<k2; \
    P^=Q<<k3; \
    P&=mask;


/* For K1==1 */
#define REM32_PENTANOMIAL_K1_1_GF2X(P,Pol,k,k1,k2,k3,Q,mask) \
    Q=(Pol)>>k; \
    Q^=(Pol)>>((k<<1)-k2); \
    Q^=(Pol)>>((k<<1)-k3); \
    P=Pol; \
    P^=Q; \
    P^=Q<<k1; \
    P^=Q<<k2; \
    P^=Q<<k3; \
    P&=mask;


#define REM64_TRINOMIAL_GF2X(P,Pol,k,k3,Q,R,mask) \
    Q=((Pol)[0]>>k)^((Pol)[1]<<(64-k)); \
    R=Q>>(k-k3); \
    Q^=R; \
    P=(Pol)[0]^Q; \
    P^=Q<<k3; \
    P&=mask;


/* K3==1 */
#define REM64_TRINOMIAL_GF2X_K31(P,Pol,k,k3,Q,R,mask) \
    Q=((Pol)[0]>>k)^((Pol)[1]<<(64-k)); \
    P=(Pol)[0]^Q^(Q<<k3);\
    P&=mask;


#define REM64_PENTANOMIAL_GF2X(P,Pol,k,k1,k2,k3,Q,R,mask) \
    Q=((Pol)[0]>>k)^((Pol)[1]<<(64-k)); \
    P=(Pol)[0]^Q; \
    P^=Q<<k1; \
    P^=Q<<k2; \
    P^=Q<<k3; \
    R=Q>>(k-k1); \
    R^=Q>>(k-k2); \
    R^=Q>>(k-k3); \
    P^=R; \
    P^=R<<k1; \
    P^=R<<k2; \
    P^=R<<k3; \
    P&=mask;


/* Special case k==64 */
#define REM64_PENTANOMIAL_K64_GF2X(P,Pol,k,k1,k2,k3,R) \
    P=(Pol)[0]^(Pol)[1];\
    P^=(Pol)[1]<<k1; \
    P^=(Pol)[1]<<k2; \
    P^=(Pol)[1]<<k3; \
    R=(Pol)[1]>>(k-k1); \
    R^=(Pol)[1]>>(k-k2); \
    R^=(Pol)[1]>>(k-k3); \
    P^=R; \
    P^=R<<k1; \
    P^=R<<k2; \
    P^=R<<k3;


#define MACRO_128_TRINOMIAL_GF2X(ROW1,ROW2,P,Pol,k3,ki,Q,R,mask) \
    /* x^k = x^k3 + 1 */\
    ROW1;\
    ROW2;\
    /* x^k = 1 */\
    XOR2(P,Pol,Q);\
    /* x^k = x^k3 */\
    (P)[0]^=Q[0]<<k3;\
    (P)[1]^=(Q[0]>>(64-k3))^(Q[1]<<k3);\
    /* x^k = x^k3 + 1 */\
    R=(ki>=k3)?Q[1]>>(ki-k3):(Q[0]>>(64-(k3-ki)))^(Q[1]<<(k3-ki));\
    /* x^k = 1 */\
    (P)[0]^=R;\
    /* x^k = x^k3 */\
    (P)[0]^=R<<k3;\
    (P)[1]&=mask;

#define REM96_TRINOMIAL_GF2X(P,Pol,k3,ki,Q,R,mask) \
    MACRO_128_TRINOMIAL_GF2X(Q[0]=((Pol)[1]>>ki)^((Pol)[2]<<(64-ki)),\
                             Q[1]=(Pol)[2]>>ki,P,Pol,k3,ki,Q,R,mask)

#define REM128_TRINOMIAL_GF2X(P,Pol,k3,ki,ki64,Q,R,mask) \
    MACRO_128_TRINOMIAL_GF2X(Q[0]=((Pol)[1]>>ki)^((Pol)[2]<<(ki64)),\
                             Q[1]=((Pol)[2]>>ki)^((Pol)[3]<<ki64),\
                             P,Pol,k3,ki,Q,R,mask)


#define MACRO_128_PENTANOMIAL_GF2X(ROW1,ROW2,P,Pol,k1,k2,k3,ki,ki64,Q,R,mask) \
    /* x^k = x^k3 + x^k2 + x^k1 + 1 */\
    ROW1;\
    ROW2;\
    /* x^k = 1 */\
    XOR2(P,Pol,Q);\
    /* x^k = x^k1 */\
    (P)[0]^=Q[0]<<k1;\
    (P)[1]^=(Q[0]>>(64-k1))^(Q[1]<<k1);\
    /* x^k = x^k2 */\
    (P)[0]^=Q[0]<<k2;\
    (P)[1]^=(Q[0]>>(64-k2))^(Q[1]<<k2);\
    /* x^k = x^k3 */\
    (P)[0]^=Q[0]<<k3;\
    (P)[1]^=(Q[0]>>(64-k3))^(Q[1]<<k3);\
    /* x^k = x^k3 + x^k2 + x^k1 + 1 */\
    R=(ki>=k3)?Q[1]>>(ki-k3):(Q[0]>>(64-(k3-ki)))^(Q[1]<<(k3-ki));\
    R^=(ki>=k2)?Q[1]>>(ki-k2):(Q[0]>>(64-(k2-ki)))^(Q[1]<<(k2-ki));\
    R^=(ki>=k1)?Q[1]>>(ki-k1):(Q[0]>>(64-(k1-ki)))^(Q[1]<<(k1-ki));\
    /* x^k = 1 */\
    (P)[0]^=R;\
    /* x^k = x^k1 */\
    (P)[0]^=R<<k1;\
    /* x^k = x^k2 */\
    (P)[0]^=R<<k2;\
    /* x^k = x^k3 */\
    (P)[0]^=R<<k3;\
    (P)[1]&=mask;

#define REM96_PENTANOMIAL_GF2X(P,Pol,k1,k2,k3,ki,Q,R,mask) \
    MACRO_128_PENTANOMIAL_GF2X(Q[0]=((Pol)[1]>>ki)^((Pol)[2]<<(64-ki)),\
                               Q[1]=((Pol)[2]>>ki),P,Pol,k1,k2,k3,ki,,Q,R,mask)

#define REM128_PENTANOMIAL_GF2X(P,Pol,k1,k2,k3,ki,ki64,Q,R,mask) \
    MACRO_128_PENTANOMIAL_GF2X(Q[0]=((Pol)[1]>>ki)^((Pol)[2]<<ki64),\
                               Q[1]=((Pol)[2]>>ki)^((Pol)[3]<<ki64),\
                               P,Pol,k1,k2,k3,ki,ki64,Q,R,mask)


/* Special case k==128 */
#define REM128_PENTANOMIAL_K128_GF2X(P,Pol,k1,k2,k3,R) \
    XOR2(P,Pol,Pol+2);\
    (P)[0]^=(Pol)[2]<<k1;\
    (P)[1]^=((Pol)[2]>>(64-k1))^((Pol)[3]<<k1);\
    (P)[0]^=(Pol)[2]<<k2;\
    (P)[1]^=((Pol)[2]>>(64-k2))^((Pol)[3]<<k2);\
    (P)[0]^=(Pol)[2]<<k3;\
    (P)[1]^=((Pol)[2]>>(64-k3))^((Pol)[3]<<k3);\
    R=(Pol)[3]>>(64-k3);\
    R^=(Pol)[3]>>(64-k2);\
    /* Useless if k1==1 */\
    R^=(Pol)[3]>>(64-k1);\
    (P)[0]^=R;\
    (P)[0]^=R<<k1;\
    (P)[0]^=R<<k2;\
    (P)[0]^=R<<k3;


#define MACRO_192_TRINOMIAL_GF2X(ROW,P,Pol,k3,ki,ki64,k364,Q,R,mask) \
    Q[0]=((Pol)[2]>>ki)^((Pol)[3]<<ki64);\
    Q[1]=((Pol)[3]>>ki)^((Pol)[4]<<ki64);\
    ROW;\
    XOR3(P,Pol,Q);\
    (P)[0]^=Q[0]<<k3;\
    (P)[1]^=(Q[0]>>k364)^(Q[1]<<k3);\
    (P)[2]^=(Q[1]>>k364)^(Q[2]<<k3);\
    /* 64-(k364+ki) == (k3-ki) */\
    R=(ki>=k3)?Q[2]>>(ki-k3):(Q[1]>>(k364+ki))^(Q[2]<<(k3-ki));\
    (P)[0]^=R;\
    (P)[0]^=R<<k3;\
    (P)[2]&=mask;

#define REM160_TRINOMIAL_GF2X(P,Pol,k3,ki,ki64,k364,Q,R,mask) \
    MACRO_192_TRINOMIAL_GF2X(Q[2]=(Pol)[4]>>ki,P,Pol,k3,ki,ki64,k364,Q,R,mask)

#define REM192_TRINOMIAL_GF2X(P,Pol,k3,ki,ki64,k364,Q,R,mask) \
    MACRO_192_TRINOMIAL_GF2X(Q[2]=((Pol)[4]>>ki)^((Pol)[5]<<ki64),\
                             P,Pol,k3,ki,ki64,k364,Q,R,mask)


#define MACRO_192_PENTANOMIAL_GF2X(ROW,P,Pol,k1,k2,k3,ki,ki64,\
                                   k164,k264,k364,Q,R,mask) \
    Q[0]=((Pol)[2]>>ki)^((Pol)[3]<<ki64);\
    Q[1]=((Pol)[3]>>ki)^((Pol)[4]<<ki64);\
    ROW;\
    XOR3(P,Pol,Q);\
    (P)[0]^=Q[0]<<k1;\
    (P)[1]^=(Q[0]>>k164)^(Q[1]<<k1);\
    (P)[2]^=(Q[1]>>k164)^(Q[2]<<k1);\
    (P)[0]^=Q[0]<<k2;\
    (P)[1]^=(Q[0]>>k264)^(Q[1]<<k2);\
    (P)[2]^=(Q[1]>>k264)^(Q[2]<<k2);\
    (P)[0]^=Q[0]<<k3;\
    (P)[1]^=(Q[0]>>k364)^(Q[1]<<k3);\
    (P)[2]^=(Q[1]>>k364)^(Q[2]<<k3);\
    /* 64-(k364+ki) == (k3-ki) */\
    R=(ki>=k3)?Q[2]>>(ki-k3):(Q[1]>>(k364+ki))^(Q[2]<<(k3-ki));\
    R^=(ki>=k2)?Q[2]>>(ki-k2):(Q[1]>>(k264+ki))^(Q[2]<<(k2-ki));\
    R^=(ki>=k1)?Q[2]>>(ki-k1):(Q[1]>>(k164+ki))^(Q[2]<<(k1-ki));\
    (P)[0]^=R;\
    (P)[0]^=R<<k1;\
    (P)[0]^=R<<k2;\
    (P)[0]^=R<<k3;\
    (P)[2]&=mask;

#define REM160_PENTANOMIAL_GF2X(P,Pol,k1,k2,k3,ki,ki64,k164,k264,k364,Q,R,mask)\
    MACRO_192_PENTANOMIAL_GF2X(Q[2]=((Pol)[4]>>ki),\
                               P,Pol,k1,k2,k3,ki,ki64,k164,k264,k364,Q,R,mask)

#define REM192_PENTANOMIAL_GF2X(P,Pol,k1,k2,k3,ki,ki64,k164,k264,k364,Q,R,mask)\
    MACRO_192_PENTANOMIAL_GF2X(Q[2]=((Pol)[4]>>ki)^((Pol)[5]<<ki64),\
                               P,Pol,k1,k2,k3,ki,ki64,k164,k264,k364,Q,R,mask)


/* Special case k==192 */
#define REM192_PENTANOMIAL_K192_GF2X(P,Pol,k1,k2,k3,k164,k264,k364,R) \
    XOR3(P,Pol,Pol+3);\
    (P)[0]^=(Pol)[3]<<k1;\
    (P)[1]^=((Pol)[3]>>k164)^((Pol)[4]<<k1);\
    (P)[2]^=((Pol)[4]>>k164)^((Pol)[5]<<k1);\
    (P)[0]^=(Pol)[3]<<k2;\
    (P)[1]^=((Pol)[3]>>k264)^((Pol)[4]<<k2);\
    (P)[2]^=((Pol)[4]>>k264)^((Pol)[5]<<k2);\
    (P)[0]^=(Pol)[3]<<k3;\
    (P)[1]^=((Pol)[3]>>k364)^((Pol)[4]<<k3);\
    (P)[2]^=((Pol)[4]>>k364)^((Pol)[5]<<k3);\
    R=(Pol)[5]>>k364;\
    R^=(Pol)[5]>>k264;\
    /* Useless if k1==1 */\
    R^=(Pol)[5]>>k164;\
    (P)[0]^=R;\
    (P)[0]^=R<<k1;\
    (P)[0]^=R<<k2;\
    (P)[0]^=R<<k3;


#define MACRO_256_TRINOMIAL_GF2X(ROW,P,Pol,k3,ki,ki64,k364,Q,R,mask) \
    Q[0]=((Pol)[3]>>ki)^((Pol)[4]<<ki64);\
    Q[1]=((Pol)[4]>>ki)^((Pol)[5]<<ki64);\
    Q[2]=((Pol)[5]>>ki)^((Pol)[6]<<ki64);\
    ROW;\
    XOR4(P,Pol,Q);\
    (P)[0]^=Q[0]<<k3;\
    (P)[1]^=(Q[0]>>k364)^(Q[1]<<k3);\
    (P)[2]^=(Q[1]>>k364)^(Q[2]<<k3);\
    (P)[3]^=(Q[2]>>k364)^(Q[3]<<k3);\
    /* 64-(k364+ki) == (k3-ki) */\
    R=(ki>=k3)?Q[3]>>(ki-k3):(Q[2]>>(k364+ki))^(Q[3]<<(k3-ki));\
    (P)[0]^=R;\
    (P)[0]^=R<<k3;\
    (P)[3]&=mask;

#define REM224_TRINOMIAL_GF2X(P,Pol,k3,ki,ki64,k364,Q,R,mask) \
    MACRO_256_TRINOMIAL_GF2X(Q[3]=(Pol)[6]>>ki,P,Pol,k3,ki,ki64,k364,Q,R,mask)

#define REM256_TRINOMIAL_GF2X(P,Pol,k3,ki,ki64,k364,Q,R,mask) \
    MACRO_256_TRINOMIAL_GF2X(Q[3]=((Pol)[6]>>ki)^((Pol)[7]<<ki64),\
                             P,Pol,k3,ki,ki64,k364,Q,R,mask)


#define MACRO_256_PENTANOMIAL_GF2X(ROW,P,Pol,k1,k2,k3,ki,ki64,\
                                   k164,k264,k364,Q,R,mask) \
    Q[0]=((Pol)[3]>>ki)^((Pol)[4]<<ki64);\
    Q[1]=((Pol)[4]>>ki)^((Pol)[5]<<ki64);\
    Q[2]=((Pol)[5]>>ki)^((Pol)[6]<<ki64);\
    ROW;\
    XOR4(P,Pol,Q);\
    (P)[0]^=Q[0]<<k1;\
    (P)[1]^=(Q[0]>>k164)^(Q[1]<<k1);\
    (P)[2]^=(Q[1]>>k164)^(Q[2]<<k1);\
    (P)[3]^=(Q[2]>>k164)^(Q[3]<<k1);\
    (P)[0]^=Q[0]<<k2;\
    (P)[1]^=(Q[0]>>k264)^(Q[1]<<k2);\
    (P)[2]^=(Q[1]>>k264)^(Q[2]<<k2);\
    (P)[3]^=(Q[2]>>k264)^(Q[3]<<k2);\
    (P)[0]^=Q[0]<<k3;\
    (P)[1]^=(Q[0]>>k364)^(Q[1]<<k3);\
    (P)[2]^=(Q[1]>>k364)^(Q[2]<<k3);\
    (P)[3]^=(Q[2]>>k364)^(Q[3]<<k3);\
    /* 64-(k364+ki) == (k3-ki) */\
    R=(ki>=k3)?Q[3]>>(ki-k3):(Q[2]>>(k364+ki))^(Q[3]<<(k3-ki));\
    R^=(ki>=k2)?Q[3]>>(ki-k2):(Q[2]>>(k264+ki))^(Q[3]<<(k2-ki));\
    R^=(ki>=k1)?Q[3]>>(ki-k1):(Q[2]>>(k164+ki))^(Q[3]<<(k1-ki));\
    (P)[0]^=R;\
    (P)[0]^=R<<k1;\
    (P)[0]^=R<<k2;\
    (P)[0]^=R<<k3;\
    (P)[3]&=mask;

#define REM224_PENTANOMIAL_GF2X(P,Pol,k1,k2,k3,ki,ki64,k164,k264,k364,Q,R,mask)\
    MACRO_256_PENTANOMIAL_GF2X(Q[3]=((Pol)[6]>>ki),\
                               P,Pol,k1,k2,k3,ki,ki64,k164,k264,k364,Q,R,mask)

#define REM256_PENTANOMIAL_GF2X(P,Pol,k1,k2,k3,ki,ki64,k164,k264,k364,Q,R,mask)\
    MACRO_256_PENTANOMIAL_GF2X(Q[3]=((Pol)[6]>>ki)^((Pol)[7]<<ki64),\
                               P,Pol,k1,k2,k3,ki,ki64,k164,k264,k364,Q,R,mask)


/* Special case k==256 */
#define REM256_PENTANOMIAL_K256_GF2X(P,Pol,k1,k2,k3,k164,k264,k364,R) \
    XOR4(P,Pol,Pol+4);\
    (P)[0]^=(Pol)[4]<<k1;\
    (P)[1]^=((Pol)[4]>>k164)^((Pol)[5]<<k1);\
    (P)[2]^=((Pol)[5]>>k164)^((Pol)[6]<<k1);\
    (P)[3]^=((Pol)[6]>>k164)^((Pol)[7]<<k1);\
    (P)[0]^=(Pol)[4]<<k2;\
    (P)[1]^=((Pol)[4]>>k264)^((Pol)[5]<<k2);\
    (P)[2]^=((Pol)[5]>>k264)^((Pol)[6]<<k2);\
    (P)[3]^=((Pol)[6]>>k264)^((Pol)[7]<<k2);\
    (P)[0]^=(Pol)[4]<<k3;\
    (P)[1]^=((Pol)[4]>>k364)^((Pol)[5]<<k3);\
    (P)[2]^=((Pol)[5]>>k364)^((Pol)[6]<<k3);\
    (P)[3]^=((Pol)[6]>>k364)^((Pol)[7]<<k3);\
    R=(Pol)[7]>>k364;\
    R^=(Pol)[7]>>k264;\
    /* Useless if k1==1 */\
    R^=(Pol)[7]>>k164;\
    (P)[0]^=R;\
    (P)[0]^=R<<k1;\
    (P)[0]^=R<<k2;\
    (P)[0]^=R<<k3;


#define MACRO_320_TRINOMIAL_GF2X(ROW,P,Pol,k3,ki,ki64,k364,Q,R,mask) \
    Q[0]=((Pol)[4]>>ki)^((Pol)[5]<<ki64);\
    Q[1]=((Pol)[5]>>ki)^((Pol)[6]<<ki64);\
    Q[2]=((Pol)[6]>>ki)^((Pol)[7]<<ki64);\
    Q[3]=((Pol)[7]>>ki)^((Pol)[8]<<ki64);\
    ROW;\
    XOR5(P,Pol,Q);\
    (P)[0]^=Q[0]<<k3;\
    (P)[1]^=(Q[0]>>k364)^(Q[1]<<k3);\
    (P)[2]^=(Q[1]>>k364)^(Q[2]<<k3);\
    (P)[3]^=(Q[2]>>k364)^(Q[3]<<k3);\
    (P)[4]^=(Q[3]>>k364)^(Q[4]<<k3);\
    /* 64-(k364+ki) == (k3-ki) */\
    R=(ki>=k3)?Q[4]>>(ki-k3):(Q[3]>>(k364+ki))^(Q[4]<<(k3-ki));\
    (P)[0]^=R;\
    (P)[0]^=R<<k3;\
    (P)[4]&=mask;

#define REM288_TRINOMIAL_GF2X(P,Pol,k3,ki,ki64,k364,Q,R,mask) \
    MACRO_320_TRINOMIAL_GF2X(Q[4]=((Pol)[8]>>ki),P,Pol,k3,ki,ki64,k364,Q,R,mask)

#define REM320_TRINOMIAL_GF2X(P,Pol,k3,ki,ki64,k364,Q,R,mask) \
    MACRO_320_TRINOMIAL_GF2X(Q[4]=((Pol)[8]>>ki)^((Pol)[9]<<ki64),\
                             P,Pol,k3,ki,ki64,k364,Q,R,mask)


/* Specialized rem for K3<64 */
#define REM288_SPECIALIZED_TRINOMIAL_GF2X(P,Pol,k3,ki,ki64,k364,Q,R,mask) \
    Q[0]=((Pol)[4]>>ki)^((Pol)[5]<<ki64);\
    Q[1]=((Pol)[5]>>ki)^((Pol)[6]<<ki64);\
    Q[2]=((Pol)[6]>>ki)^((Pol)[7]<<ki64);\
    Q[3]=((Pol)[7]>>ki)^((Pol)[8]<<ki64);\
    Q[4]=((Pol)[8]>>ki);\
    XOR5(P,Pol,Q);\
    (P)[0]^=Q[0]<<k3;\
    (P)[1]^=(Q[0]>>k364)^(Q[1]<<k3);\
    (P)[2]^=(Q[1]>>k364)^(Q[2]<<k3);\
    (P)[3]^=(Q[2]>>k364)^(Q[3]<<k3);\
    (P)[4]^=(Q[3]>>k364)^(Q[4]<<k3);\
    /* 64-(k364+ki) == (k3-ki) */\
    R=(ki>=k3)?Q[4]>>(ki-k3):(Q[3]>>(k364+ki))^(Q[4]<<(k3-ki));\
    (P)[0]^=R;\
    (P)[0]^=R<<k3;\
    /* This row is the unique difference with REM288_TRINOMIAL_GF2X */\
    (P)[1]^=R>>k364;\
    (P)[4]&=mask;


/* Requirement: k=313, and give k3=k3&63 */
#define REM320_SPECIALIZED_TRINOMIAL_GF2X(P,Pol,k3,ki,ki64,k364,Q,R,mask) \
    {uint64_t R2;\
    Q[0]=((Pol)[4]>>ki)^((Pol)[5]<<ki64);\
    Q[1]=((Pol)[5]>>ki)^((Pol)[6]<<ki64);\
    Q[2]=((Pol)[6]>>ki)^((Pol)[7]<<ki64);\
    Q[3]=((Pol)[7]>>ki)^((Pol)[8]<<ki64);\
    Q[4]=((Pol)[8]>>ki)^((Pol)[9]<<ki64);\
    XOR5(P,Pol,Q);\
    /* 64-(k364+ki) == (k3-ki) */\
    R=(Q[3]>>(ki-k3))^(Q[4]<<(ki64+k3));\
    (P)[0]^=R;\
    R2=Q[4]>>(ki-k3);\
    (P)[1]^=R2;\
    (P)[1]^=(R^Q[0])<<k3;\
    (P)[2]^=((R^Q[0])>>k364)^((R2^Q[1])<<k3);\
    (P)[3]^=((R2^Q[1])>>k364)^(Q[2]<<k3);\
    (P)[4]^=(Q[2]>>k364)^(Q[3]<<k3);\
    (P)[4]&=mask;}


#define MACRO_320_PENTANOMIAL_GF2X(ROW,P,Pol,k1,k2,k3,ki,ki64,\
                                   k164,k264,k364,Q,R,mask) \
    Q[0]=((Pol)[4]>>ki)^((Pol)[5]<<ki64);\
    Q[1]=((Pol)[5]>>ki)^((Pol)[6]<<ki64);\
    Q[2]=((Pol)[6]>>ki)^((Pol)[7]<<ki64);\
    Q[3]=((Pol)[7]>>ki)^((Pol)[8]<<ki64);\
    ROW;\
    XOR5(P,Pol,Q);\
    (P)[0]^=Q[0]<<k1;\
    (P)[1]^=(Q[0]>>k164)^(Q[1]<<k1);\
    (P)[2]^=(Q[1]>>k164)^(Q[2]<<k1);\
    (P)[3]^=(Q[2]>>k164)^(Q[3]<<k1);\
    (P)[4]^=(Q[3]>>k164)^(Q[4]<<k1);\
    (P)[0]^=Q[0]<<k2;\
    (P)[1]^=(Q[0]>>k264)^(Q[1]<<k2);\
    (P)[2]^=(Q[1]>>k264)^(Q[2]<<k2);\
    (P)[3]^=(Q[2]>>k264)^(Q[3]<<k2);\
    (P)[4]^=(Q[3]>>k264)^(Q[4]<<k2);\
    (P)[0]^=Q[0]<<k3;\
    (P)[1]^=(Q[0]>>k364)^(Q[1]<<k3);\
    (P)[2]^=(Q[1]>>k364)^(Q[2]<<k3);\
    (P)[3]^=(Q[2]>>k364)^(Q[3]<<k3);\
    (P)[4]^=(Q[3]>>k364)^(Q[4]<<k3);\
    /* 64-(k364+ki) == (k3-ki) */\
    R=(ki>=k3)?Q[4]>>(ki-k3):(Q[3]>>(k364+ki))^(Q[4]<<(k3-ki));\
    R^=(ki>=k2)?Q[4]>>(ki-k2):(Q[3]>>(k264+ki))^(Q[4]<<(k2-ki));\
    R^=(ki>=k1)?Q[4]>>(ki-k1):(Q[3]>>(k164+ki))^(Q[4]<<(k1-ki));\
    (P)[0]^=R;\
    (P)[0]^=R<<k1;\
    (P)[0]^=R<<k2;\
    (P)[0]^=R<<k3;\
    (P)[4]&=mask;

#define REM288_PENTANOMIAL_GF2X(P,Pol,k1,k2,k3,ki,ki64,k164,k264,k364,Q,R,mask)\
    MACRO_320_PENTANOMIAL_GF2X(Q[4]=((Pol)[8]>>ki),\
                               P,Pol,k1,k2,k3,ki,ki64,k164,k264,k364,Q,R,mask)

#define REM320_PENTANOMIAL_GF2X(P,Pol,k1,k2,k3,ki,ki64,k164,k264,k364,Q,R,mask)\
    MACRO_320_PENTANOMIAL_GF2X(Q[4]=((Pol)[8]>>ki)^((Pol)[9]<<ki64),\
                               P,Pol,k1,k2,k3,ki,ki64,k164,k264,k364,Q,R,mask)


/* Special case k==320 */
#define REM320_PENTANOMIAL_K320_GF2X(P,Pol,k1,k2,k3,k164,k264,k364,R) \
    XOR5(P,Pol,Pol+5);\
    (P)[0]^=(Pol)[5]<<k1;\
    (P)[1]^=((Pol)[5]>>k164)^((Pol)[6]<<k1);\
    (P)[2]^=((Pol)[6]>>k164)^((Pol)[7]<<k1);\
    (P)[3]^=((Pol)[7]>>k164)^((Pol)[8]<<k1);\
    (P)[4]^=((Pol)[8]>>k164)^((Pol)[9]<<k1);\
    (P)[0]^=(Pol)[5]<<k2;\
    (P)[1]^=((Pol)[5]>>k264)^((Pol)[6]<<k2);\
    (P)[2]^=((Pol)[6]>>k264)^((Pol)[7]<<k2);\
    (P)[3]^=((Pol)[7]>>k264)^((Pol)[8]<<k2);\
    (P)[4]^=((Pol)[8]>>k264)^((Pol)[9]<<k2);\
    (P)[0]^=(Pol)[5]<<k3;\
    (P)[1]^=((Pol)[5]>>k364)^((Pol)[6]<<k3);\
    (P)[2]^=((Pol)[6]>>k364)^((Pol)[7]<<k3);\
    (P)[3]^=((Pol)[7]>>k364)^((Pol)[8]<<k3);\
    (P)[4]^=((Pol)[8]>>k364)^((Pol)[9]<<k3);\
    R=(Pol)[9]>>k364;\
    R^=(Pol)[9]>>k264;\
    /* Useless if k1==1 */\
    R^=(Pol)[9]>>k164;\
    (P)[0]^=R;\
    (P)[0]^=R<<k1;\
    (P)[0]^=R<<k2;\
    (P)[0]^=R<<k3;


/* Special case k==312 and k3=128 */
#define REM312_PENTANOMIAL_K3_IS_128_GF2X(P,Pol,k1,k2,k3,ki,ki64,\
                                          k164,k264,k364,Q,R,mask) \
    Q[0]=((Pol)[4]>>ki)^((Pol)[5]<<ki64);\
    Q[1]=((Pol)[5]>>ki)^((Pol)[6]<<ki64);\
    Q[2]=((Pol)[6]>>ki)^((Pol)[7]<<ki64);\
    Q[3]=((Pol)[7]>>ki)^((Pol)[8]<<ki64);\
    Q[4]=((Pol)[8]>>ki)^((Pol)[9]<<ki64);\
    /* R for K1=5 */\
    Q[0]^=(Q)[4]>>51;\
    /* R for K2=15 */\
    Q[0]^=(Q)[4]>>41;\
    /* R for K3=128 */\
    Q[0]^=((Pol)[7]>>48)^(Pol[8]<<16);\
    Q[1]^=((Pol)[8]>>48)^(Pol[9]<<16);\
    XOR5(P,Pol,Q);\
    /* K3=128 */\
    (P)[2]^=Q[0];\
    (P)[3]^=Q[1];\
    (P)[4]^=Q[2];\
    (P)[0]^=Q[0]<<k1;\
    (P)[1]^=(Q[0]>>k164)^(Q[1]<<k1);\
    (P)[2]^=(Q[1]>>k164)^(Q[2]<<k1);\
    (P)[3]^=(Q[2]>>k164)^(Q[3]<<k1);\
    (P)[4]^=(Q[3]>>k164)^(Q[4]<<k1);\
    (P)[0]^=Q[0]<<k2;\
    (P)[1]^=(Q[0]>>k264)^(Q[1]<<k2);\
    (P)[2]^=(Q[1]>>k264)^(Q[2]<<k2);\
    (P)[3]^=(Q[2]>>k264)^(Q[3]<<k2);\
    (P)[4]^=(Q[3]>>k264)^(Q[4]<<k2);\
    (P)[4]&=mask;


#define MACRO_384_TRINOMIAL_GF2X(ROW,P,Pol,k3,ki,ki64,k364,Q,R,mask) \
    Q[0]=((Pol)[5]>>ki)^((Pol)[6]<<ki64);\
    Q[1]=((Pol)[6]>>ki)^((Pol)[7]<<ki64);\
    Q[2]=((Pol)[7]>>ki)^((Pol)[8]<<ki64);\
    Q[3]=((Pol)[8]>>ki)^((Pol)[9]<<ki64);\
    Q[4]=((Pol)[9]>>ki)^((Pol)[10]<<ki64);\
    ROW;\
    XOR6(P,Pol,Q);\
    (P)[0]^=Q[0]<<k3;\
    (P)[1]^=(Q[0]>>k364)^(Q[1]<<k3);\
    (P)[2]^=(Q[1]>>k364)^(Q[2]<<k3);\
    (P)[3]^=(Q[2]>>k364)^(Q[3]<<k3);\
    (P)[4]^=(Q[3]>>k364)^(Q[4]<<k3);\
    (P)[5]^=(Q[4]>>k364)^(Q[5]<<k3);\
    /* 64-(k364+ki) == (k3-ki) */\
    R=(ki>=k3)?Q[5]>>(ki-k3):(Q[4]>>(k364+ki))^(Q[5]<<(k3-ki));\
    (P)[0]^=R;\
    (P)[0]^=R<<k3;\
    (P)[5]&=mask;

#define REM352_TRINOMIAL_GF2X(P,Pol,k3,ki,ki64,k364,Q,R,mask) \
    MACRO_384_TRINOMIAL_GF2X(Q[5]=((Pol)[10]>>ki),\
                             P,Pol,k3,ki,ki64,k364,Q,R,mask)

#define REM384_TRINOMIAL_GF2X(P,Pol,k3,ki,ki64,k364,Q,R,mask) \
    MACRO_384_TRINOMIAL_GF2X(Q[5]=((Pol)[10]>>ki)^((Pol)[11]<<ki64),\
                             P,Pol,k3,ki,ki64,k364,Q,R,mask)


#define REM384_SPECIALIZED358_TRINOMIAL_GF2X(P,Pol,k3,ki,ki64,k364,Q,R,mask) \
    Q[0]=((Pol)[5]>>ki)^((Pol)[6]<<ki64);\
    Q[1]=((Pol)[6]>>ki)^((Pol)[7]<<ki64);\
    Q[2]=((Pol)[7]>>ki)^((Pol)[8]<<ki64);\
    Q[3]=((Pol)[8]>>ki)^((Pol)[9]<<ki64);\
    Q[4]=((Pol)[9]>>ki)^((Pol)[10]<<ki64);\
    Q[5]=((Pol)[10]>>ki)^((Pol)[11]<<ki64);\
    /* 64-(k364+ki) == (k3-ki) */\
    R=(Q[4]>>(k364+ki))^(Q[5]<<(k3-ki));\
    Q[0]^=R;\
    XOR6(P,Pol,Q);\
    (P)[0]^=Q[0]<<k3;\
    (P)[1]^=(Q[0]>>k364)^(Q[1]<<k3);\
    (P)[2]^=(Q[1]>>k364)^(Q[2]<<k3);\
    (P)[3]^=(Q[2]>>k364)^(Q[3]<<k3);\
    (P)[4]^=(Q[3]>>k364)^(Q[4]<<k3);\
    (P)[5]^=(Q[4]>>k364);\
    (P)[5]&=mask;


/* Requirement: k=354, and give k3=k3&63 */
#define REM384_SPECIALIZED_TRINOMIAL_GF2X(P,Pol,k3,ki,ki64,k364,Q,R,mask) \
    {uint64_t R2;\
    Q[0]=((Pol)[5]>>ki)^((Pol)[6]<<ki64);\
    Q[1]=((Pol)[6]>>ki)^((Pol)[7]<<ki64);\
    Q[2]=((Pol)[7]>>ki)^((Pol)[8]<<ki64);\
    Q[3]=((Pol)[8]>>ki)^((Pol)[9]<<ki64);\
    Q[4]=((Pol)[9]>>ki)^((Pol)[10]<<ki64);\
    Q[5]=((Pol)[10]>>ki)^((Pol)[11]<<ki64);\
    XOR6(P,Pol,Q);\
    /* 64-(k364+ki) == (k3-ki) */\
    R=(Q[3]>>(k364+ki))^(Q[4]<<(k3-ki));\
    (P)[0]^=R;\
    R2=(Q[4]>>(k364+ki))^(Q[5]<<(k3-ki));\
    (P)[1]^=R2;\
    (P)[1]^=(R^Q[0])<<k3;\
    (P)[2]^=((R^Q[0])>>k364)^((R2^Q[1])<<k3);\
    (P)[3]^=((R2^Q[1])>>k364)^(Q[2]<<k3);\
    (P)[4]^=(Q[2]>>k364)^(Q[3]<<k3);\
    (P)[5]^=Q[3]>>k364;\
    (P)[5]&=mask;}


#define MACRO_384_PENTANOMIAL_GF2X(ROW,P,Pol,k1,k2,k3,ki,ki64,\
                                   k164,k264,k364,Q,R,mask) \
    Q[0]=((Pol)[5]>>ki)^((Pol)[6]<<ki64);\
    Q[1]=((Pol)[6]>>ki)^((Pol)[7]<<ki64);\
    Q[2]=((Pol)[7]>>ki)^((Pol)[8]<<ki64);\
    Q[3]=((Pol)[8]>>ki)^((Pol)[9]<<ki64);\
    Q[4]=((Pol)[9]>>ki)^((Pol)[10]<<ki64);\
    ROW;\
    XOR6(P,Pol,Q);\
    (P)[0]^=Q[0]<<k1;\
    (P)[1]^=(Q[0]>>k164)^(Q[1]<<k1);\
    (P)[2]^=(Q[1]>>k164)^(Q[2]<<k1);\
    (P)[3]^=(Q[2]>>k164)^(Q[3]<<k1);\
    (P)[4]^=(Q[3]>>k164)^(Q[4]<<k1);\
    (P)[5]^=(Q[4]>>k164)^(Q[5]<<k1);\
    (P)[0]^=Q[0]<<k2;\
    (P)[1]^=(Q[0]>>k264)^(Q[1]<<k2);\
    (P)[2]^=(Q[1]>>k264)^(Q[2]<<k2);\
    (P)[3]^=(Q[2]>>k264)^(Q[3]<<k2);\
    (P)[4]^=(Q[3]>>k264)^(Q[4]<<k2);\
    (P)[5]^=(Q[4]>>k264)^(Q[5]<<k2);\
    (P)[0]^=Q[0]<<k3;\
    (P)[1]^=(Q[0]>>k364)^(Q[1]<<k3);\
    (P)[2]^=(Q[1]>>k364)^(Q[2]<<k3);\
    (P)[3]^=(Q[2]>>k364)^(Q[3]<<k3);\
    (P)[4]^=(Q[3]>>k364)^(Q[4]<<k3);\
    (P)[5]^=(Q[4]>>k364)^(Q[5]<<k3);\
    /* 64-(k364+ki) == (k3-ki) */\
    R=(ki>=k3)?Q[5]>>(ki-k3):(Q[4]>>(k364+ki))^(Q[5]<<(k3-ki));\
    R^=(ki>=k2)?Q[5]>>(ki-k2):(Q[4]>>(k264+ki))^(Q[5]<<(k2-ki));\
    R^=(ki>=k1)?Q[5]>>(ki-k1):(Q[4]>>(k164+ki))^(Q[5]<<(k1-ki));\
    (P)[0]^=R;\
    (P)[0]^=R<<k1;\
    (P)[0]^=R<<k2;\
    (P)[0]^=R<<k3;\
    (P)[5]&=mask;

#define REM352_PENTANOMIAL_GF2X(P,Pol,k1,k2,k3,ki,ki64,k164,k264,k364,Q,R,mask)\
    MACRO_384_PENTANOMIAL_GF2X(Q[5]=((Pol)[10]>>ki),\
                               P,Pol,k1,k2,k3,ki,ki64,k164,k264,k364,Q,R,mask)

#define REM384_PENTANOMIAL_GF2X(P,Pol,k1,k2,k3,ki,ki64,k164,k264,k364,Q,R,mask)\
    MACRO_384_PENTANOMIAL_GF2X(Q[5]=((Pol)[10]>>ki)^((Pol)[11]<<ki64),\
                               P,Pol,k1,k2,k3,ki,ki64,k164,k264,k364,Q,R,mask)


/* Special case k==384 */
#define REM384_PENTANOMIAL_K384_GF2X(P,Pol,k1,k2,k3,k164,k264,k364,R) \
    XOR6(P,Pol,Pol+6);\
    (P)[0]^=(Pol)[6]<<k1;\
    (P)[1]^=((Pol)[6]>>k164)^((Pol)[7]<<k1);\
    (P)[2]^=((Pol)[7]>>k164)^((Pol)[8]<<k1);\
    (P)[3]^=((Pol)[8]>>k164)^((Pol)[9]<<k1);\
    (P)[4]^=((Pol)[9]>>k164)^((Pol)[10]<<k1);\
    (P)[5]^=((Pol)[10]>>k164)^((Pol)[11]<<k1);\
    (P)[0]^=(Pol)[6]<<k2;\
    (P)[1]^=((Pol)[6]>>k264)^((Pol)[7]<<k2);\
    (P)[2]^=((Pol)[7]>>k264)^((Pol)[8]<<k2);\
    (P)[3]^=((Pol)[8]>>k264)^((Pol)[9]<<k2);\
    (P)[4]^=((Pol)[9]>>k264)^((Pol)[10]<<k2);\
    (P)[5]^=((Pol)[10]>>k264)^((Pol)[11]<<k2);\
    (P)[0]^=(Pol)[6]<<k3;\
    (P)[1]^=((Pol)[6]>>k364)^((Pol)[7]<<k3);\
    (P)[2]^=((Pol)[7]>>k364)^((Pol)[8]<<k3);\
    (P)[3]^=((Pol)[8]>>k364)^((Pol)[9]<<k3);\
    (P)[4]^=((Pol)[9]>>k364)^((Pol)[10]<<k3);\
    (P)[5]^=((Pol)[10]>>k364)^((Pol)[11]<<k3);\
    R=(Pol)[11]>>k364;\
    R^=(Pol)[11]>>k264;\
    /* Useless if k1==1 */\
    R^=(Pol)[11]>>k164;\
    (P)[0]^=R;\
    (P)[0]^=R<<k1;\
    (P)[0]^=R<<k2;\
    (P)[0]^=R<<k3;


#define MACRO_448_TRINOMIAL_GF2X(ROW,P,Pol,k3,ki,ki64,k364,Q,R,mask) \
    Q[0]=((Pol)[6]>>ki)^((Pol)[7]<<ki64);\
    Q[1]=((Pol)[7]>>ki)^((Pol)[8]<<ki64);\
    Q[2]=((Pol)[8]>>ki)^((Pol)[9]<<ki64);\
    Q[3]=((Pol)[9]>>ki)^((Pol)[10]<<ki64);\
    Q[4]=((Pol)[10]>>ki)^((Pol)[11]<<ki64);\
    Q[5]=((Pol)[11]>>ki)^((Pol)[12]<<ki64);\
    ROW;\
    XOR7(P,Pol,Q);\
    (P)[0]^=Q[0]<<k3;\
    (P)[1]^=(Q[0]>>k364)^(Q[1]<<k3);\
    (P)[2]^=(Q[1]>>k364)^(Q[2]<<k3);\
    (P)[3]^=(Q[2]>>k364)^(Q[3]<<k3);\
    (P)[4]^=(Q[3]>>k364)^(Q[4]<<k3);\
    (P)[5]^=(Q[4]>>k364)^(Q[5]<<k3);\
    (P)[6]^=(Q[5]>>k364)^(Q[6]<<k3);\
    /* 64-(k364+ki) == (k3-ki) */\
    R=(ki>=k3)?Q[6]>>(ki-k3):(Q[5]>>(k364+ki))^(Q[6]<<(k3-ki));\
    (P)[0]^=R;\
    (P)[0]^=R<<k3;\
    (P)[6]&=mask;


#define REM416_TRINOMIAL_GF2X(P,Pol,k3,ki,ki64,k364,Q,R,mask) \
    MACRO_448_TRINOMIAL_GF2X(Q[6]=((Pol)[12]>>ki),\
                             P,Pol,k3,ki,ki64,k364,Q,R,mask)

#define REM448_TRINOMIAL_GF2X(P,Pol,k3,ki,ki64,k364,Q,R,mask) \
    MACRO_448_TRINOMIAL_GF2X(Q[6]=((Pol)[12]>>ki)^((Pol)[13]<<ki64),\
                             P,Pol,k3,ki,ki64,k364,Q,R,mask)


/* Requirement: k=402, and give k3=k3&63 */
#define REM402_SPECIALIZED_TRINOMIAL_GF2X(P,Pol,k3,ki,ki64,k364,Q,R,mask) \
    Q[0]=((Pol)[6]>>ki)^((Pol)[7]<<ki64);\
    Q[1]=((Pol)[7]>>ki)^((Pol)[8]<<ki64);\
    Q[2]=((Pol)[8]>>ki)^((Pol)[9]<<ki64);\
    Q[3]=((Pol)[9]>>ki)^((Pol)[10]<<ki64);\
    Q[4]=((Pol)[10]>>ki)^((Pol)[11]<<ki64);\
    Q[5]=((Pol)[11]>>ki)^((Pol)[12]<<ki64);\
    Q[6]=((Pol)[12]>>ki);\
\
    Q[0]^=(Q[3]>>39)^(Q[4]<<25);\
    Q[1]^=(Q[4]>>39)^(Q[5]<<25);\
    Q[2]^=(Q[5]>>39)^(Q[6]<<25);\
\
    XOR7(P,Pol,Q);\
\
    (P)[2]^=(Q[0]<<k3);\
    (P)[3]^=(Q[0]>>k364)^(Q[1]<<k3);\
    (P)[4]^=(Q[1]>>k364)^(Q[2]<<k3);\
    (P)[5]^=(Q[2]>>k364)^(Q[3]<<k3);\
    (P)[6]^=Q[3]>>k364;\
    (P)[6]&=mask;


#define MACRO_448_PENTANOMIAL_GF2X(ROW,P,Pol,k1,k2,k3,ki,ki64,\
                                   k164,k264,k364,Q,R,mask) \
    Q[0]=((Pol)[6]>>ki)^((Pol)[7]<<ki64);\
    Q[1]=((Pol)[7]>>ki)^((Pol)[8]<<ki64);\
    Q[2]=((Pol)[8]>>ki)^((Pol)[9]<<ki64);\
    Q[3]=((Pol)[9]>>ki)^((Pol)[10]<<ki64);\
    Q[4]=((Pol)[10]>>ki)^((Pol)[11]<<ki64);\
    Q[5]=((Pol)[11]>>ki)^((Pol)[12]<<ki64);\
    ROW;\
    XOR7(P,Pol,Q);\
    (P)[0]^=Q[0]<<k1;\
    (P)[1]^=(Q[0]>>k164)^(Q[1]<<k1);\
    (P)[2]^=(Q[1]>>k164)^(Q[2]<<k1);\
    (P)[3]^=(Q[2]>>k164)^(Q[3]<<k1);\
    (P)[4]^=(Q[3]>>k164)^(Q[4]<<k1);\
    (P)[5]^=(Q[4]>>k164)^(Q[5]<<k1);\
    (P)[6]^=(Q[5]>>k164)^(Q[6]<<k1);\
    (P)[0]^=Q[0]<<k2;\
    (P)[1]^=(Q[0]>>k264)^(Q[1]<<k2);\
    (P)[2]^=(Q[1]>>k264)^(Q[2]<<k2);\
    (P)[3]^=(Q[2]>>k264)^(Q[3]<<k2);\
    (P)[4]^=(Q[3]>>k264)^(Q[4]<<k2);\
    (P)[5]^=(Q[4]>>k264)^(Q[5]<<k2);\
    (P)[6]^=(Q[5]>>k264)^(Q[6]<<k2);\
    (P)[0]^=Q[0]<<k3;\
    (P)[1]^=(Q[0]>>k364)^(Q[1]<<k3);\
    (P)[2]^=(Q[1]>>k364)^(Q[2]<<k3);\
    (P)[3]^=(Q[2]>>k364)^(Q[3]<<k3);\
    (P)[4]^=(Q[3]>>k364)^(Q[4]<<k3);\
    (P)[5]^=(Q[4]>>k364)^(Q[5]<<k3);\
    (P)[6]^=(Q[5]>>k364)^(Q[6]<<k3);\
    /* 64-(k364+ki) == (k3-ki) */\
    R=(ki>=k3)?Q[6]>>(ki-k3):(Q[5]>>(k364+ki))^(Q[6]<<(k3-ki));\
    R^=(ki>=k2)?Q[6]>>(ki-k2):(Q[5]>>(k264+ki))^(Q[6]<<(k2-ki));\
    R^=(ki>=k1)?Q[6]>>(ki-k1):(Q[5]>>(k164+ki))^(Q[6]<<(k1-ki));\
    (P)[0]^=R;\
    (P)[0]^=R<<k1;\
    (P)[0]^=R<<k2;\
    (P)[0]^=R<<k3;\
    (P)[6]&=mask;

#define REM416_PENTANOMIAL_GF2X(P,Pol,k1,k2,k3,ki,ki64,k164,k264,k364,Q,R,mask)\
    MACRO_448_PENTANOMIAL_GF2X(Q[6]=((Pol)[12]>>ki),\
                               P,Pol,k1,k2,k3,ki,ki64,k164,k264,k364,Q,R,mask)

#define REM448_PENTANOMIAL_GF2X(P,Pol,k1,k2,k3,ki,ki64,k164,k264,k364,Q,R,mask)\
    MACRO_448_PENTANOMIAL_GF2X(Q[6]=((Pol)[12]>>ki)^((Pol)[13]<<ki64),\
                               P,Pol,k1,k2,k3,ki,ki64,k164,k264,k364,Q,R,mask)


/* Special case k==448 */
#define REM448_PENTANOMIAL_K448_GF2X(P,Pol,k1,k2,k3,k164,k264,k364,R) \
    R=(Pol)[13]>>k364;\
    R^=(Pol)[13]>>k264;\
    /* Useless if k1==1 */\
    R^=(Pol)[13]>>k164;\
    R^=(Pol)[7];\
    (P)[0]=(Pol)[0]^R;\
    (P)[0]^=R<<k1;\
    (P)[0]^=R<<k2;\
    (P)[0]^=R<<k3;\
    (P)[1]=(Pol)[1]^(Pol)[8];\
    (P)[2]=(Pol)[2]^(Pol)[9];\
    (P)[3]=(Pol)[3]^(Pol)[10];\
    (P)[4]=(Pol)[4]^(Pol)[11];\
    (P)[5]=(Pol)[5]^(Pol)[12];\
    (P)[6]=(Pol)[6]^(Pol)[13];\
    (P)[1]^=((Pol)[7]>>k164)^((Pol)[8]<<k1);\
    (P)[2]^=((Pol)[8]>>k164)^((Pol)[9]<<k1);\
    (P)[3]^=((Pol)[9]>>k164)^((Pol)[10]<<k1);\
    (P)[4]^=((Pol)[10]>>k164)^((Pol)[11]<<k1);\
    (P)[5]^=((Pol)[11]>>k164)^((Pol)[12]<<k1);\
    (P)[6]^=((Pol)[12]>>k164)^((Pol)[13]<<k1);\
    (P)[1]^=((Pol)[7]>>k264)^((Pol)[8]<<k2);\
    (P)[2]^=((Pol)[8]>>k264)^((Pol)[9]<<k2);\
    (P)[3]^=((Pol)[9]>>k264)^((Pol)[10]<<k2);\
    (P)[4]^=((Pol)[10]>>k264)^((Pol)[11]<<k2);\
    (P)[5]^=((Pol)[11]>>k264)^((Pol)[12]<<k2);\
    (P)[6]^=((Pol)[12]>>k264)^((Pol)[13]<<k2);\
    (P)[1]^=((Pol)[7]>>k364)^((Pol)[8]<<k3);\
    (P)[2]^=((Pol)[8]>>k364)^((Pol)[9]<<k3);\
    (P)[3]^=((Pol)[9]>>k364)^((Pol)[10]<<k3);\
    (P)[4]^=((Pol)[10]>>k364)^((Pol)[11]<<k3);\
    (P)[5]^=((Pol)[11]>>k364)^((Pol)[12]<<k3);\
    (P)[6]^=((Pol)[12]>>k364)^((Pol)[13]<<k3);


/* Special case k==448 and k3=64 */
#define REM448_PENTANOMIAL_K448_K3_IS_64_GF2X(P,Pol,k1,k2,k3,k164,k264,k364,R) \
    R=(Pol)[13];\
    R^=(Pol)[13]>>k264;\
    /* Useless if k1==1 */\
    R^=(Pol)[13]>>k164;\
    R^=(Pol)[7];\
    (P)[0]=(Pol)[0]^R;\
    (P)[1]=(Pol)[1]^R^(Pol)[8];\
    (P)[2]=(Pol)[2]^(Pol)[8]^(Pol)[9];\
    (P)[3]=(Pol)[3]^(Pol)[9]^(Pol)[10];\
    (P)[4]=(Pol)[4]^(Pol)[10]^(Pol)[11];\
    (P)[5]=(Pol)[5]^(Pol)[11]^(Pol)[12];\
    (P)[6]=(Pol)[6]^(Pol)[12]^(Pol)[13];\
    (P)[0]^=R<<k1;\
    (P)[1]^=(R>>k164)^((Pol)[8]<<k1);\
    (P)[2]^=((Pol)[8]>>k164)^((Pol)[9]<<k1);\
    (P)[3]^=((Pol)[9]>>k164)^((Pol)[10]<<k1);\
    (P)[4]^=((Pol)[10]>>k164)^((Pol)[11]<<k1);\
    (P)[5]^=((Pol)[11]>>k164)^((Pol)[12]<<k1);\
    (P)[6]^=((Pol)[12]>>k164)^((Pol)[13]<<k1);\
    (P)[0]^=R<<k2;\
    (P)[1]^=(R>>k264)^((Pol)[8]<<k2);\
    (P)[2]^=((Pol)[8]>>k264)^((Pol)[9]<<k2);\
    (P)[3]^=((Pol)[9]>>k264)^((Pol)[10]<<k2);\
    (P)[4]^=((Pol)[10]>>k264)^((Pol)[11]<<k2);\
    (P)[5]^=((Pol)[11]>>k264)^((Pol)[12]<<k2);\
    (P)[6]^=((Pol)[12]>>k264)^((Pol)[13]<<k2);


#define MACRO_512_TRINOMIAL_GF2X(ROW,P,Pol,k3,ki,ki64,k364,Q,R,mask) \
    Q[0]=((Pol)[7]>>ki)^((Pol)[8]<<ki64);\
    Q[1]=((Pol)[8]>>ki)^((Pol)[9]<<ki64);\
    Q[2]=((Pol)[9]>>ki)^((Pol)[10]<<ki64);\
    Q[3]=((Pol)[10]>>ki)^((Pol)[11]<<ki64);\
    Q[4]=((Pol)[11]>>ki)^((Pol)[12]<<ki64);\
    Q[5]=((Pol)[12]>>ki)^((Pol)[13]<<ki64);\
    Q[6]=((Pol)[13]>>ki)^((Pol)[14]<<ki64);\
    ROW;\
    XOR8(P,Pol,Q);\
    (P)[0]^=Q[0]<<k3;\
    (P)[1]^=(Q[0]>>k364)^(Q[1]<<k3);\
    (P)[2]^=(Q[1]>>k364)^(Q[2]<<k3);\
    (P)[3]^=(Q[2]>>k364)^(Q[3]<<k3);\
    (P)[4]^=(Q[3]>>k364)^(Q[4]<<k3);\
    (P)[5]^=(Q[4]>>k364)^(Q[5]<<k3);\
    (P)[6]^=(Q[5]>>k364)^(Q[6]<<k3);\
    (P)[7]^=(Q[6]>>k364)^(Q[7]<<k3);\
    /* 64-(k364+ki) == (k3-ki) */\
    R=(ki>=k3)?Q[7]>>(ki-k3):(Q[6]>>(k364+ki))^(Q[7]<<(k3-ki));\
    (P)[0]^=R;\
    (P)[0]^=R<<k3;\
    (P)[7]&=mask;

#define REM480_TRINOMIAL_GF2X(P,Pol,k3,ki,ki64,k364,Q,R,mask) \
    MACRO_512_TRINOMIAL_GF2X(Q[7]=((Pol)[14]>>ki),\
                             P,Pol,k3,ki,ki64,k364,Q,R,mask)

#define REM512_TRINOMIAL_GF2X(P,Pol,k3,ki,ki64,k364,Q,R,mask) \
    MACRO_512_TRINOMIAL_GF2X(Q[7]=((Pol)[14]>>ki)^((Pol)[15]<<ki64),\
                             P,Pol,k3,ki,ki64,k364,Q,R,mask)


#define MACRO_512_PENTANOMIAL_GF2X(ROW,P,Pol,k1,k2,k3,ki,ki64,\
                                   k164,k264,k364,Q,R,mask) \
    Q[0]=((Pol)[7]>>ki)^((Pol)[8]<<ki64);\
    Q[1]=((Pol)[8]>>ki)^((Pol)[9]<<ki64);\
    Q[2]=((Pol)[9]>>ki)^((Pol)[10]<<ki64);\
    Q[3]=((Pol)[10]>>ki)^((Pol)[11]<<ki64);\
    Q[4]=((Pol)[11]>>ki)^((Pol)[12]<<ki64);\
    Q[5]=((Pol)[12]>>ki)^((Pol)[13]<<ki64);\
    Q[6]=((Pol)[13]>>ki)^((Pol)[14]<<ki64);\
    ROW;\
    XOR8(P,Pol,Q);\
    (P)[0]^=Q[0]<<k1;\
    (P)[1]^=(Q[0]>>k164)^(Q[1]<<k1);\
    (P)[2]^=(Q[1]>>k164)^(Q[2]<<k1);\
    (P)[3]^=(Q[2]>>k164)^(Q[3]<<k1);\
    (P)[4]^=(Q[3]>>k164)^(Q[4]<<k1);\
    (P)[5]^=(Q[4]>>k164)^(Q[5]<<k1);\
    (P)[6]^=(Q[5]>>k164)^(Q[6]<<k1);\
    (P)[7]^=(Q[6]>>k164)^(Q[7]<<k1);\
    (P)[0]^=Q[0]<<k2;\
    (P)[1]^=(Q[0]>>k264)^(Q[1]<<k2);\
    (P)[2]^=(Q[1]>>k264)^(Q[2]<<k2);\
    (P)[3]^=(Q[2]>>k264)^(Q[3]<<k2);\
    (P)[4]^=(Q[3]>>k264)^(Q[4]<<k2);\
    (P)[5]^=(Q[4]>>k264)^(Q[5]<<k2);\
    (P)[6]^=(Q[5]>>k264)^(Q[6]<<k2);\
    (P)[7]^=(Q[6]>>k264)^(Q[7]<<k2);\
    (P)[0]^=Q[0]<<k3;\
    (P)[1]^=(Q[0]>>k364)^(Q[1]<<k3);\
    (P)[2]^=(Q[1]>>k364)^(Q[2]<<k3);\
    (P)[3]^=(Q[2]>>k364)^(Q[3]<<k3);\
    (P)[4]^=(Q[3]>>k364)^(Q[4]<<k3);\
    (P)[5]^=(Q[4]>>k364)^(Q[5]<<k3);\
    (P)[6]^=(Q[5]>>k364)^(Q[6]<<k3);\
    (P)[7]^=(Q[6]>>k364)^(Q[7]<<k3);\
    /* 64-(k364+ki) == (k3-ki) */\
    R=(ki>=k3)?Q[7]>>(ki-k3):(Q[6]>>(k364+ki))^(Q[7]<<(k3-ki));\
    R^=(ki>=k2)?Q[7]>>(ki-k2):(Q[6]>>(k264+ki))^(Q[7]<<(k2-ki));\
    R^=(ki>=k1)?Q[7]>>(ki-k1):(Q[6]>>(k164+ki))^(Q[7]<<(k1-ki));\
    (P)[0]^=R;\
    (P)[0]^=R<<k1;\
    (P)[0]^=R<<k2;\
    (P)[0]^=R<<k3;\
    (P)[7]&=mask;

#define REM480_PENTANOMIAL_GF2X(P,Pol,k1,k2,k3,ki,ki64,k164,k264,k364,Q,R,mask)\
    MACRO_512_PENTANOMIAL_GF2X(Q[7]=((Pol)[14]>>ki),\
                               P,Pol,k1,k2,k3,ki,ki64,k164,k264,k364,Q,R,mask)

#define REM512_PENTANOMIAL_GF2X(P,Pol,k1,k2,k3,ki,ki64,k164,k264,k364,Q,R,mask)\
    MACRO_512_PENTANOMIAL_GF2X(Q[7]=((Pol)[14]>>ki)^((Pol)[15]<<ki64),\
                               P,Pol,k1,k2,k3,ki,ki64,k164,k264,k364,Q,R,mask)


/* Special case k==512 */
#define REM512_PENTANOMIAL_K512_GF2X(P,Pol,k1,k2,k3,k164,k264,k364,R) \
    R=(Pol)[15]>>k364;\
    R^=(Pol)[15]>>k264;\
    /* Useless if k1==1 */\
    R^=(Pol)[15]>>k164;\
    R^=(Pol)[8];\
    (P)[0]=(Pol)[0]^R;\
    (P)[0]^=R<<k1;\
    (P)[0]^=R<<k2;\
    (P)[0]^=R<<k3;\
    (P)[1]=(Pol)[1]^(Pol)[9];\
    (P)[2]=(Pol)[2]^(Pol)[10];\
    (P)[3]=(Pol)[3]^(Pol)[11];\
    (P)[4]=(Pol)[4]^(Pol)[12];\
    (P)[5]=(Pol)[5]^(Pol)[13];\
    (P)[6]=(Pol)[6]^(Pol)[14];\
    (P)[7]=(Pol)[7]^(Pol)[15];\
    (P)[1]^=((Pol)[8]>>k164)^((Pol)[9]<<k1);\
    (P)[2]^=((Pol)[9]>>k164)^((Pol)[10]<<k1);\
    (P)[3]^=((Pol)[10]>>k164)^((Pol)[11]<<k1);\
    (P)[4]^=((Pol)[11]>>k164)^((Pol)[12]<<k1);\
    (P)[5]^=((Pol)[12]>>k164)^((Pol)[13]<<k1);\
    (P)[6]^=((Pol)[13]>>k164)^((Pol)[14]<<k1);\
    (P)[7]^=((Pol)[14]>>k164)^((Pol)[15]<<k1);\
    (P)[1]^=((Pol)[8]>>k264)^((Pol)[9]<<k2);\
    (P)[2]^=((Pol)[9]>>k264)^((Pol)[10]<<k2);\
    (P)[3]^=((Pol)[10]>>k264)^((Pol)[11]<<k2);\
    (P)[4]^=((Pol)[11]>>k264)^((Pol)[12]<<k2);\
    (P)[5]^=((Pol)[12]>>k264)^((Pol)[13]<<k2);\
    (P)[6]^=((Pol)[13]>>k264)^((Pol)[14]<<k2);\
    (P)[7]^=((Pol)[14]>>k264)^((Pol)[15]<<k2);\
    (P)[1]^=((Pol)[8]>>k364)^((Pol)[9]<<k3);\
    (P)[2]^=((Pol)[9]>>k364)^((Pol)[10]<<k3);\
    (P)[3]^=((Pol)[10]>>k364)^((Pol)[11]<<k3);\
    (P)[4]^=((Pol)[11]>>k364)^((Pol)[12]<<k3);\
    (P)[5]^=((Pol)[12]>>k364)^((Pol)[13]<<k3);\
    (P)[6]^=((Pol)[13]>>k364)^((Pol)[14]<<k3);\
    (P)[7]^=((Pol)[14]>>k364)^((Pol)[15]<<k3);


#define MACRO_576_TRINOMIAL_GF2X(ROW,P,Pol,k3,ki,ki64,k364,Q,R,mask) \
    Q[0]=((Pol)[8]>>ki)^((Pol)[9]<<ki64);\
    Q[1]=((Pol)[9]>>ki)^((Pol)[10]<<ki64);\
    Q[2]=((Pol)[10]>>ki)^((Pol)[11]<<ki64);\
    Q[3]=((Pol)[11]>>ki)^((Pol)[12]<<ki64);\
    Q[4]=((Pol)[12]>>ki)^((Pol)[13]<<ki64);\
    Q[5]=((Pol)[13]>>ki)^((Pol)[14]<<ki64);\
    Q[6]=((Pol)[14]>>ki)^((Pol)[15]<<ki64);\
    Q[7]=((Pol)[15]>>ki)^((Pol)[16]<<ki64);\
    ROW;\
    XOR9(P,Pol,Q);\
    (P)[0]^=Q[0]<<k3;\
    (P)[1]^=(Q[0]>>k364)^(Q[1]<<k3);\
    (P)[2]^=(Q[1]>>k364)^(Q[2]<<k3);\
    (P)[3]^=(Q[2]>>k364)^(Q[3]<<k3);\
    (P)[4]^=(Q[3]>>k364)^(Q[4]<<k3);\
    (P)[5]^=(Q[4]>>k364)^(Q[5]<<k3);\
    (P)[6]^=(Q[5]>>k364)^(Q[6]<<k3);\
    (P)[7]^=(Q[6]>>k364)^(Q[7]<<k3);\
    (P)[8]^=(Q[7]>>k364)^(Q[8]<<k3);\
    /* 64-(k364+ki) == (k3-ki) */\
    R=(ki>=k3)?Q[8]>>(ki-k3):(Q[7]>>(k364+ki))^(Q[8]<<(k3-ki));\
    (P)[0]^=R;\
    (P)[0]^=R<<k3;\
    (P)[8]&=mask;

#define REM544_TRINOMIAL_GF2X(P,Pol,k3,ki,ki64,k364,Q,R,mask) \
    MACRO_576_TRINOMIAL_GF2X(Q[8]=((Pol)[16]>>ki),\
                             P,Pol,k3,ki,ki64,k364,Q,R,mask)

#define REM576_TRINOMIAL_GF2X(P,Pol,k3,ki,ki64,k364,Q,R,mask) \
    MACRO_576_TRINOMIAL_GF2X(Q[8]=((Pol)[16]>>ki)^((Pol)[17]<<ki64),\
                             P,Pol,k3,ki,ki64,k364,Q,R,mask)


#define MACRO_576_PENTANOMIAL_GF2X(ROW,P,Pol,k1,k2,k3,ki,ki64,\
                                   k164,k264,k364,Q,R,mask) \
    Q[0]=((Pol)[8]>>ki)^((Pol)[9]<<ki64);\
    Q[1]=((Pol)[9]>>ki)^((Pol)[10]<<ki64);\
    Q[2]=((Pol)[10]>>ki)^((Pol)[11]<<ki64);\
    Q[3]=((Pol)[11]>>ki)^((Pol)[12]<<ki64);\
    Q[4]=((Pol)[12]>>ki)^((Pol)[13]<<ki64);\
    Q[5]=((Pol)[13]>>ki)^((Pol)[14]<<ki64);\
    Q[6]=((Pol)[14]>>ki)^((Pol)[15]<<ki64);\
    Q[7]=((Pol)[15]>>ki)^((Pol)[16]<<ki64);\
    ROW;\
    XOR9(P,Pol,Q);\
    (P)[0]^=Q[0]<<k1;\
    (P)[1]^=(Q[0]>>k164)^(Q[1]<<k1);\
    (P)[2]^=(Q[1]>>k164)^(Q[2]<<k1);\
    (P)[3]^=(Q[2]>>k164)^(Q[3]<<k1);\
    (P)[4]^=(Q[3]>>k164)^(Q[4]<<k1);\
    (P)[5]^=(Q[4]>>k164)^(Q[5]<<k1);\
    (P)[6]^=(Q[5]>>k164)^(Q[6]<<k1);\
    (P)[7]^=(Q[6]>>k164)^(Q[7]<<k1);\
    (P)[8]^=(Q[7]>>k164)^(Q[8]<<k1);\
    (P)[0]^=Q[0]<<k2;\
    (P)[1]^=(Q[0]>>k264)^(Q[1]<<k2);\
    (P)[2]^=(Q[1]>>k264)^(Q[2]<<k2);\
    (P)[3]^=(Q[2]>>k264)^(Q[3]<<k2);\
    (P)[4]^=(Q[3]>>k264)^(Q[4]<<k2);\
    (P)[5]^=(Q[4]>>k264)^(Q[5]<<k2);\
    (P)[6]^=(Q[5]>>k264)^(Q[6]<<k2);\
    (P)[7]^=(Q[6]>>k264)^(Q[7]<<k2);\
    (P)[8]^=(Q[7]>>k264)^(Q[8]<<k2);\
    (P)[0]^=Q[0]<<k3;\
    (P)[1]^=(Q[0]>>k364)^(Q[1]<<k3);\
    (P)[2]^=(Q[1]>>k364)^(Q[2]<<k3);\
    (P)[3]^=(Q[2]>>k364)^(Q[3]<<k3);\
    (P)[4]^=(Q[3]>>k364)^(Q[4]<<k3);\
    (P)[5]^=(Q[4]>>k364)^(Q[5]<<k3);\
    (P)[6]^=(Q[5]>>k364)^(Q[6]<<k3);\
    (P)[7]^=(Q[6]>>k364)^(Q[7]<<k3);\
    (P)[8]^=(Q[7]>>k364)^(Q[8]<<k3);\
    /* 64-(k364+ki) == (k3-ki) */\
    R=(ki>=k3)?Q[8]>>(ki-k3):(Q[7]>>(k364+ki))^(Q[8]<<(k3-ki));\
    R^=(ki>=k2)?Q[8]>>(ki-k2):(Q[7]>>(k264+ki))^(Q[8]<<(k2-ki));\
    R^=(ki>=k1)?Q[8]>>(ki-k1):(Q[7]>>(k164+ki))^(Q[8]<<(k1-ki));\
    (P)[0]^=R;\
    (P)[0]^=R<<k1;\
    (P)[0]^=R<<k2;\
    (P)[0]^=R<<k3;\
    (P)[8]&=mask;

#define REM544_PENTANOMIAL_GF2X(P,Pol,k1,k2,k3,ki,ki64,k164,k264,k364,Q,R,mask)\
    MACRO_576_PENTANOMIAL_GF2X(Q[8]=((Pol)[16]>>ki),\
                               P,Pol,k1,k2,k3,ki,ki64,k164,k264,k364,Q,R,mask)

#define REM576_PENTANOMIAL_GF2X(P,Pol,k1,k2,k3,ki,ki64,k164,k264,k364,Q,R,mask)\
    MACRO_576_PENTANOMIAL_GF2X(Q[8]=((Pol)[16]>>ki)^((Pol)[17]<<ki64),\
                               P,Pol,k1,k2,k3,ki,ki64,k164,k264,k364,Q,R,mask)


/* Special case k==576 */
#define REM576_PENTANOMIAL_K576_GF2X(P,Pol,k1,k2,k3,k164,k264,k364,R) \
    R=(Pol)[17]>>k364;\
    R^=(Pol)[17]>>k264;\
    /* Useless if k1==1 */\
    R^=(Pol)[17]>>k164;\
    R^=(Pol)[9];\
    (P)[0]=(Pol)[0]^R;\
    (P)[0]^=R<<k1;\
    (P)[0]^=R<<k2;\
    (P)[0]^=R<<k3;\
    (P)[1]=(Pol)[1]^(Pol)[10];\
    (P)[2]=(Pol)[2]^(Pol)[11];\
    (P)[3]=(Pol)[3]^(Pol)[12];\
    (P)[4]=(Pol)[4]^(Pol)[13];\
    (P)[5]=(Pol)[5]^(Pol)[14];\
    (P)[6]=(Pol)[6]^(Pol)[15];\
    (P)[7]=(Pol)[7]^(Pol)[16];\
    (P)[8]=(Pol)[8]^(Pol)[17];\
    (P)[1]^=((Pol)[9]>>k164)^((Pol)[10]<<k1);\
    (P)[2]^=((Pol)[10]>>k164)^((Pol)[11]<<k1);\
    (P)[3]^=((Pol)[11]>>k164)^((Pol)[12]<<k1);\
    (P)[4]^=((Pol)[12]>>k164)^((Pol)[13]<<k1);\
    (P)[5]^=((Pol)[13]>>k164)^((Pol)[14]<<k1);\
    (P)[6]^=((Pol)[14]>>k164)^((Pol)[15]<<k1);\
    (P)[7]^=((Pol)[15]>>k164)^((Pol)[16]<<k1);\
    (P)[8]^=((Pol)[16]>>k164)^((Pol)[17]<<k1);\
    (P)[1]^=((Pol)[9]>>k264)^((Pol)[10]<<k2);\
    (P)[2]^=((Pol)[10]>>k264)^((Pol)[11]<<k2);\
    (P)[3]^=((Pol)[11]>>k264)^((Pol)[12]<<k2);\
    (P)[4]^=((Pol)[12]>>k264)^((Pol)[13]<<k2);\
    (P)[5]^=((Pol)[13]>>k264)^((Pol)[14]<<k2);\
    (P)[6]^=((Pol)[14]>>k264)^((Pol)[15]<<k2);\
    (P)[7]^=((Pol)[15]>>k264)^((Pol)[16]<<k2);\
    (P)[8]^=((Pol)[16]>>k264)^((Pol)[17]<<k2);\
    (P)[1]^=((Pol)[9]>>k364)^((Pol)[10]<<k3);\
    (P)[2]^=((Pol)[10]>>k364)^((Pol)[11]<<k3);\
    (P)[3]^=((Pol)[11]>>k364)^((Pol)[12]<<k3);\
    (P)[4]^=((Pol)[12]>>k364)^((Pol)[13]<<k3);\
    (P)[5]^=((Pol)[13]>>k364)^((Pol)[14]<<k3);\
    (P)[6]^=((Pol)[14]>>k364)^((Pol)[15]<<k3);\
    (P)[7]^=((Pol)[15]>>k364)^((Pol)[16]<<k3);\
    (P)[8]^=((Pol)[16]>>k364)^((Pol)[17]<<k3);


/* Special case k==544 and k3=128 */
#define REM544_PENTANOMIAL_K3_IS_128_GF2X(P,Pol,k1,k2,k3,ki,ki64,\
                                          k164,k264,k364,Q,R,mask) \
    Q[0]=((Pol)[8]>>ki)^((Pol)[9]<<ki64);\
    Q[1]=((Pol)[9]>>ki)^((Pol)[10]<<ki64);\
    Q[2]=((Pol)[10]>>ki)^((Pol)[11]<<ki64);\
    Q[3]=((Pol)[11]>>ki)^((Pol)[12]<<ki64);\
    Q[4]=((Pol)[12]>>ki)^((Pol)[13]<<ki64);\
    Q[5]=((Pol)[13]>>ki)^((Pol)[14]<<ki64);\
    Q[6]=((Pol)[14]>>ki)^((Pol)[15]<<ki64);\
    Q[7]=((Pol)[15]>>ki)^((Pol)[16]<<ki64);\
    Q[8]=((Pol)[16]>>ki);\
    /* R for K2=3 */\
    Q[0]^=(Pol)[16]>>(k264);\
    /* R for K3=128 */\
    Q[0]^=(Q[6]>>ki)^(Q[7]<<ki64);\
    Q[1]^=(Q[7]>>ki)^(Q[8]<<ki64);\
    XOR9(P,Pol,Q);\
    /* K3=128 */\
    (P)[2]^=Q[0];\
    (P)[3]^=Q[1];\
    (P)[4]^=Q[2];\
    (P)[5]^=Q[3];\
    (P)[6]^=Q[4];\
    (P)[7]^=Q[5];\
    (P)[8]^=Q[6];\
    (P)[0]^=Q[0]<<k1;\
    (P)[1]^=(Q[0]>>k164)^(Q[1]<<k1);\
    (P)[2]^=(Q[1]>>k164)^(Q[2]<<k1);\
    (P)[3]^=(Q[2]>>k164)^(Q[3]<<k1);\
    (P)[4]^=(Q[3]>>k164)^(Q[4]<<k1);\
    (P)[5]^=(Q[4]>>k164)^(Q[5]<<k1);\
    (P)[6]^=(Q[5]>>k164)^(Q[6]<<k1);\
    (P)[7]^=(Q[6]>>k164)^(Q[7]<<k1);\
    (P)[8]^=(Q[7]>>k164)^(Q[8]<<k1);\
    (P)[0]^=Q[0]<<k2;\
    (P)[1]^=(Q[0]>>k264)^(Q[1]<<k2);\
    (P)[2]^=(Q[1]>>k264)^(Q[2]<<k2);\
    (P)[3]^=(Q[2]>>k264)^(Q[3]<<k2);\
    (P)[4]^=(Q[3]>>k264)^(Q[4]<<k2);\
    (P)[5]^=(Q[4]>>k264)^(Q[5]<<k2);\
    (P)[6]^=(Q[5]>>k264)^(Q[6]<<k2);\
    (P)[7]^=(Q[6]>>k264)^(Q[7]<<k2);\
    (P)[8]^=(Q[7]>>k264)^(Q[8]<<k2);\
    (P)[8]&=mask;


#endif

