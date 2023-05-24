#include <iostream>
#include <bits/stdc++.h>
// #define n = 10;

using namespace std;

typedef struct fcfs_with_arrivaltime
{
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int process_id;
} fcfs;

bool compare(fcfs a, fcfs b)
{
    if (a.arrival_time < b.arrival_time)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    int n;
    cout << "enter the number of processes: " << endl;
    cin >> n;

    fcfs_with_arrivaltime a[n];

    cout << "enter arrival time and burst time of processes: " << endl;

    for (int i = 0; i < n; i++)
    {
        cin >> a[i].arrival_time >> a[i].burst_time;
        a[i].process_id = i + 1;
    }

    // sorting struct array based on arrival time
    sort(a, a + n, compare);

    // completion time calculation
    a[0].completion_time = a[0].arrival_time + a[0].burst_time;
    for (int i = 1; i < n; i++)
    {
        if (a[i].arrival_time < a[i - 1].completion_time)
        {
            a[i].completion_time = a[i - 1].completion_time + a[i].burst_time;
        }
        else
        {
            a[i].completion_time = a[i].arrival_time + a[i].burst_time;
        }
    }


    // turnaround time calculation
    for (int i = 0; i < n; i++)
    {
        a[i].turnaround_time = a[i].completion_time - a[i].arrival_time;
    }


    // waiting time calculation
    for (int i = 0; i < n; i++)
    {
        a[i].waiting_time = a[i].turnaround_time - a[i].burst_time;
    }

    float avgtat;
    float sumtat = 0;
    float avgwt;
    float sumwt = 0;


    //average turnaround time calculation
    for (int i = 0; i < n; i++)
    {
        sumtat = sumtat + a[i].turnaround_time;
    }
    avgtat = sumtat / n;


    //average waiting time calculation
    for (int i = 0; i < n; i++)
    {
        sumwt = sumwt + a[i].waiting_time;
    }
    avgwt = sumwt / n;

    // print fcfs table
    for (int i = 0; i < n; i++)
    {
        cout << "process id: p" << a[i].process_id <<", arrival time: " << a[i].arrival_time << ", burst time: " << a[i].burst_time << ", completition time: " << a[i].completion_time << ", turn around time: " << a[i].turnaround_time << ", waiting time: " << a[i].waiting_time << endl;
    }

    cout << "Average Waiting Time: " << avgwt << "\n";
    cout << "Average Turnaround Time: " << avgtat << "\n";
}