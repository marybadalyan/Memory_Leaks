# 🧠 Memory Allocation Benchmark & Leak Simulation

This project demonstrates how **memory leaks** can affect memory usage and performance. It includes a simple C++ program that:

- Simulates memory leaks
- Benchmarks memory allocation performance before and after leaking
- Measures actual memory consumption using **Resident Set Size (VmRSS)**
- Works on both **Linux** and **Windows**

---

## ❓ What Are Memory Leaks?

A **memory leak** happens when a program **allocates memory but never releases it**. This "lost" memory remains reserved even though it’s no longer needed, causing:

- Increased memory consumption
- Fragmentation of the heap
- Slower allocation times
- Potential crashes if memory runs out

### Example of a Memory Leak:

```cpp
int* leak = new int[100]; 
// Memory allocated but no delete[] call => leak
```

### 📋 Features
- Simulates intentional memory leaks

- Benchmarks allocation/deallocation speed

- Measures actual memory footprint (VmRSS/WorkingSetSize)

- Works on Linux and Windows platforms


### Why Fixing Memory Leaks Improves Memory Consumption
By fixing memory leaks, you:

- Reduce total memory used (VmRSS decreases)

- Prevent heap fragmentation, leading to faster memory allocations

- Avoid long-term slowdowns and instability, especially for long-running processes

- Improve overall system performance

In short:

🚀 Less wasted memory = more efficient program = faster execution + less chance of crashing.


---

## Build & Run Instructions  

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/main 
```

## Example output

```
=== Benchmark without leaks ===
Allocation/free time: 5.57724 seconds
VmRSS after benchmark: 4652 KB

=== Simulating memory leaks ===
After leaking 1MB: VmRSS = 5744 KB

=== Benchmark after leaks ===
Allocation/free time: 6.17553 seconds
VmRSS after benchmark: 5744 KB

```

# 📝 Overview
This project is a simple C++ benchmarking tool to demonstrate how memory leaks impact performance and memory consumption. It also provides a simple reference for cross-platform memory monitoring in C++.