#include <stdio.h>

// Function declaration
void Sort(double* pa, int size);


int main(void)
{
    double dArrEngATemp[5] = { 612.5, 618.0, 615.3, 620.1, 616.4 };
    double dArrEngBTemp[5] = { 605.2, 640.8, 598.7, 652.3, 610.0 };
    double dArrEngCTemp[5] = { 630.0, 628.4, 633.9, 631.2, 629.5 };

    double* dEgt[3] = { dArrEngATemp, dArrEngBTemp, dArrEngCTemp };

    const char* strEngName[3] = { "ENG-A", "ENG-B", "ENG-C" };

    double range[3];
    int i, j, largest = 0;


    printf("%-6s%7s%7s%7s%7s%7s |%7s%7s%7s\n",
        "Engine", "#1", "#2", "#3", "#4", "#5",
        "Min", "Max", "Range");


    // Print the measured temperatures
    for (i = 0; i < 3; i++)
    {
        printf("%-6s", strEngName[i]);

        for (j = 0; j < 5; j++)
        {
            printf("%7.1f", dEgt[i][j]);
        }

        // Sort the temperatures and calculate the range
        Sort(dEgt[i], 5);

        range[i] = dEgt[i][4] - dEgt[i][0];

        printf(" |%7.1f%7.1f%7.1f\n",
            dEgt[i][0], dEgt[i][4], range[i]);
    }


    // Find the largest range
    for (i = 1; i < 3; i++)
    {
        if (range[i] > range[largest])
        {
            largest = i;
        }
    }

    printf("Largest variation : %s (%.1f deg C)\n",
        strEngName[largest], range[largest]);

    return 0;
}


// Sorting order
void Sort(double* pa, int size)
{
    int i, j;
    double temp;

    for (i = 0; i < size - 1; i++)
    {
        for (j = i + 1; j < size; j++)
        {
            if (pa[i] > pa[j])
            {
                temp = pa[i];
                pa[i] = pa[j];
                pa[j] = temp;
            }
        }
    }
}