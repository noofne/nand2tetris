#include "../m1_gates/impl.h"

cbit_2 *HALFADDER(int, int);
cbit_2 *FULLADDER(int, int);
cbit_16 *ADDER_c16(cbit_16 *, cbit_16 *);
cbit_16 *INCREMENTER(cbit_16 *);

typedef struct alu_out 
{
    cbit_16 *data;
    int zr;
    int ng;
} alu_out;

alu_out *ALU(cbit_16 *, cbit_16 *, int, int, int, int, int, int);