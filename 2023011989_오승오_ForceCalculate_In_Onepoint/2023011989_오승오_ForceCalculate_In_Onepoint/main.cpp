#include <stdio.h>
#include <math.h>

// Function declarations
double CalcMagnitude(double* force);
int FindLargest(double* magnitude);


int main(void)
{
    const char* strCableName[4] = 
    {"Cable-1", "Cable-2", "Cable-3", "Cable-4"};

    // Each row : {Fx, Fy, Fz}
    double dArrCableForce[4][3] = 
    {{ 120.0, 50.0, -30.0 },
        { -80.0, 140.0, 60.0 },
        { 45.0, -95.0, 110.0 },
        { -60.0, -70.0, -150.0 } };

    double magnitude[4];
    double resultant[3] = { 0.0 };
    double * force;

    int i, j, largest;

    printf("%-9s%8s%8s%8s |%8s   [N]\n",
        "Force", "Fx", "Fy", "Fz", "|F|");


    // Calculate each cable force.
    for (i = 0; i < 4; i++)
    {
        force = *(dArrCableForce + i);
        magnitude[i] = CalcMagnitude(force);

        printf("%-9s", *(strCableName + i));

        for (j = 0; j < 3; j++)
        {
            printf("%8.1f", *(force + j));
            resultant[j] += *(force + j);
        }

        printf(" |%8.1f\n", magnitude[i]);
    }


    // Print the resultant force.
    printf("%-9s%8.1f%8.1f%8.1f |%8.1f\n",
        "Resultant", resultant[0], resultant[1], resultant[2],
        CalcMagnitude(resultant));


    largest = FindLargest(magnitude);

    printf("Largest force : %s (%.1f N)\n",
        strCableName[largest], magnitude[largest]);

    return 0;
}


// Calculate the magnitude of a force.
double CalcMagnitude(double* force)
{
    double fx = *force;
    double fy = *(force + 1);
    double fz = *(force + 2);

    return sqrt(fx * fx + fy * fy + fz * fz);
}


// Sort cable indices in descending order.
int FindLargest(double* magnitude)
{
    int order[4] = { 0, 1, 2, 3 };
    int i, j, temp;

    for (i = 0; i < 3; i++)
    {
        for (j = i + 1; j < 4; j++)
        {
            if (magnitude[order[i]] < magnitude[order[j]])
            {
                temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }

    return order[0];
}