#include <stdio.h>

#define MAX_BLOCKS 100  // Maximum number of blocks allowed

// Structure for memory block
struct Block {
    int size;        // Size of block
    int is_used;     // 1 = used, 0 = free
    int time;        // For FIFO and Round Robin 
};

// Global variables
struct Block memory[MAX_BLOCKS];  // Array of memory blocks
int total_blocks = 0;             // Number of blocks
int total_memory = 0;             // Total memory size
int last_allocated = 0;           // For Next Fit algorithm
int current_time = 0;             // For FIFO and Round Robin

// Initialize memory
void init_memory() {
    printf("\n=== Memory Initialization ===\n");
    printf("Enter total memory size: ");
    scanf("%d", &total_memory);
    printf("Enter number of blocks: ");
    scanf("%d", &total_blocks);
    if (total_blocks > MAX_BLOCKS) {
        printf("Error: Maximum blocks allowed is %d\n", MAX_BLOCKS);
        total_blocks = MAX_BLOCKS;
    }
    // Initialize each block
    for (int i = 0; i < total_blocks; i++) {
        printf("Enter size of block %d: ", i);
        scanf("%d", &memory[i].size);
        memory[i].is_used = 0;
        memory[i].time = 0;
    }
    printf("\nMemory initialized successfully!\n");
}

// First Fit Algorithm
int first_fit(int size) {// the amount of memory you want to allocate
    for (int i = 0; i < total_blocks; i++) {//checks every memory block, one by one, from the first to the last
        if (memory[i].is_used == 0 && memory[i].size >= size) {// Is this block free? && Is this block big enough to fit the requested size?
            memory[i].is_used = 1; //marks the block as used (allocated)
            memory[i].time = current_time++; // Fifo & Tourniquet Purposes :) ////
            return i;// returns the index i of the block that was just allocated.
        }
    }
    return -1; // -1 to indicate failure
}

// Best Fit Algorithm
int best_fit(int size) { // the amount of memory you want to allocate
    int best_block = -1; //Keeps track of which block number is the best fit
    int best_size = total_memory + 1;//will store the index of the best (smallest that fits)
    for (int i = 0; i < total_blocks; i++) {
        if (memory[i].is_used == 0 && memory[i].size >= size) {
            if (memory[i].size < best_size) { // If we found a block that's free and big enough, is it smaller than our best so far?
                best_size = memory[i].size; // If the current block is a better fit, remember its size.
                best_block = i; // remember the index of this block.
            }
        }
    }
    if (best_block != -1) { // checks if a suitable block was found
        memory[best_block].is_used = 1; //If a suitable block was found, mark it as used.
        memory[best_block].time = current_time++; // Set the time for this block (for FIFO/Round Robin algorithms).
    }
    return best_block; // RETURN THE INDEX OR -1 IF NONE WAS FOUND.
}

// Worst Fit Algorithm
int worst_fit(int size) {
    int worst_block = -1; // largest that fits
    int worst_size = -1;// This is used to keep track of the largest block found that is big enough for the request.
    for (int i = 0; i < total_blocks; i++) {
        if (memory[i].is_used == 0 && memory[i].size >= size) {
            if (memory[i].size > worst_size) { //checks if the current block is larger than the worst block found so far
                worst_size = memory[i].size;// If the current block is a better (larger) fit, remember its size.
                worst_block = i; // remember the index of this block.
            }
        }
    }
    if (worst_block != -1) {
        memory[worst_block].is_used = 1;// If a suitable block was found, mark it as used
        memory[worst_block].time = current_time++;
    }
    return worst_block;
}

// Next Fit Algorithm
int next_fit(int size) {
    int start = last_allocated; // last_allocated keeps track of the index of the last block that was allocate
    for (int i = start; i < total_blocks; i++) {
        if (memory[i].is_used == 0 && memory[i].size >= size) {
            memory[i].is_used = 1;
            memory[i].time = current_time++;
            last_allocated = i; // Updates last_allocated to the current index, so the next search will start from here.
            return i; //Returns the index of the block that was just allocated.
        }
    }
    for (int i = 0; i < start; i++) {
        if (memory[i].is_used == 0 && memory[i].size >= size) {
            memory[i].is_used = 1;
            memory[i].time = current_time++;
            last_allocated = i;
            return i;
        }
    }
    return -1;
}

// FIFO Algorithm
int fifo(int size) {
    int oldest_block = -1;//will store the index of the oldest (longest free) block found so far.
    int oldest_time = current_time;// This will be used to find the block that has been free the longest 
    for (int i = 0; i < total_blocks; i++) {
        if (memory[i].is_used == 0 && memory[i].size >= size) {
            if (memory[i].time < oldest_time) { // This checks if the current block's time is less than oldest_time.
                oldest_time = memory[i].time; // If so, remember this block's time as the new oldest.
                oldest_block = i; // remember the index of this block.
            }
        }
    }
    if (oldest_block != -1) {
        memory[oldest_block].is_used = 1;
        memory[oldest_block].time = current_time++;
    }
    return oldest_block;
}

