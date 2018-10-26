#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define FILE_IN "input.1.txt"
#define length 20
typedef struct dataSection
{
    int process;
    int arrival;
    int burst;
    struct dataSection *next; //reference to next dataSection node in LL

} dataSection;

dataSection empty = {-1, -1, 0, NULL}; //initialize our empty struct

void findWaitingTime(int processes[], int n,
                     int burstTimeList[], int waitTimeList[])
{
    // waiting time for first process is 0
    waitTimeList[0] = 0;

    // calculating waiting time
    for (int i = 1; i < n; i++)
        waitTimeList[i] = burstTimeList[i - 1] + waitTimeList[i - 1];
}

// Function to calculate turn around time
void findTurnAroundTime(int processes[], int n,
                        int burstTimeList[], int waitTimeList[], int turnaroundTime[])
{
    // calculating turnaround time by adding
    // bt[i] + wt[i]
    for (int i = 0; i < n; i++)
        turnaroundTime[i] = burstTimeList[i] + waitTimeList[i];
}

//Function to calculate average time
void findavgTime(int processes[], int n, int burstTimeList[])
{
    int waitTimeList[n], turnaroundTime[n], total_wt = 0, total_tat = 0;

    //Function to find waiting time of all processes
    findWaitingTime(processes, n, burstTimeList, waitTimeList);

    //Function to find turn around time for all processes
    findTurnAroundTime(processes, n, burstTimeList, waitTimeList, turnaroundTime);

    //Display processes along with all details
    printf("Processes   Burst time   Waiting time   Turn around time\n");

    // Calculate total waiting time and total turn
    // around time
    for (int i = 0; i < n; i++)
    {
        total_wt = total_wt + waitTimeList[i];
        total_tat = total_tat + turnaroundTime[i];
        printf("   %d ", (i + 1));
        printf("       %d ", burstTimeList[i]);
        printf("       %d", waitTimeList[i]);
        printf("       %d\n", turnaroundTime[i]);
    }
    int s = (float)total_wt / (float)n;
    int t = (float)total_tat / (float)n;
    printf("Average waiting time = %d", s);
    printf("\n");
    printf("Average turn around time = %d ", t);
}

int main(int argc, char *argv[])
{

    int process, arrivalTime, burstTime;
    int systemTime = 0;
    int count = 0;
    char str[256];

    int waitTime[length];
    dataSection *ptr = NULL;

    FILE *input_file;

    input_file = fopen("input.1.txt", "r"); //read

    if (input_file == NULL)
    {
        printf("Error on opening the input file \n");
        exit(EXIT_FAILURE);
    }

    waitTime[0] = 0;                           //initialize first wait time
    while (fgets(str, sizeof str, input_file)) //read input file
    {
        char *p = strchr(str, '\n');
        if (p)
            *p = 0; // weird hack to remove the trailing newline

        if (sscanf(str, "%d %d %d", &process, &arrivalTime, &burstTime) == 3)
        {

            dataSection *temp;                                 //need a temp pointer to reference the next dataSection
            temp = (dataSection *)malloc(sizeof(dataSection)); //otherwise we'd overwrite the current ptr's dataSection
            temp->next = ptr;                                  //increment our linked list
            ptr = temp;
            ptr->process = process; //assign necessary variables
            ptr->arrival = arrivalTime;
            ptr->burst = burstTime;

            printf("%d %d %d\n", ptr->process, ptr->arrival, ptr->burst);

            if (strcmp(argv[1], "FCFS") == 0)
            {

                //  Input the processes along with their burst time (bt).
                // 2-  Find waiting time (wt) for all processes.
                // 3-  As first process that comes need not to wait so
                //     waiting time for process 1 will be 0 i.e. wt[0] = 0.
                // 4-  Find waiting time for all other processes i.e. for
                //      process i ->
                //        wt[i] = bt[i-1] + wt[i-1] .
                // 5-  Find turnaround time = waiting_time + burst_time
                //     for all processes.
                // 6-  Find average waiting time =
                //                  total_waiting_time / no_of_processes.
                // 7-  Similarly, find average turnaround time =
                //                  total_turn_around_time / no_of_processes.
                int tempBurstTime = burstTime;
                while (tempBurstTime >= 0)
                {
                    if (tempBurstTime == 0)
                    {
                        printf("\n<System Time %d> process %d is finished!\n", systemTime, ptr->process);
                        break;
                    }
                    else
                    {
                        printf("\n<System Time %d> process %d is running...\n", systemTime, ptr->process);
                        tempBurstTime--;
                    }
                    systemTime++;
                }
            }
            else if (strcmp(argv[1], "RR") == 0)
            {

                printf("RR algo %s\n", argv[1]);
            }
            else if (strcmp(argv[1], "SJF") == 0)
            {
                printf("SJF algo %s\n", argv[1]);
            }
            else
            {
                perror("Error with input");
            }
        }
        else
        {
            printf("error reading input text, needs to be in a 3 colunm format");
        }
    }

    // for (int i = 0; i < length; i++)
    // {

    //     process = 0;
    //     while (burstTime >= 0)
    //     {
    //         if (burstTime == 0)
    //         {
    //             printf("\nCurrent burst time: %d", burstTime);
    //             printf("\n<System Time     %d>", systemTime);
    //             printf("\n****switch to next process");
    //             break;
    //         }
    //         else
    //         {
    //             printf("\nCurrent burst time: %d", burstTime);
    //             printf("\n<System Time     %d>", systemTime);
    //         }
    //         burstTime--;
    //         systemTime++;
    //     }
    //     process++;
    // }

    fclose(input_file);
    return EXIT_SUCCESS;
}