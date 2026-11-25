#include <stdio.h>

// This function changes the energy using the even or odd rule
int nextEnergy(int energy);


int main()
{
    int energy;       // Stores the current energy
    int maxEnergy;    // Stores the highest energy reached
    int steps = 0;    // Counts how many times the energy changes

    // Get the starting energy from the user
    printf("Enter the initial engine energy: ");
    scanf_s("%d", &energy);

    // Before the energy changes, the starting value is the highest value
    maxEnergy = energy;

    // Print the starting value first
    printf("Sequence: %d", energy);

    // Keep changing the energy while it is not 1
    while (energy != 1)
    {
        // Send the current energy to the function and save the result
        energy = nextEnergy(energy);

        // The energy changed once, so add 1 to the step count
        steps = steps + 1;

        // Print the new value after an arrow
        printf(" -> %d", energy);

        // If the new energy is higher than the saved maximum,
        // save the new energy as the maximum
        if (energy > maxEnergy)
        {
            maxEnergy = energy;
        }
    }

    // The energy is now 1, so print the escape result
    printf("\nEscape successful!\n");

    // Print the total number of changes and the highest energy
    printf("Total steps: %d\n", steps);
    printf("Maximum altitude reached: %d\n", maxEnergy);

    return 0;
}


// Receive the current energy and return the next energy value
int nextEnergy(int energy)
{
    // If the remainder after dividing by 2 is 0, the energy is even
    if (energy % 2 == 0)
    {
        // For an even number, divide the energy by 2
        return energy / 2;
    }
    else
    {
        // For an odd number, multiply the energy by 3 and add 1
        return energy * 3 + 1;
    }
}