// Round Robin (Tourniquet) Algorithm
int round_robin(int size) {
    static int current = 0;
    for (int i = 0; i < total_blocks; i++) {
        int index = (current + i) % total_blocks;
        if (memory[index].is_used == 0 && memory[index].size >= size) {
            memory[index].is_used = 1;
            memory[index].time = current_time++;
            current = (index + 1) % total_blocks;
            return index;
        }
    }
    return -1;
}

// Display memory status
void display_memory() {
    printf("\n=== Memory Status ===\n");
    printf("Total Memory: %d bytes\n", total_memory);
    printf("Total Blocks: %d\n", total_blocks);
    printf("\nBlock\tSize\tStatus\tTime\n");
    printf("------------------------\n");
    for (int i = 0; i < total_blocks; i++) {
        printf("%d\t%d\t%s\t%d\n", i, memory[i].size, memory[i].is_used ? "Used" : "Free", memory[i].time);
    }
    printf("\n");
}

int main() {
    int choice, size, block;
    printf("Welcome to Memory Allocation Simulator!\n");
    init_memory();
    while (1) {
        printf("\nWhat would you like to do?\n");
        printf("1. Allocate memory (First Fit)\n");
        printf("2. Allocate memory (Best Fit)\n");
        printf("3. Allocate memory (Worst Fit)\n");
        printf("4. Allocate memory (Next Fit)\n");
        printf("5. Allocate memory (FIFO)\n");
        printf("6. Allocate memory (Round Robin)\n");
        printf("7. Free memory\n");
        printf("8. Show memory status\n");
        printf("9. Exit\n");
        printf("\nEnter your choice (1-9): ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("\nHow much memory do you want to allocate? ");
                scanf("%d", &size);
                if (size <= 0 || size > total_memory) {
                    printf("Error: Invalid size! Must be between 1 and %d\n", total_memory);
                    break;
                }
                block = first_fit(size);
                if (block != -1) {
                    printf("Success! Memory allocated in block %d\n", block);
                } else {
                    printf("Error: Not enough memory available!\n");
                }
                break;
            case 2:
                printf("\nHow much memory do you want to allocate? ");
                scanf("%d", &size);
                if (size <= 0 || size > total_memory) {
                    printf("Error: Invalid size! Must be between 1 and %d\n", total_memory);
                    break;
                }
                block = best_fit(size);
                if (block != -1) {
                    printf("Success! Memory allocated in block %d\n", block);
                } else {
                    printf("Error: Not enough memory available!\n");
                }
                break;
            case 3:
                printf("\nHow much memory do you want to allocate? ");
                scanf("%d", &size);
                if (size <= 0 || size > total_memory) {
                    printf("Error: Invalid size! Must be between 1 and %d\n", total_memory);
                    break;
                }
                block = worst_fit(size);
                if (block != -1) {
                    printf("Success! Memory allocated in block %d\n", block);
                } else {
                    printf("Error: Not enough memory available!\n");
                }
                break;
            case 4:
                printf("\nHow much memory do you want to allocate? ");
                scanf("%d", &size);
                if (size <= 0 || size > total_memory) {
                    printf("Error: Invalid size! Must be between 1 and %d\n", total_memory);
                    break;
                }
                block = next_fit(size);
                if (block != -1) {
                    printf("Success! Memory allocated in block %d\n", block);
                } else {
                    printf("Error: Not enough memory available!\n");
                }
                break;
            case 5:
                printf("\nHow much memory do you want to allocate? ");
                scanf("%d", &size);
                if (size <= 0 || size > total_memory) {
                    printf("Error: Invalid size! Must be between 1 and %d\n", total_memory);
                    break;
                }
                block = fifo(size);
                if (block != -1) {
                    printf("Success! Memory allocated in block %d\n", block);
                } else {
                    printf("Error: Not enough memory available!\n");
                }
                break;
            case 6:
                printf("\nHow much memory do you want to allocate? ");
                scanf("%d", &size);
                if (size <= 0 || size > total_memory) {
                    printf("Error: Invalid size! Must be between 1 and %d\n", total_memory);
                    break;
                }
                block = round_robin(size);
                if (block != -1) {
                    printf("Success! Memory allocated in block %d\n", block);
                } else {
                    printf("Error: Not enough memory available!\n");
                }
                break;
            case 7:
                printf("\nWhich block do you want to free? ");
                scanf("%d", &block);
                if (block >= 0 && block < total_blocks) {
                    memory[block].is_used = 0;
                    memory[block].time = 0;
                    printf("Success! Block %d has been freed\n", block);
                } else {
                    printf("Error: Invalid block number!\n");
                }
                break;
            case 8:
                display_memory();
                break;
            case 9:
                printf("\nThank you for using Memory Allocation Simulator!\n");
                return 0;
            default:
                printf("\nError: Please enter a number between 1 and 9\n");
        }
    }
    return 0;
} 