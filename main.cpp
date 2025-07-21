#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#endif

size_t getVmRSS() {
#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        return static_cast<size_t>(pmc.WorkingSetSize / 1024);  // KB
    }
#else
    std::ifstream status_file("/proc/self/status");
    std::string line;
    while (std::getline(status_file, line)) {
        if (line.substr(0, 6) == "VmRSS:") {
            std::string value_str = line.substr(6);
            return std::stoul(value_str);  // KB
        }
    }
#endif
    return 0;
}

void simulateLeak() {
    static std::vector<void*> leaks;
    for (int i = 0; i < 1000; ++i) {
        leaks.push_back(malloc(1024));  // leak 1KB blocks
    }
    std::cout << "After leaking 1MB: VmRSS = " << getVmRSS() << " KB\n";
}

void benchmarkAllocations(int iterations) {
    using Clock = std::chrono::high_resolution_clock;
    auto start = Clock::now();

    for (int i = 0; i < iterations; ++i) {
        void* p = malloc(1024 * 1024);  // 1MB
        free(p);
    }

    auto end = Clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Allocation/free time: " << elapsed.count() << " seconds\n";
    std::cout << "VmRSS after benchmark: " << getVmRSS() << " KB\n";
}

int main() {
    std::cout << "=== Benchmark without leaks ===\n";
    benchmarkAllocations(1000000);

    std::cout << "\n=== Simulating memory leaks ===\n";
    simulateLeak();

    std::cout << "\n=== Benchmark after leaks ===\n";
    benchmarkAllocations(1000000);

    return 0;
}
