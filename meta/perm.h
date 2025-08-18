typedef struct permutation { 
    int order;
    int data[];
} permutation;

typedef struct registry {
    int size;
    permutation* permutations[];
} registry;

static void intd_to_binary(int*, int, int);

registry* init_registry(int);

void print_registry(registry*);