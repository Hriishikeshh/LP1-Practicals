#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class schedule
{
public:
    //      fcfs non premptive

    void fcfs(vector<int> pid, vector<int> arrival_time, vector<int> burst_time, int n)
    {

        vector<int> completion_time(n), waiting_time(n), turnaround_time(n);

        vector<int> indices(n);
        for (int i = 0; i < n; i++)
        {
            indices[i] = i;
        }
        sort(indices.begin(), indices.end(), [&](int a, int b)
             { return arrival_time[a] < arrival_time[b]; });

        int done = 0;
        int current_time = 0;
        vector<pair<int, int>> gantt_chart;

        while (done != n)
        {
            int idx = indices[done];

            if (current_time < arrival_time[idx])
            {
                cout << "(" << current_time << ",idle)";
                current_time = arrival_time[idx];
            }

            // gantt chart
            // cout<<"("<<current_time<<",P"<<pid[idx]<<" ";

            gantt_chart.push_back({current_time, pid[idx]});

            current_time += burst_time[idx];
            completion_time[idx] = current_time;

            turnaround_time[idx] = completion_time[idx] - arrival_time[idx];
            waiting_time[idx] = turnaround_time[idx] - burst_time[idx];

            done++;
        }

        cout << endl;

        for (auto &it : gantt_chart)
        {
            cout << "(" << it.first << ",P" << it.second << ")";
        }

        cout << endl;

        // Print completion, turnaround, and waiting times
        for (int i = 0; i < n; i++)
        {
            cout << "P" << pid[i] << ": Completion Time = " << completion_time[i]
                 << ", Turnaround Time = " << turnaround_time[i]
                 << ", Waiting Time = " << waiting_time[i] << endl;
        }
    }

    //      sjf premptive

    void sjf(vector<int> pid, vector<int> arrival_time, vector<int> remaining_time, vector<int> burst_time, int n)
    {

        int done = 0;
        int current_time = 0;
        vector<pair<int, int>> gantt_chart;

        vector<int> completion_time(n), turnaround_time(n), waiting_time(n);

        while (done != n)
        {
            int min_time = INT_MAX;
            int idx = -1;

            for (int i = 0; i < n; i++)
            {
                if (current_time >= arrival_time[i] && remaining_time[i] > 0 && remaining_time[i] < min_time)
                {
                    min_time = remaining_time[i];
                    idx = i;
                }
            }

            if (idx != -1)
            {
                gantt_chart.push_back({current_time, pid[idx]});
                remaining_time[idx]--;
                current_time++;

                if (remaining_time[idx] == 0)
                {
                    completion_time[idx] = current_time;
                    turnaround_time[idx] = completion_time[idx] - arrival_time[idx];
                    waiting_time[idx] = turnaround_time[idx] - burst_time[idx];
                    done++;
                }
            }
            else
            {
                gantt_chart.push_back({current_time, -1});
                current_time++;
            }
        }

        cout << "gantt chart :" << endl;
        for (auto &it : gantt_chart)
        {
            if (it.second == -1)
                cout << "(" << it.first << ",idle)" << " ";
            else
                cout << "(" << it.first << ",P" << it.second << ") ";
        }

        cout << endl;

        cout << "pid\tat\tbt\tcompletion time\tturnaround time\twaiting time" << endl;

        for (int i = 0; i < n; i++)
        {
            cout << "P" << pid[i] << "\t" << arrival_time[i] << "\t" << burst_time[i] << "\t\t" << completion_time[i] << "\t\t  " << turnaround_time[i] << "\t\t  " << waiting_time[i] << endl;
        }
    }

    //      priority non premptive

    void priority(vector<int> pid, vector<int> arrival_time, vector<int> burst_time, int n)
    {

        vector<int> indices(n), priority(n);
        vector<int> completion_time(n), waiting_time(n), turnaround_time(n);

        priority = {2, 1, 4, 3};

        for (int i = 0; i < n; i++)
        {
            indices[i] = i;
        }

        // for(int i=0;i<n;i++){
        //     cout<<"enter priority of process "<<i+1<<" :";
        //     cin>>priority[i];
        // }

        sort(indices.begin(), indices.end(), [&](int a, int b)
             { return priority[a] > priority[b]; });

        int current_time = 0;
        int done = 0;
        vector<pair<int, int>> gantt_chart;

        while (done != n)
        {
            int idx = -1;
            int highest_priority = INT_MAX;

            for (int i = 0; i < n; i++)
            {
                if (current_time >= arrival_time[i] && completion_time[i] == 0)
                {
                    if (priority[i] < highest_priority)
                    {
                        highest_priority = priority[i];
                        idx = i;
                    }
                }
            }

            if (idx != -1)
            {
                gantt_chart.push_back({current_time, pid[idx]});
                current_time += burst_time[idx];

                completion_time[idx] = current_time;
                turnaround_time[idx] = completion_time[idx] - arrival_time[idx];
                waiting_time[idx] = turnaround_time[idx] - burst_time[idx];
                done++;
            }
            else
            {
                gantt_chart.push_back({current_time, -1});
                current_time++;
            }
        }

        cout << "gantt chart :" << endl;
        for (auto &it : gantt_chart)
        {
            if (it.second == -1)
                cout << "(" << it.first << ",idle)" << " ";
            else
                cout << "(" << it.first << ",P" << it.second << ") ";
        }

        cout << endl;

        cout << "pid\tat\tbt\tpriority\tcompletion time\tturnaround time\twaiting time" << endl;

        for (int i = 0; i < n; i++)
        {
            cout << "P" << pid[i] << "\t" << arrival_time[i] << "\t" << burst_time[i] << "\t" << priority[i] << "\t\t" << completion_time[i] << "\t\t  " << turnaround_time[i] << "\t\t  " << waiting_time[i] << endl;
        }
    }

    //      premptive round robin
    void roundrobin(vector<int> pid, vector<int> arrival_time, vector<int> burst_time, int n)
    {

        vector<int> remaining_time(n);
        for (int i = 0; i < n; i++)
        {
            remaining_time[i] = burst_time[i];
        }

        vector<int> completion_time(n), waiting_time(n), turnaround_time(n);

        int done = 0;
        int current_time = 0;
        vector<pair<int, int>> gantt_chart;

        int quant;
        cout << "enter time quantum :";
        cin >> quant;

    
        while (done != n)
        {
            bool flag = false;
            for (int i = 0; i < n; i++)
            {

                if (arrival_time[i] <= current_time && remaining_time[i] > 0)
                {
                    flag = true;
                    if (remaining_time[i] <= quant)
                    {
                        current_time += remaining_time[i];
                        remaining_time[i] = 0;
                        gantt_chart.push_back({pid[i], current_time});
                    }
                    else
                    {
                        current_time += quant;
                        remaining_time[i] -= quant;
                        gantt_chart.push_back({pid[i], current_time});
                    }

                    if (remaining_time[i] == 0)
                    {
                        completion_time[i] = current_time;
                        turnaround_time[i] = completion_time[i] - arrival_time[i];
                        waiting_time[i] = turnaround_time[i] - burst_time[i];
                        done++;
                    }
                }
            }

            if (!flag)
            {
                current_time++;
            }
        }

        // Print Gantt Chart
    cout << "\nGantt Chart:\n";
    for (auto &g : gantt_chart) {
        cout << "| P" << g.first << " ";
    }
    cout << "|\n";

    int time_marker = 0;
    cout << time_marker;
    for (auto &g : gantt_chart) {
        cout << "----" << g.second;
    }
    cout << endl;

    // Output Results
    cout << "\nProcess No.\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time" << endl;
    for (int i = 0; i < n; i++) {
        cout << pid[i] << "\t\t" << arrival_time[i] << "\t\t" << burst_time[i]
             << "\t\t" << completion_time[i] << "\t\t" << turnaround_time[i] << "\t\t" << waiting_time[i] << endl;
    }
       
    }
};

int main()
{
    int n;
    cout << "enter number of processes: ";
    cin >> n;

    vector<int> pid(n), burst_time(n), remaining_time(n), arrival_time(n);

    // for (int i = 0; i < n; i++)
    // {
    //     pid[i] = i + 1;
    //     cout << "enter arrival time for process " << i + 1 << " :";
    //     cin >> arrival_time[i];
    //     cout << "enter burst time for process " << i + 1 << " :";
    //     cin >> burst_time[i];
    //     remaining_time[i] = burst_time[i];
    // }

    pid = {1, 2, 3, 4};
    burst_time = {6, 4, 5, 3};
    arrival_time = {0, 2, 4, 5};

    schedule sc;
    // sc.sjf(pid,arrival_time,remaining_time,burst_time,n);

    // sc.fcfs(pid,arrival_time,burst_time,n);

    // sc.priority(pid,arrival_time,burst_time,n);

    sc.roundrobin(pid, arrival_time, burst_time, n);
}