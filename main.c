#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FILE_IN "input.1.txt"
#define length 6

int main(void)
{

    int process, arrivalTime, burstTime;
    int systemTime = 0;
    int count = 0;
    char str[256];
    int arrival[length];
    int burst[length];

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
            arrival[count] = arrivalTime;
            burst[count] = burstTime;
        }
        count++;
    }

    for (int n = 0; n < 6; n++)
    {
        printf("arrival time: %d, burst time: %d\n", arrival[n], burst[n]);
    }

    // while (burstTime >= 0)
    // {
    //     printf("\nCurrent burst time: %d", burstTime);
    //     printf("\n<System Time     %d>", systemTime);
    //     burstTime--;
    //     //go to next process
    //     if (burstTime == 0)
    //     {
    //         printf("\nCurrent burst time: %d", burstTime);
    //         printf("\n<System Time     %d>", systemTime);
    //         printf("\n****switch to next process");
    //     }
    // }

    fclose(input_file);
    return EXIT_SUCCESS;
}