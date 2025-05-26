# Memory Allocation Algorithm Simulator (Mini Project)

This is a simple C program that simulates two basic memory allocation algorithms:
- **First Fit**
- **Best Fit**

It allows you to allocate and free memory blocks, and see how the algorithms work in practice.

## Features
- User chooses total memory size and number of blocks
- Allocate memory using First Fit or Best Fit
- Free memory blocks
- Display current memory status
- Simple, menu-driven interface

## How to Compile and Run

1. **Compile:**
   ```bash
   gcc memory_simulator.c -o memory_simulator
   ```
2. **Run:**
   ```bash
   ./memory_simulator
   ```

## Menu Options
- **1. Allocate memory (First Fit):** Allocates using the first available block that fits
- **2. Allocate memory (Best Fit):** Allocates using the smallest available block that fits
- **3. Free memory:** Frees a block by its number
- **4. Show memory status:** Displays all blocks and their status
- **5. Exit:** Quits the program

## Example
```
Welcome to Memory Allocation Simulator!

=== Memory Initialization ===
Enter total memory size: 1000
Enter number of blocks: 3
Enter size of block 0: 400
Enter size of block 1: 300
Enter size of block 2: 300

What would you like to do?
1. Allocate memory (First Fit)
2. Allocate memory (Best Fit)
3. Free memory
4. Show memory status
5. Exit

Enter your choice (1-5): 1
How much memory do you want to allocate? 200
Success! Memory allocated in block 0
```

## Author
- [Your Name] 