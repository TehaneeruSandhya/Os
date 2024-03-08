#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 100

typedef struct Block {
    int size;
    int allocated;
} Block;

Block memory[MEMORY_SIZE];

void initializeMemory() {
    memory[0].size = MEMORY_SIZE;
    memory[0].allocated = 0;
}

void displayMemory() {
    printf("Memory Status:\n");
    for (int i = 0; i < MEMORY_SIZE; i++) {
        printf("[%d] Size: %d, Allocated: %s\n", i, memory[i].size,
               memory[i].allocated ? "Yes" : "No");
    }
    printf("\n");
}

void firstFit(int processSize) {
    int i;

    for (i = 0; i < MEMORY_SIZE; i++) {
        if (!memory[i].allocated && memory[i].size >= processSize) {
            memory[i].allocated = 1;

            if (memory[i].size > processSize) {
                // Split the block if there's remaining space
                int remainingSize = memory[i].size - processSize;
                int newBlockIndex = i + 1;

                memory[newBlockIndex].size = remainingSize;
                memory[newBlockIndex].allocated = 0;

                memory[i].size = processSize;
            }

            printf("Process of size %d allocated to block %d\n", processSize, i);
            break;
        }
    }

    if (i == MEMORY_SIZE) {
        printf("No suitable block found for the process of size %d\n", processSize);
    }
}

void deallocateMemory() {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i].allocated = 0;
    }
}

int main() {
    initializeMemory();
    displayMemory();

    // Simulate allocation of processes
    firstFit(30);
    displayMemory();

    firstFit(20);
    displayMemory();

    firstFit(50);
    displayMemory();

    // Simulate deallocation
    deallocateMemory();
    displayMemory();

    return 0;
}
