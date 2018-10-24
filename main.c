#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FILE_IN "input.1.txt"

//compare function for out qsort() function
int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main(void)
{

    int process, arrivalTime, burstTime;
    int systemTime = 0;
    int count = 0;
    char str[256];
    int arrivalTimeList[15];

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
            arrivalTimeList[count] = arrivalTime;
        }
        count++;
    }

    qsort(arrivalTimeList, count, sizeof(int), cmpfunc);
    printf("\nAfter sorting the list is: \n");
    for (int n = 0; n < 6; n++)
    {
        printf("%d ", arrivalTimeList[n]);
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