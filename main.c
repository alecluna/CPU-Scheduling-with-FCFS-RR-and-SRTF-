#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FILE_IN "input.1.txt"
#define length 6
typedef struct dataSection
{
    int process;
    int arrival;
    int burst;
    struct dataSection *next; //reference to next dataSection node in LL

} dataSection;

dataSection empty = {-1, -1, 0, NULL}; //initialize our empty struct
int main(void)
{

    int process, arrivalTime, burstTime;
    int systemTime = 0;
    int count = 0;
    char str[256];
    int arrival[length];
    int burst[length];
    int waitTime[length];
    dataSection *ptr = NULL;

    FILE *input_file;

    input_file = fopen("input.1.txt", "r"); //read

    if (input_file == NULL)
    {
        printf("Error on opening the input file \n");
        exit(EXIT_FAILURE);
    }

    //read input file first
    while (fgets(str, sizeof str, input_file))
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
        }
        else
        {
            printf("error reading input text, needs to be in a 3 colunm format");
        }
    }

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

    // for (int n = 0; n < 6; n++)
    // {
    //     printf("arrival time: %d, burst time: %d\n", arrival[n], burst[n]);
    // }

    // for (int i = 0; i < length; i++)
    // {

    //     arrivalTime = arrival[i];
    //     burstTime = burst[i];
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
    //}

    fclose(input_file);
    return EXIT_SUCCESS;
}