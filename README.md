# 📦 Memory Allocation Simulator (C)

A simple, interactive command-line **Memory Allocation Simulator** written in C.  
It allows you to simulate and compare different dynamic memory allocation strategies, commonly taught in operating systems courses.

---

## 📖 Description

This simulator manages a predefined number of memory blocks and allows the user to allocate memory using various well-known algorithms:

- **First Fit**
- **Best Fit**
- **Worst Fit**
- **Next Fit**
- **FIFO (First In First Out)**
- **Round Robin (Tourniquet)**

You can allocate and free memory blocks, and display the current memory status through a menu-driven interface.

---

## 🚀 Features

- 📏 Initialize total memory and block sizes
- 📊 Simulate memory allocation using six different algorithms
- 🗑️ Free allocated memory blocks
- 📝 View real-time memory status and block allocation history
- 🖥️ Simple, interactive, and terminal-based

---

## 🛠️ How It Works

- **Blocks**: The memory is divided into a fixed number of blocks, each with a user-defined size.
- **Allocation Algorithms**:
  - **First Fit**: Allocates the first block large enough.
  - **Best Fit**: Allocates the smallest block that fits.
  - **Worst Fit**: Allocates the largest block that fits.
  - **Next Fit**: Like First Fit, but continues search from the last allocated block.
  - **FIFO**: Allocates the oldest available block.
  - **Round Robin**: Cycles through memory blocks in a circular fashion.
- **Freeing Memory**: You can free a specific block by its index.
- **Display Memory**: Check each block's size, status (used/free), and timestamp.

---

## 📦 How to Compile and Run

### 🖥️ Requirements:
- GCC compiler
- Terminal / Command Prompt

### 📝 Compile:
```bash
gcc -o memory_simulator memory_simulator.c
