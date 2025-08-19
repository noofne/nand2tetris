#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "../meta/perm.h"
#include "../m1_gates/impl.h"

/* NAME:   `half-adder`                                                 */
/* INPUT:   a, b                                                        */
/* OUTPUT:  c, s (carry, sum)                                           */
/* LOGIC:   Adds two bits together, returning the sum and carry bits.   */
cbit_2 *HALFADDER(int a, int b)
{
    cbit_2 *r = malloc(2 * sizeof(int));
    r->data[0] = AND(a, b); // carry
    r->data[1] = XOR(a, b); // sum

    return r;
}

/* NAME:   `full-adder`                                                 */
/* INPUT:   a, b, c                                                     */
/* OUTPUT:  c, s (carry, sum)                                           */
/* LOGIC:   Adds three bits together, returning the sum and carry bits. */
cbit_2 *FULLADDER(int a, int b, int c)
{
    cbit_2 *r = malloc(2 * sizeof(int));
    cbit_2 *rh = HALFADDER(a, b);
    cbit_2 *rc = HALFADDER(rh->data[1], c);

    r->data[0] = OR(rh->data[0], rc->data[0]);
    r->data[1] = rc->data[1];

    return r;
}

/* NAME:   `adder_c16`                                                          */
/* INPUT:  a[16], b[16]                                                         */
/* OUTPUT: o[16]                                                                */
/* LOGIC:  Adds two 16-bit integers together, where the carry bit is dropped.   */
cbit_16 *ADDER_c16(cbit_16 *a, cbit_16 *b)
{
    cbit_16 *r = malloc(16 * sizeof(int));

    cbit_2 *rgs[16];
    rgs[0] = HALFADDER(a->data[0], b->data[0]);
    r->data[0] = rgs[0]->data[1]; // sum

    for (int i = 1; i < 16; ++i)
    {
        rgs[i] = FULLADDER(a->data[i], b->data[i], rgs[i - 1]->data[0]);
        r->data[i] = rgs[i]->data[1]; // sum
    }

    return r;
}

/* NAME:   `incrementer`                                        */
/* INPUT:  a[16]                                                */
/* OUTPUT: o[16]                                                */
/* LOGIC:  Increments input by 1. The carry bit is dropped.     */
cbit_16 *INCREMENTER(cbit_16 *a)
{
    cbit_16 *r = malloc(16 * sizeof(int));

    int carry = 1;

    for (int i = 0; i < 16; ++i)
    {
        r->data[i] = XOR(carry, a->data[i]);
        carry = AND(carry, a->data[i]);
    }

    return r;
}

typedef struct alu_out
{
    cbit_16 *data;
    int zr;
    int ng;
} alu_out;

alu_out *ALU(cbit_16 *x, cbit_16 *y, int zx, int nx, int zy, int ny, int f, int no)
{

    for (int i = 0; i < 16; ++i)
    {
        x->data[i] = AND(zx, x->data[i]); // x vanish
        x->data[i] = XOR(nx, x->data[i]); // x negate

        y->data[i] = AND(zy, y->data[i]); // y vanish
        y->data[i] = XOR(ny, y->data[i]); // y negate
    }

    cbit_16 *r = MUX_c16(ADDER_c16(x, y), AND_c16(x, y), f); // computation

    for (int i = 0; i < 16; ++i)
    {
        r->data[i] = XOR(no, r->data[i]); // o negate
    }

    int zr = NOT(OR(
        OR_p8(r->data[0], r->data[1], r->data[2], r->data[3],
              r->data[4], r->data[5], r->data[6], r->data[7]),
        OR_p8(r->data[8], r->data[9], r->data[10], r->data[11],
              r->data[12], r->data[13], r->data[14], r->data[15])));
    int ng = r->data[15];

    alu_out *r_out = malloc(sizeof(alu_out));
    r_out->data = r;
    r_out->zr = zr;
    r_out->ng = ng;

    return r_out;
}

int main()
{
    registry *reg2 = init_registry(2);

    /* HALF-ADDER */
    for (int i = 0; i < reg2->size; ++i)
    {
        printf("[HALFADDER | ");
        permutation *pm = reg2->permutations[i];
        int a = pm->data[0];
        int b = pm->data[1];
        cbit_2 *r = HALFADDER(a, b);

        printf("a=%d, b=%d] %d %d\n", a, b, r->data[0], r->data[1]);
    }

    registry *reg3 = init_registry(3);

    /* FULL-ADDER */
    for (int i = 0; i < reg3->size; ++i)
    {
        printf("[FULLADDER | ");
        permutation *pm = reg3->permutations[i];
        int a = pm->data[0];
        int b = pm->data[1];
        int c = pm->data[2];
        cbit_2 *r = FULLADDER(a, b, c);

        printf("a=%d, b=%d, c=%d] %d %d\n", a, b, c, r->data[0], r->data[1]);
    }

    int A_data[16] = {1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0};
    int B_data[16] = {0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0};

    cbit_16 *A = malloc(16 * sizeof(int));
    cbit_16 *B = malloc(16 * sizeof(int));

    for (int i = 0; i < 16; i++)
    {
        A->data[i] = A_data[i];
        B->data[i] = B_data[i];
    }
    cbit_16 *C = ADDER_c16(A, B);
    cbit_16 *D = INCREMENTER(A);

    for (int i = 0; i < 16; i++)
    {
        printf("[C] %d\n", C->data[i]);
    }

    for (int i = 0; i < 16; i++)
    {
        printf("[D] %d\n", D->data[i]);
    }

    return 0;
}