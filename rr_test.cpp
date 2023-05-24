#include <iostream>
#include <bits/stdc++.h>
using namespace std;
typedef struct rr_with_arrivaltime
{
    int arrival_time;
    int burst_time;
    int completion_time = 0;
    int turnaround_time;
    int waiting_time;
    int process_id;
    int remaining_time;
    bool visited = false;
    bool running = false;
} rr;
bool compare(rr a, rr b)
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
    queue<int> q;
    int clocktime = 0;
    int n;
    cout << "enter the number of processes: " << endl;
    cin >> n;
    int time_quanta = 0;
    cout << "enter the time quantum of process: " << endl;
    cin >> time_quanta;
    rr_with_arrivaltime a[n];
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
    a[0].running = true;
    clocktime = a[0].arrival_time;
    q.push(0);
    while (count_comp < n)
    {
        index = q.front();
        q.pop();
        int var = min(time_quanta, a[index].remaining_time);
        clocktime = clocktime + var;
        a[index].remaining_time = a[index].remaining_time - var;
        if (a[index].remaining_time != 0)
        {
            for (int k = 0; k < n; k++)
            {
                if (a[k].arrival_time <= clocktime && a[k].process_id != a[index].process_id && a[k].running == false && a[k].visited == false)
                {
                    a[k].running = true;
                    q.push(k);
                }
            }
            q.push(index);
        }
        else
        {
            a[index].completion_time = clocktime;
            a[index].visited = true;
            a[index].running = false;
            count_comp++;
            for (int k = 0; k < n; k++)
            {
                if (a[k].arrival_time <= clocktime && a[k].process_id != a[index].process_id && a[k].running == false && a[k].visited == false)
                {
                    a[k].running = true;
                    q.push(k);
                }
            }
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
    // print rr table
    for (int i = 0; i < n; i++)
    {
        cout << "process id: p" << a[i].process_id << ", arrival time: " << a[i].arrival_time << ", burst time: " << a[i].burst_time << ", completition time: " << a[i].completion_time << ", turn around time: " << a[i].turnaround_time << ", waiting time: " << a[i].waiting_time << endl;
    }
    cout << "Average Waiting Time: " << avgwt << "\n";
    cout << "Average Turnaround Time: " << avgtat << "\n";
}

// #include <iostream>
// #include <bits/stdc++.h>

// using namespace std;

// typedef struct rr_with_arrivaltime
// {
//     int arrival_time;
//     int burst_time;
//     int completion_time = 0;
//     int turnaround_time;
//     int waiting_time;
//     int process_id;
//     int remaining_time;
//     bool visited = false;
//     bool running = false;
// } rr;

// bool compare(rr a, rr b)
// {
//     if (a.arrival_time < b.arrival_time)
//     {
//         return true;
//     }
//     else
//     {
//         return false;
//     }
// }

// int main()
// {
//     // queue<sjf_with_arrivaltime> q;
//     queue<int> q;
//     int clocktime = 0;

//     int n;
//     cout << "enter the number of processes: " << endl;
//     cin >> n;

//     int time_quanta = 0;
//     cout << "enter the time quantum of process: " << endl;
//     cin >> time_quanta;

//     rr_with_arrivaltime a[n];
//     // sjf_with_arrivaltime c[n];

//     cout << "enter arrival time and burst time of processes: " << endl;

//     for (int i = 0; i < n; i++)
//     {
//         cin >> a[i].arrival_time >> a[i].burst_time;
//         a[i].remaining_time = a[i].burst_time;
//         a[i].process_id = i;
//     }

//     // sorting struct array based on arrival time
//     sort(a, a + n, compare);
//     int count_comp = 0;

//     int index = 0;
//     a[0].running = true;
//     clocktime = a[0].arrival_time;
//     q.push(0);
//     cout << "index before: " << index << endl;

//     while (count_comp < n)
//     {
//         index = q.front();
//         q.pop();
//         cout << "stage1"
//              << "entered while" << endl;

//         cout << "index after: " << index << endl;

//         cout << "process id: p" << a[index].process_id << ", arrival time: " << a[index].arrival_time << ", burst time: " << a[index].burst_time << " remaining time: " << a[index].remaining_time << " completion time: " << a[index].completion_time << endl;

//         // if (a[index].remaining_time > time_quanta)
//         // {
//         //     a[index].remaining_time = a[index].remaining_time - time_quanta;
//         //     clocktime = clocktime + time_quanta;

//         //     cout << "stage2"
//         //          << "> || < time quanta"
//         //          << "if" << endl;
//         // cout << "process id: p" << a[index].process_id << ", arrival time: " << a[index].arrival_time << ", burst time: " << a[index].burst_time << " remaining time: " << a[index].remaining_time << " completion time: " << a[index].completion_time << endl;

//         // }
//         // else if (a[index].remaining_time <= time_quanta)
//         // {
//         //     clocktime = clocktime + a[index].remaining_time;
//         //     a[index].remaining_time = 0;
//         //     cout << "stage2"
//         //          << "> || < time quanta"
//         //          << "else" << endl;

//         //     cout << "clocktime "
//         //          << " for pid: " << a[index].process_id << " is " << clocktime << endl;
//         // }
//         // else{}
//         int var = min(time_quanta,a[index].remaining_time);

//         clocktime = clocktime + var;
//         a[index].remaining_time = a[index].remaining_time - var;

//         if (a[index].remaining_time != 0)
//         {
//             for (int k = 0; k < n; k++)
//             {
//                 if (a[k].arrival_time <= clocktime && a[k].process_id != a[index].process_id && a[k].running == false && a[k].visited == false)
//                 {
//                     cout << "stage3" << "> || < process queue addition: " << "if" << endl;

//                     cout << "process added o queue id: p" << a[k].process_id << ", arrival time: " << a[k].arrival_time << ", burst time: " << a[k].burst_time << " remaining time: " << a[k].remaining_time << " completion time: " << a[k].completion_time << endl;
//                     a[k].running = true;
//                     q.push(k);
//                 }
//             }
//             q.push(index);
//         }
//         else
//         {
//             a[index].completion_time = clocktime;
//             a[index].visited = true;
//             a[index].running = false;
//             count_comp++;

//             for (int k = 0; k < n; k++)
//             {
//                  if (a[k].arrival_time <= clocktime && a[k].process_id != a[index].process_id && a[k].running == false && a[k].visited == false)
//                 {
//                     cout << "stage3" << "> || < process queue addition: " << "else" << endl;

//                     cout << "process added o queue id: p" << a[k].process_id << ", arrival time: " << a[k].arrival_time << ", burst time: " << a[k].burst_time << " remaining time: " << a[k].remaining_time << " completion time: " << a[k].completion_time << endl;
//                     a[k].running = true;
//                     q.push(k);
//                 }
//             }
//         }
//     }

//     // turnaround time calculation
//     for (int i = 0; i < n; i++)
//     {
//         a[i].turnaround_time = a[i].completion_time - a[i].arrival_time;
//     }

//     // waiting time calculation
//     for (int i = 0; i < n; i++)
//     {
//         a[i].waiting_time = a[i].turnaround_time - a[i].burst_time;
//     }

//     float avgtat;
//     float sumtat = 0;
//     float avgwt;
//     float sumwt = 0;

//     // average turnaround time calculation
//     for (int i = 0; i < n; i++)
//     {
//         sumtat = sumtat + a[i].turnaround_time;
//     }
//     avgtat = sumtat / n;

//     // average waiting time calculation
//     for (int i = 0; i < n; i++)
//     {
//         sumwt = sumwt + a[i].waiting_time;
//     }
//     avgwt = sumwt / n;

//     // print sjf table
//     for (int i = 0; i < n; i++)
//     {
//         cout << "process id: p" << a[i].process_id << ", arrival time: " << a[i].arrival_time << ", burst time: " << a[i].burst_time << ", completition time: " << a[i].completion_time << ", turn around time: " << a[i].turnaround_time << ", waiting time: " << a[i].waiting_time << endl;
//     }

//     cout << "Average Waiting Time: " << avgwt << "\n";
//     cout << "Average Turnaround Time: " << avgtat << "\n";
// }

