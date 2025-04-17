# 🧠 Virtual Memory and Page Replacement Simulator

![C++](https://img.shields.io/badge/Language-C++%2FCLI-blue)  
![OS Concept](https://img.shields.io/badge/Concept-Virtual%20Memory-critical)  
![Algorithm](https://img.shields.io/badge/Page%20Replacement-LRU-green)  
![Interface](https://img.shields.io/badge/GUI-Windows%20Forms-lightgrey)

---

## 🖥️ Project Overview

A complete virtual memory simulation system implemented in **C++/CLI** with a **Windows Forms GUI**, simulating page-based memory management using the **Least Recently Used (LRU)** page replacement policy. The project models:

- Virtual-to-physical memory mapping  
- Page tables and frame allocation  
- LRU-based replacement simulation  
- Internal fragmentation tracking  
- Real-time visualization of memory operations  

---

## 🌟 Key Features

### Core Memory Management

- Virtual Memory: 20 blocks, each with 4 pages (512 bytes per page)  
- Physical Memory: Mirrored structure for frame allocation  
- Internal Fragmentation: Calculates and displays wasted memory  
- Page Table Mapping: Dynamic virtual-to-physical page resolution  

Example declaration:  
`page<T>* v_memory[v_len]; // 20 x 4 virtual memory blocks`

---

### Page Replacement Engine

- Algorithm: Least Recently Used (LRU)  
- Mechanism: Step-wise page replacement on reference string  
- Tracks page faults and manages memory state transitions  

Class structure:  
`std::vector<int> page_table; bool step(); // Executes one LRU replacement cycle`

---

### GUI Components

Built using **Windows Forms (C++/CLI)**:

- Visualizes page tables, valid/invalid bits, and physical memory mapping  
- Real-time simulation with progress bar and status indicators  
- Interactive controls for process size input and speed adjustment  

---

## ⚙️ System Architecture

### Class Responsibilities

- `process`: Tracks memory requirements  
- `virtual_memory`: Allocates virtual pages  
- `page_table`: Maps virtual pages to physical frames  
- `physical_memory`: Allocates actual frames  
- `PageReplacement`: Implements the LRU algorithm  
- `MyForm`: GUI interface for simulation controls and output  

### Data Flow

1. Process initialized with required memory size  
2. Virtual memory allocates pages  
3. Page table maps virtual to physical blocks  
4. Physical memory allocates actual frames  
5. GUI displays current memory state  
6. LRU simulator handles reference string for page accesses  

---

## 📈 Performance Characteristics

### Time Complexities

- Page Lookup: O(1) – direct mapping  
- LRU Replacement: O(n) – linear scan of page history  
- Fragmentation Calculation: O(n²) – nested block scan  

### Memory Configuration

- Virtual Memory: 20 blocks × 4 pages × 512B = 40KB  
- Physical Memory: Configurable  
- Page Table: Dynamic size based on process size  

---

## 🧠 LRU Algorithm Deep Dive

The LRU algorithm handles three scenarios during a memory access:

- If the page is already in memory → hit → no replacement needed  
- If memory has space → insert page into an empty frame  
- If memory is full → find and replace the least recently used page  

On every page fault, the fault counter is incremented, and the GUI updates the memory layout in real time.

---

## 🧪 Sample Output

=== Simulation Results ===
Page Faults: 11
Reference String: 193343465163975
Internal Fragmentation: 2.5KB
Physical Memory Utilization: 78%


---

## 🖱️ GUI Walkthrough

[Process Details Panel]  
├─ Page Table (Valid | VM Block | PM Block)  
├─ Physical Memory Grid (20×4 layout)  
└─ Controls:  
   ├─ Reference String Display  
   ├─ Process Size Input  
   ├─ Progress Bar (0–100%)  
   └─ Page Fault Counter  

---

## 🚀 Getting Started

### Prerequisites

- Visual Studio 2019 or later  
- .NET Framework 4.8  
- C++/CLI enabled  

### Build Instructions

1. Clone the repository  
2. Open `PagingAlgorithm.sln` in Visual Studio  
3. Build in **Release** mode using the **x86** platform  

### Run the Simulation

Launch the executable with an optional process size:  
`VirtualMemorySimulator.exe [process_size]`  
(Default: 35 pages)

---
