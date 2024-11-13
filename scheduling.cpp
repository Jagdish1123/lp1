#include <climits>
#include <iomanip>
#include <iostream>
using namespace std;

class Process {
public:
  int id;
  int at;
  int bt;
  int priority;
  int remaining_bt;
};

class SchedulingAlgo {
  Process *p;

public:
  SchedulingAlgo(Process *q) { p = q; }

  void FCFS_Calc(int n, int ct[], int tat[], int wt[]) {
    int wait = 0;
    for (int i = 0; i < n; i++) {
      ct[i] = wait + p[i].bt;
      tat[i] = ct[i] - p[i].at;
      wt[i] = tat[i] - p[i].bt;
      wait = ct[i];
    }
  }

  void SJF_PreEmp(int n, int ct[], int tat[], int wt[]) {
    int completed = 0;
    int current_time = 0;

    while (completed < n) {
      int min_bt = INT_MAX;
      int min_bt_index = -1;
      for (int i = 0; i < n; i++) {
        if (p[i].at <= current_time && p[i].remaining_bt < min_bt &&
            p[i].remaining_bt > 0) {
          min_bt = p[i].remaining_bt;
          min_bt_index = i;
        }
      }

      if (min_bt_index == -1) {
        current_time++;
        continue;
      }

      p[min_bt_index].remaining_bt--;
      current_time++;

      if (p[min_bt_index].remaining_bt == 0) {
        completed++;
        ct[min_bt_index] = current_time;
        tat[min_bt_index] = ct[min_bt_index] - p[min_bt_index].at;
        wt[min_bt_index] = tat[min_bt_index] - p[min_bt_index].bt;
      } 
    }
  }

  void priority_NonPreEmp(int n, int ct[], int tat[], int wt[]) {
    int completed = 0;
    int current_time = 0;

    while (completed < n) {
      int highest_priority_index = -1;
      int highest_priority = INT_MAX;

      for (int i = 0; i < n; i++) {
        if (p[i].at <= current_time && p[i].priority < highest_priority &&
            p[i].remaining_bt > 0) {
          highest_priority = p[i].priority;
          highest_priority_index = i;
        }
      }

      if (highest_priority_index != -1) {
        ct[highest_priority_index] =
            current_time + p[highest_priority_index].bt;
        tat[highest_priority_index] =
            ct[highest_priority_index] - p[highest_priority_index].at;
        wt[highest_priority_index] =
            tat[highest_priority_index] - p[highest_priority_index].bt;

        p[highest_priority_index].remaining_bt = 0;
        completed++;
        current_time = ct[highest_priority_index];
      } else {
        current_time++;
      }
    }
  }

  void RoundRobin_PreEmp(int n, int ct[], int tat[], int wt[], int quantum) {
    int remaining_processes = n;
    int current_time = 0;
    int *remaining_time = new int[n];

    for (int i = 0; i < n; i++) {
      remaining_time[i] = p[i].bt;
    }

    while (remaining_processes > 0) {
      bool done = true;

      for (int i = 0; i < n; i++) {
        if (p[i].at <= current_time && remaining_time[i] > 0) {

          done = false; 

          if (remaining_time[i] > quantum) {
            current_time += quantum;
            remaining_time[i] -= quantum;
          } else {
            current_time += remaining_time[i];
            ct[i] = current_time;
            tat[i] = ct[i] - p[i].at;
            wt[i] = tat[i] - p[i].bt;
            remaining_processes--;
            remaining_time[i] = 0;
          }
        }
      }

      if (done) {
        current_time++; // No pending process, move to the next time unit
      }
    }
    delete[] remaining_time;
  }
};

void displayResults(Process p[], int n, int ct[], int tat[], int wt[]) {
  cout << "ProgId" << setw(8) << "AT" << setw(8) << "BT" << setw(8) << "CT"
       << setw(8) << "TAT" << setw(8) << "WT" << endl;
  for (int i = 0; i < n; i++) {
    cout << p[i].id << setw(8) << p[i].at << setw(8) << p[i].bt << setw(8)
         << ct[i] << setw(8) << tat[i] << setw(8) << wt[i] << endl;
  }
}

int main() {
  Process *p;
  int n;
  cout << "Enter the number of processes: ";
  cin >> n;
  p = new Process[n];

  int choice, quantum;
  do {
    cout << "\nSelect Scheduling Algorithm:\n";
    cout << "1. First Come First Serve (FCFS)\n";
    cout << "2. Shortest Job First (SJF) Preemptive\n";
    cout << "3. Priority Scheduling Non-Preemptive\n";
    cout << "4. Round Robin Scheduling\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    cout << "Enter data (ProgId AT BT):" << endl;
    for (int i = 0; i < n; i++) {
      cin >> p[i].id >> p[i].at >> p[i].bt;
      p[i].remaining_bt = p[i].bt;
    }

    if (choice == 3) {
      cout << "Enter Priority for each process:" << endl;
      for (int i = 0; i < n; i++) {
        cin >> p[i].priority;
      }
    }

    int ct[n], tat[n], wt[n];

    SchedulingAlgo algo(p);

    switch (choice) {
    case 1:
      algo.FCFS_Calc(n, ct, tat, wt);
      cout << "First Come First Serve (FCFS) Results:\n";
      displayResults(p, n, ct, tat, wt);
      break;

    case 2:
      algo.SJF_PreEmp(n, ct, tat, wt);
      cout << "Shortest Job First (SJF) Preemptive Results:\n";
      displayResults(p, n, ct, tat, wt);
      break;

    case 3:
      algo.priority_NonPreEmp(n, ct, tat, wt);
      cout << "Priority Scheduling Non-Preemptive Results:\n";
      displayResults(p, n, ct, tat, wt);
      break;

    case 4:
      cout << "Enter quantum time: ";
      cin >> quantum;
      algo.RoundRobin_PreEmp(n, ct, tat, wt, quantum);
      cout << "Round Robin Scheduling Results:\n";
      displayResults(p, n, ct, tat, wt);
      break;

    case 5:
      cout << "Exiting...\n";
      break;

    default:
      cout << "Invalid choice! Please try again.\n";
    }
  } while (choice != 5);

  delete[] p;
  return 0;
}