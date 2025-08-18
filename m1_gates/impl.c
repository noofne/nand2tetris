#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#include <math.h>

#include "../meta/perm.h"

/* PROGRAM SPECIFICATION                                                    */
/* Follows the first chapter of the NAND2TETRIS programme, which implements */
/* a comprehensive set of logic gates to be used in the future to build mor */
/* e complex parts, including the eventual components of our computer.      */

/* SIMPLE-BIT LOGIC GATES */

/* NAME:    `nand`          */
/* INPUT:   [2] p, q        */
/* OUTPUT:  o               */
/* NOTE:    primitive gate  */
int NAND(int p, int q)
{
    return (p && q) ? 0 : 1;
}

/* NAME:    `not`           */
/* INPUT:   [1] p           */
/* OUTPUT:  o               */
/* NOTE:    ¬               */
int NOT(int p) 
{
    return NAND(p, p);
}

/* NAME:    `and`           */
/* INPUT:   [2] p, q        */
/* OUTPUT:  o               */
/* NOTE:    ∧               */
int AND(int p, int q)
{
    return NOT(NAND(p, q));
}

/* NAME:    `or`            */
/* INPUT:   [2] p, q        */
/* OUTPUT:  o               */
/* NOTE:    ∨               */
int OR(int p, int q)
{
    return NAND(NOT(p), NOT(q));
}

/* NAME:    `xor`           */
/* INPUT:   [2] p, q        */
/* OUTPUT:  o               */
/* NOTE:    ⊕               */
int XOR(int p, int q)
{
    return OR( AND(p, NOT(q)), AND(NOT(p), q) );
}

/* NAME:    `mux`           */
/* INPUT:   [1|2] s, p, q   */
/* OUTPUT:  o               */
/* NOTE:    ?               */
int MUX(int p, int q, int s)
{
    return OR( AND(p, NOT(s)), AND(q, s) );
}


/* COMPOUND-BIT LOGIC GATES */

/* compound-bit (16-bit) structure */
typedef struct cbit_16 
{
    int data[16];
} cbit_16;

/* NAME:    `not_c16`       */
/* INPUT:   p[16]           */
/* OUTPUT:  o[16]           */
/* NOTE:    ¬*              */
cbit_16 *NOT_c16(cbit_16* p)
{
    cbit_16 *r = malloc(16 * sizeof(int));

    r->data[ 0] = NOT(p->data[ 0]);
    r->data[ 1] = NOT(p->data[ 1]);
    r->data[ 2] = NOT(p->data[ 2]);
    r->data[ 3] = NOT(p->data[ 3]);

    r->data[ 4] = NOT(p->data[ 4]);
    r->data[ 5] = NOT(p->data[ 5]);
    r->data[ 6] = NOT(p->data[ 6]);
    r->data[ 7] = NOT(p->data[ 7]);

    r->data[ 8] = NOT(p->data[ 8]);
    r->data[ 9] = NOT(p->data[ 9]);
    r->data[10] = NOT(p->data[10]);
    r->data[11] = NOT(p->data[11]);

    r->data[12] = NOT(p->data[12]);
    r->data[13] = NOT(p->data[13]);
    r->data[14] = NOT(p->data[14]);
    r->data[15] = NOT(p->data[15]);

    return r;
}

