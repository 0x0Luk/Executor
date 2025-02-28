#ifndef ADDRESS_H
#define ADDRESS_H

#include <stdint.h>
#include <stdbool.h>

//Váriaveis iniciais
#define TOTAL_SIZE 516
#define SIGNATURE_FILE 0x034e4452

typedef struct {
    uint8_t AC;
    uint8_t PC;
    uint8_t position;
    uint8_t* memory;
} CPU;

void printMemory(const uint8_t *);
void freeMemory(CPU **);
CPU* createMemory();

#endif
