#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#include <math.h>

typedef struct permutation { 
    int order;
    int data[];
} permutation;

typedef struct registry {
    int size;
    permutation* permutations[];
} registry;

// optimise later ...
void intd_to_binary(int* buffer, int buffer_size, int d_value) 
{
    // SIZE CHECK
    int d_size;

    if (d_value != 0) {
        d_size = (int) floor( log2(d_value) ) + 1;
    } else {
        d_size = 1;
    }

    if ( d_size > (buffer_size/sizeof(int)) ) {
        printf("[UINTD->BINARY] Required buffer size exceeds argument, no cha"
                "nge effected");
        return;
    }
    // END SIZE CHECK
    
    for (int i = d_size-1; i >= 0; --i) {
        if (d_value - (int) pow(2, i) < 0) {
            buffer[i] = 0;
        } else {
            buffer[i] = 1;
            d_value -= (int) pow(2, i);
        }

        if (d_value == 0) { return; }
    }
}

registry* init_registry(int order) 
{
    registry* rg = malloc(sizeof(int) + (int) pow(2, order) * sizeof(permutation*));
    rg->size = (int) pow(2, order);
    printf("[RG->SIZE] %d  [ORDER] %d\n", rg->size, order);

    for (int i = 0; i < rg->size; ++i) {
        int *data_buffer = malloc(order * sizeof(int));
        memset (data_buffer, 0, order * sizeof(int));

        intd_to_binary(data_buffer, order*sizeof(int), i);

        permutation* pm = malloc(sizeof(int) + order*sizeof(int));
        pm->order = order;
        for (int j = 0; j < order; ++j) { pm->data[j] = data_buffer[j]; }
        rg->permutations[i] = pm;

        free(data_buffer);
    }

    return rg;
}

void print_registry(registry* rg) 
{
    printf("\n");
    printf("[REGISTRY {%p}] %d\n", rg, rg->size);

    for (int i = 0; i < rg->size; ++i) {
        int ord = rg->permutations[0]->order;
        printf("(%5d): ", i);
        for (int j = 0; j < ord; ++j) {
            printf("%d ", rg->permutations[i]->data[j]);
        }
        printf("\n");
    }
    printf("\n");
}
