// STRUCTURES

typedef struct cbit_2 { int data[2]; } cbit_2;
typedef struct cbit_4 { int data[4]; } cbit_4;
typedef struct cbit_8 { int data[8]; } cbit_8;
typedef struct cbit_16 { int data[16]; } cbit_16;

// GATES

int  NOT(int);

int NAND(int, int);
int  AND(int, int);
int   OR(int, int);
int  XOR(int, int);

int  MUX(int, int, int);

cbit_16 *NOT_c16(cbit_16 *);

cbit_16 *AND_c16(cbit_16 *, cbit_16 *);
cbit_16  *OR_c16(cbit_16 *, cbit_16 *);
cbit_16 *MUX_c16(cbit_16 *, cbit_16 *, int);

int OR_p8(int, int, int, int, int, int, int, int);
cbit_16 *MUX_c16_p4(cbit_16 *, cbit_16 *, cbit_16 *, cbit_16 *, int, int);
cbit_16 *MUX_c16_p8(cbit_16 *, cbit_16 *, cbit_16 *, cbit_16 *,
                    cbit_16 *, cbit_16 *, cbit_16 *, cbit_16 *, int, int, int);

cbit_2 *DEMUX(int, int);
cbit_4 *DEMUX_p4(int, int, int);
cbit_8 *DEMUX_p8(int, int, int, int);

int OR_p3(int, int, int);