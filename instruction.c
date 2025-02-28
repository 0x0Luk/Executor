#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "executor.h"

bool flagZero(uint8_t AC) {
    return AC == 0x00;
}

bool flagNeg(uint8_t AC) {
    return AC >= 0x80;
}

// STA - armazena o acumulador na memória
void instructionSTA(CPU *executor) {
    executor->PC += 2;
    executor->position = executor->memory[executor->PC];
    printf("STA ----- POSICAO: %x ---- MEMORIA: %x\n\n", executor->position, executor->memory[executor->position * 2 + 4]);
    executor->memory[executor->position * 2 + 4] = executor->AC;
    executor->PC += 2;
}

// LDA - carrega um valor da memória para o acumulador
void instructionLDA(CPU *executor) {
    executor->PC += 2;
    executor->position = executor->memory[executor->PC];
    printf("LDA ----- POSICAO: %x ---- MEMORIA: %x\n\n", executor->position, executor->memory[executor->position * 2 + 4]);
    executor->AC = executor->memory[executor->position * 2 + 4];
    executor->PC += 2;
}

// ADD - soma um valor da memória ao acumulador
void instructionADD(CPU *executor) {
    executor->PC += 2;
    executor->position = executor->memory[executor->PC];
    printf("ADD ----- POSICAO: %x ---- MEMORIA: %x\n\n", executor->position, executor->memory[executor->position * 2 + 4]);
    executor->AC += executor->memory[executor->position * 2 + 4];
    executor->PC += 2;
}

// AND - realiza operação lógica AND com o acumulador
void instructionAND(CPU *executor) {
    executor->PC += 2;
    executor->position = executor->memory[executor->PC];
    printf("AND ----- POSICAO: %x ---- MEMORIA: %x\n\n", executor->position, executor->memory[executor->position * 2 + 4]);
    executor->AC &= executor->memory[executor->position * 2 + 4];
    executor->PC += 2;
}

// OR - realiza operação lógica OR com o acumulador
void instructionOR(CPU *executor) {
    executor->PC += 2;
    executor->position = executor->memory[executor->PC];
    printf("OR ----- POSICAO: %x ---- MEMORIA: %x\n\n", executor->position, executor->memory[executor->position * 2 + 4]);
    executor->AC |= executor->memory[executor->position * 2 + 4];
    executor->PC += 2;
}

// NOT - inverte os bits do acumulador
void instructionNOT(CPU *executor) {
    executor->AC = ~executor->AC;
    executor->PC += 2;
}

// JMP - salta para uma posição específica da memória
void instructionJMP(CPU *executor) {
    executor->PC += 2;
    executor->position = executor->memory[executor->PC];
    printf("JMP ----- POSICAO: %x ---- MEMORIA: %x ------ MEMORY[PC] %x\n\n",
           executor->position, executor->memory[executor->position * 2 + 4], executor->memory[executor->PC]);
    executor->PC = executor->position * 2 + 4;
}

// JN - salta se o acumulador for negativo
void instructionJN(CPU *executor) {
    executor->PC += 2;
    if (flagNeg(executor->AC)) {
        executor->position = executor->memory[executor->PC];
        executor->PC = executor->position * 2 + 4;
    } else {
        executor->PC += 2;
    }
}

// JZ - salta se o acumulador for zero
void instructionJZ(CPU *executor) {
    executor->PC += 2;
    if (flagZero(executor->AC)) {
        executor->position = executor->memory[executor->PC];
        executor->PC = executor->position * 2 + 4;
    } else {
        executor->PC += 2;
    }
}
