#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "executor.h"

// Exibe memória (hexadicimal) em blocos de 16 bytes por linha
void printMemory(const uint8_t *memory) {
    for (int i = 0; i < TOTAL_SIZE; i++) {
        if (i % 16 == 0) {
            printf("\n%04X: ", i);
        }
        printf("%02X ", memory[i]);
    }
    printf("\n");
}

//Libera a memória alocada para CPU
void freeMemory(CPU **cpu) {
    if (cpu && *cpu) {
        if ((*cpu)->memory) {
            free((*cpu)->memory);
        }
        free(*cpu);
        *cpu = NULL;
    }
}

//Cria a memória da CPU
CPU* createMemory() {
    CPU *cpu = (CPU*)malloc(sizeof(CPU));
    if (!cpu) {
        fprintf(stderr, "[!] Erro ao alocar memória para a CPU.\n");
        return NULL;
    }

    cpu->memory = (uint8_t*)calloc(TOTAL_SIZE, sizeof(uint8_t));
    if (!cpu->memory) {
        fprintf(stderr, "[!] Erro ao alocar memória para a memória da CPU.\n");
        free(cpu);
        return NULL;
    }
    
    cpu->AC = 0x00;
    cpu->PC = 0x04;
    cpu->position = 0;

    return cpu;
}
