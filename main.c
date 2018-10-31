#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define length 6
typedef int bool;
#define true 1
#define false 0

typedef struct dataSection
{
    int process;
    int arrival;
    int burst;
    struct dataSection *next; //reference to next dataSection node in LL

} dataSection;

dataSection empty = {-1, -1, 0, NULL}; //initialize our empty struct

struct Queue
{
    struct dataSection *front, *rear;
};

void findWaitingTime(int processList[], int size,
                     int burstTimeList[], int waitTimeList[])
{
    waitTimeList[0] = 0; //first one to arrive is always 0
    for (int i = 1; i <= size + 1; i++)
    {
        waitTimeList[i] = burstTimeList[i - 1] + waitTimeList[i - 1];
        printf("Wait time List read inside wait time function: %d\n", waitTimeList[i - 1]);
        printf("%d\n", size);
    }
}

void findTurnAroundTime(int processList[], int size,
                        int burstTimeList[], int waitTimeList[], int turnAroundTimeList[])
{

    for (int i = 0; i < size; i++)
        turnAroundTimeList[i] = burstTimeList[i] + waitTimeList[i];
}

//Function to calculate average time
void findavgTime(int processList[], int size, int burstTimeList[])
{
    int waitTime[size], turnaroundTimeList[size], total_tat = 0;
    int totalWaitTime = 0;

    //Function to find waiting time of all processes
    findWaitingTime(processList, size, burstTimeList, waitTime);
    findTurnAroundTime(processList, size, burstTimeList, waitTime, turnaroundTimeList);

    for (int i = 0; i < size; i++)
        printf("\n Wait time list after exiting function: %d \n", waitTime[i]);

    printf("Processes   Burst time   Waiting time  Turnaround Time\n");

    // Calculate total waiting time and total turn
    // around time
    for (int i = 0; i < size; i++)
    {
        totalWaitTime = totalWaitTime + waitTime[i];
        total_tat = total_tat + turnaroundTimeList[i];
        printf("   %d", (i + 1));
        printf("        %d", burstTimeList[i]);
        printf("            %d", waitTime[i]);
        printf("               %d\n", turnaroundTimeList[i]);
    }
    int averageWaitTime = (float)totalWaitTime / (float)size;
    int tat = (float)total_tat / (float)size;
    printf("Average waiting time = %d", averageWaitTime);
    printf("\n");
    printf("Average turn around time = %d ", tat);
}

void roundRobinAlgo(struct dataSection **head_ref, int timeQuantum)
{
    int systemTime;
    struct dataSection *current = *head_ref;
    while (current != NULL)
    {

        printf("\n<System Time %d> process %d is running... with Time Quantum %d\n", systemTime, current->process, timeQuantum);

        current = current->next;
        systemTime++;
    }
}

static void reverse(struct dataSection **head)
{
    struct dataSection *prev = NULL;
    struct dataSection *current = *head;
    struct dataSection *next = NULL;
    while (current != NULL)
    {
        next = current->next;

        current->next = prev;

        prev = current;
        current = next;
    }
    *head = prev;
}

int main(int argc, char *argv[])
{

    if (argc > 3) //error validate more than 4 args
    {
        printf("Incorrect number of arguments\n");
        return 1;
    }
    int process, arrivalTime, burstTime;
    int systemTime = 0;
    int count = 0;
    int totalJobs = 0;
    char str[256];
    dataSection *ptr = NULL;
    struct dataSection *n1, *n = NULL;

    int waitTimeList[length];
    int processList[length];
    int burstTimeList[length];

    FILE *input_file;

    input_file = fopen(argv[1], "r"); //read

    if (input_file == NULL)
    {
        printf("Error on opening the input file \n");
        exit(EXIT_FAILURE);
    }

    while (fgets(str, sizeof str, input_file)) //read input file
    {
        char *p = strchr(str, '\n');
        if (p)
            *p = 0; // weird hack to remove the trailing newline

        if (sscanf(str, "%d %d %d", &process, &arrivalTime, &burstTime) == 3)
        {

            dataSection *next;                                 //need a temp pointer to reference the next dataSection
            next = (dataSection *)malloc(sizeof(dataSection)); //otherwise we'd overwrite the current ptr's dataSection
            next->next = ptr;                                  //increment our linked list
            ptr = next;
            ptr->process = process; //assign necessary variables
            ptr->arrival = arrivalTime;
            ptr->burst = burstTime;
            processList[count] = ptr->process;
            burstTimeList[count] = ptr->burst;
            count++;
            totalJobs++;
        }
        else
        {
            printf("error reading input text, needs to be in a 3 colunm format");
        }
    }
    fclose(input_file);

    printf("Selected Algorithm: %s\n", argv[2]);
    printf("Total %d tasks are read from \"%s\". press 'enter' to start...\n", totalJobs, input_file);
    printf("==================================================================\n");
    if (strcmp(argv[2], "FCFS") == 0)
    {
        reverse(&ptr); //reverse linked list, was trversing backwards for some reason

        while (ptr->next != NULL)
        {
            int tempBurstTime = ptr->burst;
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
                    systemTime++;
                }
            }
            ptr = ptr->next;
        }
        printf("<system time %d> All processes finished....................\n", systemTime);

        //findavgTime(processList, size, burstTimeList);
    }
    // else if ((strcmp(argv[2], "RR") == 0) && (atoi(argv[3]) >= 1))
    // {
    //     reverse(&ptr);
    //     int timeQuantum = atoi(argv[3]);
    //     int rem_bt[length];
    //     //map a new burst time array
    //     for (int i = 0; i < length; i++)
    //         rem_bt[i] = burstTimeList[i];

    //     printf("RR algo %s\n", argv[2]);
    //     printf("Time Quantum: %d\n", timeQuantum);

    //     roundRobinAlgo(&ptr, timeQuantum);
    // }
    // else if (strcmp(argv[2], "SRTF") == 0)
    // {
    //     n1 = ptr = sortBurst(ptr);
    //     sortBurst(ptr);

    //     printf("SRTF algo %s\n", argv[2]);
    //     while (ptr)
    //     {
    //         printf("Actual order of LL Node being read: %d  %d\n", ptr->process, ptr->burst);
    //         ptr = ptr->next;
    //     }
    // }
    // else
    // {
    //     perror("Error with input or Time Quantum entered was less than 1");
    // }

    //calculate average here
    // for (int i = 0; i < 6; i++){
    //     printf("Process List array that will be passed into the average time function: %d  %d\n", processList[i],burstTimeList[i]);
    // }
    // int size = sizeof processList / sizeof processList[0];
    // findavgTime(processList, size, burstTimeList);
    printf("\n");
    return EXIT_SUCCESS;
}
