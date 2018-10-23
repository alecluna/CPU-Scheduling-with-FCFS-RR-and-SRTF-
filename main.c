#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FILE_IN "input.1.txt"

int main(void)
{

    int systemTime, arrivalTime, burstTime;
    int count = 0;
    char str[256];

    FILE *input_file;

    input_file = fopen("input.1.txt", "r"); //read

    if (input_file == NULL)
    {
        printf("Error on opening the input file \n");
        exit(EXIT_FAILURE);
    }

    while (fgets(str, sizeof str, input_file))
    {
        char *p = strchr(str, '\n');
        if (p)
            *p = 0; // remove the trailing newline, if

        if (sscanf(str, "%d %d %d", &systemTime, &arrivalTime, &burstTime) == 3)
        {
            printf("\nCurrent System Time:  %d\n", systemTime);
            printf("\nArrival Time:   %d\n", arrivalTime);
            printf("%d %d %d\n", systemTime, arrivalTime, burstTime);
            /* do processing with i, j & k */
        }
        else
        {
            perror("Error:");
        }
    }

    fclose(input_file);
    return EXIT_SUCCESS;
}