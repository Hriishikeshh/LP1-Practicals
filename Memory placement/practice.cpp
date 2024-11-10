#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class MemoryAllocator {
public:
    vector<pair<int, bool>> memoryBlocks; // Pair: {size, isAllocated}

    MemoryAllocator(vector<int> blockSizes) {
        for (int size : blockSizes) {
            memoryBlocks.push_back({size, false}); // Initialize with {size, false}
        }
    }

    void printMemoryStatus() {
        cout << "Memory Blocks Status: ";
        for (auto &block : memoryBlocks) {
            cout << "[Size: " << block.first << ", " << (block.second ? "Allocated" : "Free") << "] ";
        }
        cout << endl;
    }

    void firstFit(int processSize) {
        bool allocated = false;
        for (auto &block : memoryBlocks) {
            if (!block.second && block.first >= processSize) {
                block.second = true;
                cout << "Allocated " << processSize << " in block of size " << block.first << " using First Fit.\n";
                allocated = true;
                break;
            }
        }
        if (!allocated) {
            cout << "Failed to allocate " << processSize << " using First Fit.\n";
        }
        printMemoryStatus();
    }

    void bestFit(int processSize) {
        int bestIndex = -1;
        int minSize = INT_MAX;
        for (int i = 0; i < memoryBlocks.size(); i++) {
            if (!memoryBlocks[i].second && memoryBlocks[i].first >= processSize && memoryBlocks[i].first < minSize) {
                minSize = memoryBlocks[i].first;
                bestIndex = i;
            }
        }
        if (bestIndex != -1) {
            memoryBlocks[bestIndex].second = true;
            cout << "Allocated " << processSize << " in block of size " << memoryBlocks[bestIndex].first << " using Best Fit.\n";
        } else {
            cout << "Failed to allocate " << processSize << " using Best Fit.\n";
        }
        printMemoryStatus();
    }

    void worstFit(int processSize) {
        int worstIndex = -1;
        int maxSize = 0;
        for (int i = 0; i < memoryBlocks.size(); i++) {
            if (!memoryBlocks[i].second && memoryBlocks[i].first >= processSize && memoryBlocks[i].first > maxSize) {
                maxSize = memoryBlocks[i].first;
                worstIndex = i;
            }
        }
        if (worstIndex != -1) {
            memoryBlocks[worstIndex].second = true;
            cout << "Allocated " << processSize << " in block of size " << memoryBlocks[worstIndex].first << " using Worst Fit.\n";
        } else {
            cout << "Failed to allocate " << processSize << " using Worst Fit.\n";
        }
        printMemoryStatus();
    }

    void nextFit(int processSize, int &lastIndex) {
        bool allocated = false;
        for (int i = 0; i < memoryBlocks.size(); i++) {
            int index = (lastIndex + i) % memoryBlocks.size();
            if (!memoryBlocks[index].second && memoryBlocks[index].first >= processSize) {
                memoryBlocks[index].second = true;
                lastIndex = index;
                cout << "Allocated " << processSize << " in block of size " << memoryBlocks[index].first << " using Next Fit.\n";
                allocated = true;
                break;
            }
        }
        if (!allocated) {
            cout << "Failed to allocate " << processSize << " using Next Fit.\n";
        }
        printMemoryStatus();
    }

    void resetMemory() {
        for (auto &block : memoryBlocks) {
            block.second = false; // Reset allocation status
        }
        cout << "Memory reset.\n";
        printMemoryStatus();
    }
};

int main() {
    vector<int> blockSizes = {100, 500, 200, 300, 600};
    MemoryAllocator allocator(blockSizes);

    vector<int> processSizes = {212, 417, 112, 426};
    int lastIndex = 0;

    // Example allocation runs:
    cout << "First Fit Allocation:\n";
    for (int size : processSizes) {
        allocator.firstFit(size);
    }
    allocator.resetMemory();

    cout << "\nBest Fit Allocation:\n";
    for (int size : processSizes) {
        allocator.bestFit(size);
    }
    allocator.resetMemory();

    cout << "\nWorst Fit Allocation:\n";
    for (int size : processSizes) {
        allocator.worstFit(size);
    }
    allocator.resetMemory();

    cout << "\nNext Fit Allocation:\n";
    for (int size : processSizes) {
        allocator.nextFit(size, lastIndex);
    }

    return 0;
}
