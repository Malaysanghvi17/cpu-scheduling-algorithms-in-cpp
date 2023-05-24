#include <iostream>
#include <bits/stdc++.h>

using namespace std;

typedef struct sjf_with_arrivaltime
{
    int arrival_time;
    int burst_time;
    int priority;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int process_id;
    bool flag = 0;
} sjf;

bool compare_at(sjf a, sjf b)
{
    if (a.arrival_time == b.arrival_time)
    {
        return a.burst_time < b.burst_time;
    }
    else
    {
        return a.arrival_time < b.arrival_time;
    }
}

int main()
{
    int n;
    cout << "enter the number of processes: " << endl;
    cin >> n;

    sjf_with_arrivaltime a[n];

    cout << "enter arrival time and burst time and priority(higher number --> higher priority) of processes: " << endl;

    for (int i = 0; i < n; i++)
    {
        cin >> a[i].arrival_time >> a[i].burst_time >> a[i].priority;
        a[i].process_id = i + 1;
    }

    // sorting struct array based on arrival time
    sort(a, a + n, compare_at);

    // completion time calculation
    int current_time = a[0].arrival_time;
    int completed_processes = 0;

    while (completed_processes < n)
    {
        int largest_priority = INT_MIN;
        int shortest_process_index = -1;

        for (int i = 0; i < n; i++)
        {
            if (a[i].flag == 0 && a[i].arrival_time <= current_time && a[i].priority > largest_priority)
            {
                largest_priority = a[i].priority;
                shortest_process_index = i;
            }
        }

        if (shortest_process_index != -1)
        {
            current_time = current_time + a[shortest_process_index].burst_time;
            a[shortest_process_index].completion_time = current_time;
            a[shortest_process_index].turnaround_time = a[shortest_process_index].completion_time - a[shortest_process_index].arrival_time;
            a[shortest_process_index].waiting_time = a[shortest_process_index].turnaround_time - a[shortest_process_index].burst_time;
            a[shortest_process_index].flag = 1;
            completed_processes++;
        }
        else
        {
            current_time++;
        }
    }

    float avgtat;
    float sumtat = 0;
    float avgwt;
    float sumwt = 0;

    // average turnaround time calculation
    for (int i = 0; i < n; i++)
    {
        sumtat = sumtat + a[i].turnaround_time;
    }
    avgtat = sumtat / n;

    // average waiting time calculation
    for (int i = 0; i < n; i++)
    {
        sumwt = sumwt + a[i].waiting_time;
    }
    avgwt = sumwt / n;

    // print sjf table
    for (int i = 0; i < n; i++)
    {
        cout << "process id: p" << a[i].process_id << ", arrival time: " << a[i].arrival_time << ", burst time: " << a[i].burst_time << ", priority: " << a[i].priority << ", completition time: " << a[i].completion_time << ", turn around time: " << a[i].turnaround_time << ", waiting time: " << a[i].waiting_time << endl;
    }

    cout << "Average Waiting Time: " << avgwt << "\n";
    cout << "Average Turnaround Time: " << avgtat << "\n";
}
