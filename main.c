#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "executor.h"
#include "instruction.h"

void getRealAddress(void* value, size_t size) {
    uint8_t* bytes = (uint8_t*) value;
    for (size_t i = 0; i < size / 2; i++) {
        uint8_t aux = bytes[i];
        bytes[i] = bytes[size - i - 1];
        bytes[size - i - 1] = aux;
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo.mem>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        fprintf(stderr, "[!] Não foi possível abrir o arquivo %s!\n", argv[1]);
        return EXIT_FAILURE;
    }

    CPU* executor = createMemory();
    if (!executor) {
        fclose(file);
        return EXIT_FAILURE;
    }

    if (fread(executor->memory, sizeof(uint8_t), TOTAL_SIZE, file) != TOTAL_SIZE) {
        fprintf(stderr, "[!] Falha na leitura do arquivo %s!\n", argv[1]);
        fclose(file);
        freeMemory(&executor);
        return EXIT_FAILURE;
    }
    fclose(file);

    uint32_t file_validation = *((uint32_t*)(executor->memory));
    getRealAddress(&file_validation, sizeof(uint32_t));

    if (file_validation != SIGNATURE_FILE) {
        fprintf(stderr, "[!] Arquivo não compatível. Extensão aceita: .mem!\n");
        freeMemory(&executor);
        return EXIT_FAILURE;
    }

    printf("[+] Arquivo carregado com sucesso! \nSIGNATURE: 0x%x\n\n", file_validation);

    while (executor->memory[executor->PC] != HLT && executor->PC < TOTAL_SIZE) {
        printf("\nAC: %02X - PC: %02X - FZ: %d - FN: %d \n INSTRUÇÃO: %02X - CONTEÚDO: %02X\n\n",
               executor->AC, executor->PC, flagZero(executor->AC), flagNeg(executor->AC),
               executor->memory[executor->PC], executor->memory[executor->PC + 2]);

        static void (*instructions[])(CPU*) = {
            [STA] = instructionSTA,
            [LDA] = instructionLDA,
            [ADD] = instructionADD,
            [OR]  = instructionOR,
            [AND] = instructionAND,
            [NOT] = instructionNOT,
            [JMP] = instructionJMP,
            [JN]  = instructionJN,
            [JZ]  = instructionJZ
        };

        uint8_t opcode = executor->memory[executor->PC];
        if (opcode < sizeof(instructions) / sizeof(instructions[0]) && instructions[opcode]) {
            instructions[opcode](executor);
        } else {
            fprintf(stderr, "Instrucao desconhecida: %02X. Pulando...\n", opcode);
            executor->PC += 2;
        }

        printMemory(executor->memory);
        printf("\n");
    }

    printf("\nExecução finalizada.\n");
    freeMemory(&executor);
    return EXIT_SUCCESS;
}
