#include <iostream>
#include <bits/stdc++.h>

using namespace std;

typedef struct srtn_with_arrivaltime
{
    int arrival_time;
    int burst_time;
    int completion_time = 0;
    int turnaround_time;
    int waiting_time;
    int process_id;
    int remaining_time;
    bool visited = false;
 } srtn;

bool compare(srtn a, srtn b)
{
    if (a.arrival_time < b.arrival_time)
    {
        return true;
    }
    else
    {
        return false;
    }
}


int main()
{
    vector<int> v; 
    int clocktime = 0;

    int n;
    cout << "enter the number of processes: " << endl;
    cin >> n;

    // int time_quanta = 1;


    srtn_with_arrivaltime a[n];

    cout << "enter arrival time and burst time of processes: " << endl;

    for (int i = 0; i < n; i++)
    {
        cin >> a[i].arrival_time >> a[i].burst_time;
        a[i].remaining_time = a[i].burst_time;
        a[i].process_id = i;
    }

    // sorting struct array based on arrival time
    sort(a, a + n, compare);
    int count_comp = 0;

    int index = 0;
    clocktime = a[0].arrival_time;
    

    while (count_comp < n)
    {
        index = -1;
        int min_time = INT_MAX;

        // find the process with shortest remaining time
        for (int k = 0; k < n; k++)
        {
            if (a[k].arrival_time <= clocktime && a[k].visited == false && a[k].remaining_time < min_time)
            {
                min_time = a[k].remaining_time;
                index = k;
            }
        }

        // if no process is found, increment the clocktime
        if (index == -1)
        {
            clocktime++;
            continue;
        }

        // update the process with the shortest remaining time
        a[index].remaining_time--;
        clocktime++;

        if (a[index].remaining_time == 0)
        {
            a[index].completion_time = clocktime;
            a[index].visited = true;
            count_comp++;
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

    // print srtn table
    for (int i = 0; i < n; i++)
    {
        cout << "process id: p" << a[i].process_id + 1 << ", arrival time: " << a[i].arrival_time << ", burst time: " << a[i].burst_time << ", completition time: " << a[i].completion_time << ", turn around time: " << a[i].turnaround_time << ", waiting time: " << a[i].waiting_time << endl;
    }

    cout << "Average Waiting Time: " << avgwt << "\n";
    cout << "Average Turnaround Time: " << avgtat << "\n";
}
