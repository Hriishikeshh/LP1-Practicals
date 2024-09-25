#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

class MemoryPlacement
{
public:
    // first fit
    void firstfit(int n, int m, vector<pair<string, int>> &process, vector<int> &memory)
    {
        vector<string> allocation(memory.size(), "");

        for (int i = 0; i < n; i++)
        {
            bool allocated = false;
            for (int j = 0; j < m; j++)
            {
                if (memory[j] >= process[i].second)
                {
                    allocation[j] += process[i].first + " ";
                    memory[j] -= process[i].second;
                    allocated = true;
                    break;
                }
            }
            if (!allocated)
            {
                cout << "Process " << process[i].first << " with size " << process[i].second << " could not be allocated.\n";
            }
        }

        cout << "First Fit allocation :\n";
        for (int i = 0; i < memory.size(); ++i)
        {
            cout << "Memory Block " << i + 1 << " (" << memory[i] << "MB free): " << allocation[i] << endl;
        }
    }

    // Best-Fit Algorithm
    void bestfit(int n, int m, vector<pair<string, int>> &process, vector<int> &memory)
    {
        vector<string> allocation(memory.size(), "");

        for (int i = 0; i < n; i++)
        {
            int bestIdx = -1;
            for (int j = 0; j < m; j++)
            {
                if (memory[j] >= process[i].second)
                {
                    if (bestIdx == -1 || memory[j] < memory[bestIdx])
                    {
                        bestIdx = j;
                    }
                }
            }
            if (bestIdx != -1)
            {
                allocation[bestIdx] += process[i].first + " ";
                memory[bestIdx] -= process[i].second;
            }
            else
            {
                cout << "Process " << process[i].first << " with size " << process[i].second << " could not be allocated.\n";
            }
        }

        cout << "Memory Allocation:\n";
        for (int i = 0; i < memory.size(); ++i)
        {
            cout << "Memory Block " << i + 1 << " (" << memory[i] << "MB free): " << allocation[i] << endl;
        }
    }

    void worstfit(int n, int m, vector<pair<string, int>> &process, vector<int> &memory)
    {
        vector<string> allocation(m, " ");
        int maxi = memory[0];

        for (int i = 0; i < m; i++)
        {
            int worstidx = -1;
            int maxSize = -1;

            for (int j = 0; j < m; j++)
            {
                if (memory[j] >= process[i].second && memory[j] > maxSize)
                {
                    maxSize = memory[j];
                    worstidx = j;
                }
            }
            cout << memory[worstidx] << "  " << endl;

            if (memory[worstidx] >= process[i].second)
            {
                memory[worstidx] -= process[i].second;
                allocation[worstidx] += process[i].first + " ";
                cout << "Process" << process[i].first << "with size " << process[i].second << "allocated" << endl;
            }
            else
            {
                cout << "Process " << process[i].first << " with size " << process[i].second << " could not be allocated.\n";
            }
        }
        cout << "Memory Allocation:\n";
        for (int i = 0; i < memory.size(); ++i)
        {
            cout << "Memory Block " << i + 1 << " (" << memory[i] << "MB free): " << allocation[i] << endl;
        }
    }

    void worstfit(int n, int m, vector<pair<string, int>> &process, vector<int> &memory)
    {
        vector<string> allocation(m, " ");
        int maxi = memory[0];

        for (int i = 0; i < m; i++)
        {
            int worstidx = -1;
            int maxSize = -1;

            for (int j = 0; j < m; j++)
            {
                if (memory[j] >= process[i].second && memory[j] > maxSize)
                {
                    maxSize = memory[j];
                    worstidx = j;
                }
            }
            cout << memory[worstidx] << "  " << endl;

            if (memory[worstidx] >= process[i].second)
            {
                memory[worstidx] -= process[i].second;
                allocation[worstidx] += process[i].first + " ";
                cout << "Process" << process[i].first << "with size " << process[i].second << "allocated" << endl;
            }
            else
            {
                cout << "Process " << process[i].first << " with size " << process[i].second << " could not be allocated.\n";
            }
        }
        cout << "Memory Allocation:\n";
        for (int i = 0; i < memory.size(); ++i)
        {
            cout << "Memory Block " << i + 1 << " (" << memory[i] << "MB free): " << allocation[i] << endl;
        }
    }
};

int main()
{
    vector<int> memory = {100, 500, 200, 300, 600};
    vector<pair<string, int>> process = {{"p1", 120}, {"p2", 200}, {"p3", 50}, {"p4", 80}, {"p5", 300}};

    int m = process.size();
    int n = memory.size();

    MemoryPlacement mp;

    // First-Fit algorithm
    // mp.firstfit(n, m, process, memory);

    // Best-Fit Algorithm
    // mp.bestfit(n, m, process, memory);

    // worst fit
    mp.worstfit(n, m, process, memory);

    return 0;
}