/* NAME:    `and_c16`       */
/* INPUT:   p[16], q[16]    */
/* OUTPUT:  o[16]           */
/* NOTE:    ∧*              */
cbit_16 *AND_c16(cbit_16 *p, cbit_16 *q)
{
    cbit_16 *r = malloc(16 * sizeof(int));

    r->data[ 0] = AND(p->data[ 0], q->data[ 0]);
    r->data[ 1] = AND(p->data[ 1], q->data[ 1]);
    r->data[ 2] = AND(p->data[ 2], q->data[ 2]);
    r->data[ 3] = AND(p->data[ 3], q->data[ 3]);
    r->data[ 4] = AND(p->data[ 4], q->data[ 4]);
    r->data[ 5] = AND(p->data[ 5], q->data[ 5]);
    r->data[ 6] = AND(p->data[ 6], q->data[ 6]);
    r->data[ 7] = AND(p->data[ 7], q->data[ 7]);
    r->data[ 8] = AND(p->data[ 8], q->data[ 8]);
    r->data[ 9] = AND(p->data[ 9], q->data[ 9]);
    r->data[10] = AND(p->data[10], q->data[10]);
    r->data[11] = AND(p->data[11], q->data[11]);
    r->data[12] = AND(p->data[12], q->data[12]);
    r->data[13] = AND(p->data[13], q->data[13]);
    r->data[14] = AND(p->data[14], q->data[14]);
    r->data[15] = AND(p->data[15], q->data[15]);

    return r;
}

/* NAME:    `or_c16`        */
/* INPUT:   p[16], q[16]    */
/* OUTPUT:  o[16]           */
/* NOTE:    ∨*              */
cbit_16 *OR_c16(cbit_16 *p, cbit_16 *q)
{
    cbit_16 *r = malloc(16 * sizeof(int));

    r->data[ 0] = OR(p->data[ 0], q->data[ 0]);
    r->data[ 1] = OR(p->data[ 1], q->data[ 1]);
    r->data[ 2] = OR(p->data[ 2], q->data[ 2]);
    r->data[ 3] = OR(p->data[ 3], q->data[ 3]);
    r->data[ 4] = OR(p->data[ 4], q->data[ 4]);
    r->data[ 5] = OR(p->data[ 5], q->data[ 5]);
    r->data[ 6] = OR(p->data[ 6], q->data[ 6]);
    r->data[ 7] = OR(p->data[ 7], q->data[ 7]);
    r->data[ 8] = OR(p->data[ 8], q->data[ 8]);
    r->data[ 9] = OR(p->data[ 9], q->data[ 9]);
    r->data[10] = OR(p->data[10], q->data[10]);
    r->data[11] = OR(p->data[11], q->data[11]);
    r->data[12] = OR(p->data[12], q->data[12]);
    r->data[13] = OR(p->data[13], q->data[13]);
    r->data[14] = OR(p->data[14], q->data[14]);
    r->data[15] = OR(p->data[15], q->data[15]);

    return r;
}

/* NAME:    `mux_c16`       */
/* INPUT:   p[16], q[16], s */
/* OUTPUT:  o[16]           */
/* NOTE:    ?*              */
cbit_16 *MUX_c16(cbit_16 *p, cbit_16 *q, int s)
{
    cbit_16 *r = malloc(16 * sizeof(int));

    r->data[ 0] = MUX(p->data[ 0], q->data[ 0], s);
    r->data[ 1] = MUX(p->data[ 1], q->data[ 1], s);
    r->data[ 2] = MUX(p->data[ 2], q->data[ 2], s);
    r->data[ 3] = MUX(p->data[ 3], q->data[ 3], s);
    r->data[ 4] = MUX(p->data[ 4], q->data[ 4], s);
    r->data[ 5] = MUX(p->data[ 5], q->data[ 5], s);
    r->data[ 6] = MUX(p->data[ 6], q->data[ 6], s);
    r->data[ 7] = MUX(p->data[ 7], q->data[ 7], s);
    r->data[ 8] = MUX(p->data[ 8], q->data[ 8], s);
    r->data[ 9] = MUX(p->data[ 9], q->data[ 9], s);
    r->data[10] = MUX(p->data[10], q->data[10], s);
    r->data[11] = MUX(p->data[11], q->data[11], s);
    r->data[12] = MUX(p->data[12], q->data[12], s);
    r->data[13] = MUX(p->data[13], q->data[13], s);
    r->data[14] = MUX(p->data[14], q->data[14], s);
    r->data[15] = MUX(p->data[15], q->data[15], s);

    return r;
}


