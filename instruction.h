#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <stdint.h>
#include <stdbool.h>
#include "executor.h"

// Definição das instruções
#define NOP 0x00  // Sem operação
#define STA 0x10  // Armazena na memória
#define LDA 0x20  // Lê da memória
#define ADD 0x30  // Adiciona
#define OR  0x40  // Operador OR
#define AND 0x50  // Operador AND
#define NOT 0x60  // Operador NOT
#define JMP 0x80  // Salto incondicional
#define JN  0x90  // Salto se negativo
#define JZ  0xA0  // Salto se zero
#define HLT 0xF0  // Finalizar programa

// Funções auxiliares
bool flagZero(uint8_t ac);
bool flagNeg(uint8_t ac);

// Instruções da CPU
void instructionSTA(CPU *cpu);
void instructionLDA(CPU *cpu);
void instructionADD(CPU *cpu);
void instructionAND(CPU *cpu);
void instructionOR(CPU *cpu);
void instructionNOT(CPU *cpu);
void instructionJMP(CPU *cpu);
void instructionJN(CPU *cpu);
void instructionJZ(CPU *cpu);

#endif
