#include <iostream>
#include <vector>
using namespace std;

// Function to conduct the ring election algorithm
void ringElection(vector<int> processes, int initiator) {
    int n = processes.size();
    int currentLeader = initiator;
    int maxID = processes[initiator];  // Start with the initiator's ID
    vector<int> electionRing;  // To hold the IDs in the election

    cout << "Election started by process " << initiator << " with ID " << processes[initiator] << endl;

    // Traverse the ring starting from the initiator
    for (int i = 0; i < n; i++) {
        int currentProcess = (initiator + i) % n;
        electionRing.push_back(processes[currentProcess]);
        if (processes[currentProcess] > maxID) {
            maxID = processes[currentProcess];  // Update maximum ID
            currentLeader = currentProcess;
            cout << "Process " << currentProcess << " with ID " << processes[currentProcess] << " passes the message." << endl;
        }
        
    }

    // Announce the new leader
    cout << "The new leader is process " << currentLeader << " with ID " << maxID << endl;
    cout << "Announcing the new leader to all processes." << endl;

    // Notify all processes
    for (int i = 0; i < n; i++) {
        cout << "Process " << i << " acknowledges the new leader: Process " << currentLeader << " with ID " << maxID << endl;
    }
}

int main() {
    // Example processes with their IDs
    vector<int> processes = {3, 1, 4, 5, 2};  // IDs of the processes
    int initiator = 0;  // The index of the process that starts the election

    // Run the ring election algorithm
    ringElection(processes, initiator);

    return 0;
}
