#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

class Process {
public:
    int pid, arrival_time, cpu_time, priority, waiting_time, turnaround_time, remaining_time;

    Process(int pid, int arrival_time, int cpu_time, int priority) {
        this->pid = pid;
        this->arrival_time = arrival_time;
        this->cpu_time = cpu_time;
        this->priority = priority;
        this->waiting_time = 0;
        this->turnaround_time = 0;
        this->remaining_time = cpu_time;
    }
};


bool compareArrivalTime(Process p1, Process p2) {
    return p1.arrival_time < p2.arrival_time;
}


bool compareCpuTime(Process p1, Process p2) {
    return p1.cpu_time < p2.cpu_time;
}


bool comparePriority(Process p1, Process p2) {
    return p1.priority < p2.priority;
}


void calculateAvgTimes(vector<Process> &processes) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    for (auto &process : processes) {
        total_waiting_time += process.waiting_time;
        total_turnaround_time += process.turnaround_time;
    }
    double avg_waiting_time = (double) total_waiting_time / processes.size();
    double avg_turnaround_time = (double) total_turnaround_time / processes.size();
    cout << "Average Waiting Time: " << avg_waiting_time << endl;
    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;
}


void fcfs(vector<Process> &processes) {
    sort(processes.begin(), processes.end(), compareArrivalTime);
    int current_time = 0;
    for (auto &process : processes) {
        if (current_time < process.arrival_time) {
            current_time = process.arrival_time;
        }
        process.waiting_time = current_time - process.arrival_time;
        process.turnaround_time = process.waiting_time + process.cpu_time;
        current_time += process.cpu_time;
    }
    cout << "FCFS Scheduling:" << endl;
    calculateAvgTimes(processes);
}


void preemptiveSJF(vector<Process> &processes) {
    int current_time = 0;
    int completed = 0;
    int n = processes.size();
    int shortest = 0;
    bool found = false;
    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                if (!found || processes[i].remaining_time < processes[shortest].remaining_time) {
                    shortest = i;
                    found = true;
                }
            }
        }
        if (!found) {
            current_time++;
            continue;
        }
        processes[shortest].remaining_time--;
        current_time++;
        if (processes[shortest].remaining_time == 0) {
            completed++;
            found = false;
            processes[shortest].turnaround_time = current_time - processes[shortest].arrival_time;
            processes[shortest].waiting_time = processes[shortest].turnaround_time - processes[shortest].cpu_time;
        }
    }
    cout << "Preemptive SJF Scheduling:" << endl;
    calculateAvgTimes(processes);
}


void nonPreemptiveSJF(vector<Process> &processes) {
    sort(processes.begin(), processes.end(), compareArrivalTime);
    int current_time = 0;
    int completed = 0;
    int n = processes.size();
    while (completed != n) {
        int shortest = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                if (shortest == -1 || processes[i].cpu_time < processes[shortest].cpu_time) {
                    shortest = i;
                }
            }
        }
        if (shortest == -1) {
            current_time++;
            continue;
        }
        current_time += processes[shortest].cpu_time;
        processes[shortest].turnaround_time = current_time - processes[shortest].arrival_time;
        processes[shortest].waiting_time = processes[shortest].turnaround_time - processes[shortest].cpu_time;
        processes[shortest].remaining_time = 0;
        completed++;
    }
    cout << "Non-Preemptive SJF Scheduling:" << endl;
    calculateAvgTimes(processes);
}


void priorityScheduling(vector<Process> &processes) {
    sort(processes.begin(), processes.end(), compareArrivalTime);
    int current_time = 0;
    int completed = 0;
    int n = processes.size();
    while (completed != n) {
        int highest_priority = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                if (highest_priority == -1 || processes[i].priority < processes[highest_priority].priority) {
                    highest_priority = i;
                }
            }
        }
        if (highest_priority == -1) {
            current_time++;
            continue;
        }
        current_time += processes[highest_priority].cpu_time;
        processes[highest_priority].turnaround_time = current_time - processes[highest_priority].arrival_time;
        processes[highest_priority].waiting_time = processes[highest_priority].turnaround_time - processes[highest_priority].cpu_time;
        processes[highest_priority].remaining_time = 0;
        completed++;
    }
    cout << "Priority Scheduling:" << endl;
    calculateAvgTimes(processes);
}


void roundRobin(vector<Process> &processes, int time_slice) {
    int current_time = 0;
    queue<int> ready_queue;
    int completed = 0;
    int n = processes.size();
    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time <= current_time) {
            ready_queue.push(i);
        }
    }
    while (completed != n) {
        if (ready_queue.empty()) {
            current_time++;
            for (int i = 0; i < n; i++) {
                if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                    ready_queue.push(i);
                }
            }
            continue;
        }
        int index = ready_queue.front();
        ready_queue.pop();
        int time_to_execute = min(time_slice, processes[index].remaining_time);
        current_time += time_to_execute;
        processes[index].remaining_time -= time_to_execute;
        for (int i = 0; i < n; i++) {
            if (i != index && processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                ready_queue.push(i);
            }
        }
        if (processes[index].remaining_time == 0) {
            processes[index].turnaround_time = current_time - processes[index].arrival_time;
            processes[index].waiting_time = processes[index].turnaround_time - processes[index].cpu_time;
            completed++;
        } else {
            ready_queue.push(index);
        }
    }
    cout << "Round Robin Scheduling:" << endl;
    calculateAvgTimes(processes);
}


void displayMenu() {
    cout << "CPU Scheduling Algorithms" << endl;
    cout << "1. FCFS" << endl;
    cout << "2. Preemptive SJF" << endl;
    cout << "3. Non-Preemptive SJF" << endl;
    cout << "4. Priority Scheduling" << endl;
    cout << "5. Round Robin" << endl;
    cout << "6. Exit" << endl;
}


int main() {
    vector<Process> processes;
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        int arrival, burst, prio;
        cout << "Enter Arrival Time of Process " << i + 1 << ": ";
        cin >> arrival;
        cout << "Enter Burst Time of Process " << i + 1 << ": ";
        cin >> burst;
        cout << "Enter Priority of Process " << i + 1 << ": ";
        cin >> prio;
        processes.push_back(Process(i + 1, arrival, burst, prio));
    }

    int choice;
    int time_slice = 2;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        vector<Process> temp_processes = processes;
        switch (choice) {
            case 1:
                fcfs(temp_processes);
                break;
            case 2:
                preemptiveSJF(temp_processes);
                break;
            case 3:
                nonPreemptiveSJF(temp_processes);
                break;
            case 4:
                priorityScheduling(temp_processes);
                break;
            case 5:
                roundRobin(temp_processes, time_slice);
                break;
            case 6:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}