/* COMPOUND-PATH LOGIC GATES */


/* NAME:    `or_p8`                             */
/* INPUT:   p0, p1, p2, p3, p4, p5, p6, p7, p8  */
/* OUTPUT:  o                                   */
/* NOTE:    v.                                  */
int OR_p8(int p0, int p1, int p2, int p3, 
          int p4, int p5, int p6, int p7)
{   
    return OR(
        OR( 
            OR(p0, p1),
            OR(p2, p3)
        ), OR(
            OR(p4, p5),
            OR(p6, p7)
        )
    );
}

cbit_16 *MUX_c16_p8(cbit_16 *p0, cbit_16 *p1, cbit_16 *p2, cbit_16 *p3,
                    cbit_16 *p4, cbit_16 *p5, cbit_16 *p6, cbit_16 *p7,
                    int s1, int s2, int s3)
{
    
}

int main() 
{
    /* UNARY LOGIC GATES */
    registry *rg1b = init_registry(1);
    printf("\n");

        /* NOT */
        for (int i = 0; i < rg1b->size; ++i) {
            permutation* pm = rg1b->permutations[i];
            printf( "[  NOT | p=%d] %d\n", pm->data[0], NOT(pm->data[0]) );
        } printf("\n");

    /* BINARY LOGIC GATES */
    registry *rg2b = init_registry(2);
    printf("\n");

        /* NAND */
        for (int i = 0; i < rg2b->size; ++i) {
            permutation* pm = rg2b->permutations[i];
            printf( "[ NAND | p=%d, q=%d] %d\n", pm->data[0], pm->data[1], 
                    NAND(pm->data[0], pm->data[1]) );
        } printf("\n");

        /* AND */
        for (int i = 0; i < rg2b->size; ++i) {
            permutation* pm = rg2b->permutations[i];
            printf( "[  AND | p=%d, q=%d] %d\n", pm->data[0], pm->data[1], 
                    AND(pm->data[0], pm->data[1]) );
        } printf("\n");

        /* OR */
        for (int i = 0; i < rg2b->size; ++i) {
            permutation* pm = rg2b->permutations[i];
            printf( "[   OR | p=%d, q=%d] %d\n", pm->data[0], pm->data[1], 
                    OR(pm->data[0], pm->data[1]) );
        } printf("\n");

        /* XOR */
        for (int i = 0; i < rg2b->size; ++i) {
            permutation* pm = rg2b->permutations[i];
            printf( "[  XOR | p=%d, q=%d] %d\n", pm->data[0], pm->data[1], 
                    XOR(pm->data[0], pm->data[1]) );
        } printf("\n");

    /* TERNARY LOGIC GATES */
    registry *rg3b = init_registry(3);
    printf("\n");

        for (int i = 0; i < rg3b->size; ++i) {
            permutation* pm = rg3b->permutations[i];
            printf( "[  MUX | p=%d, q=%d, s=%d] %d\n", pm->data[0], pm->data[1], 
                    pm->data[2], MUX(pm->data[0], pm->data[1], pm->data[2]) );
        } printf("\n");

    /* HIGHER-ORDER LOGIC GATES */
    registry *rg8b = init_registry(8);
    printf("\n");

        for (int i = 0; i < rg8b->size; ++i) {
            permutation* pm = rg8b->permutations[i];
            printf( "[ ORp8 | %d %d %d %d %d %d %d %d] %d\n",
                    pm->data[0], pm->data[1], pm->data[2], pm->data[3],
                    pm->data[4], pm->data[5], pm->data[6], pm->data[7],
                OR_p8(
                    pm->data[0], pm->data[1], pm->data[2], pm->data[3],
                    pm->data[4], pm->data[5], pm->data[6], pm->data[7]
                  ));
        }

    free(rg1b);
    free(rg2b);
    free(rg3b);
    return 0;
}