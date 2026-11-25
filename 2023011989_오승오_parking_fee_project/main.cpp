#include <stdio.h>

int main(void)
{
    int cars = 0;       // Number of cars to process.
    int number = 1;     // Current car number.
    int type = 0;
    int time = -1;
    int extra = 0;      // Minutes after the free parking time.
    int blocks = 0;     // Number of ten-minute blocks.
    int fee = 0;
    int discount = 0;   // Discount rate in percent.
    int cut = 0;        // Discount amount in won.

    // Keep the total and highest fee for all cars.
    int total = 0;
    int highest = 0;
    int highestCar = 0;

    // Ask again until the number of cars is between 1 and 10.
    while (cars < 1 || cars > 10)
    {
        printf("Number of cars to settle (1-10): ");
        scanf_s("%d", &cars);

        if (cars < 1 || cars > 10)
        {
            printf("-> Please enter a number between 1 and 10.\n");
        }
    }

    // Process one car at a time.
    while (number <= cars)
    {
        printf("\n[%d-th Car]\n", number);
        printf("Car Type (1: Light, 2: Regular, 3: Electric): ");
        scanf_s("%d", &type);

        // Reset the time so each car asks for a new input.
        time = -1;

        // Ask again if the parking time is negative.
        while (time < 0)
        {
            printf("Parking Time (minutes): ");
            scanf_s("%d", &time);

            if (time < 0)
            {
                printf("-> Please enter 0 or greater: ");
            }
        }

        // Clear the previous car's fee and discount.
        fee = 0;
        discount = 0;

        // Charge only for time over 30 minutes.
        if (time > 30)
        {
            extra = time - 30;

            // Integer division counts full ten-minute blocks.
            blocks = extra / 10;

            // Remaining minutes count as one more block.
            if (extra % 10 > 0)
            {
                blocks = blocks + 1;
            }

            // 40 blocks cost 20000 won, the limit before the discount.
            if (blocks > 40)
            {
                blocks = 40;
            }

            fee = blocks * 500;
        }

        // Choose the discount rate for this car.
        switch (type)
        {
        case 1: // Light car.
            discount = 50;
            break;

        case 2: // Regular car.
            discount = 0;
            break;

        case 3: // Electric car.
            discount = 30;
            break;

        default:
            // An unknown car type keeps the regular rate of 0 percent.
            printf("Applying regular fee policy.\n");
            break;
        }

        // Apply the discount after the fee limit.
        cut = fee * discount / 100;
        fee = fee - cut;

        // Use %% to print one percent sign.
        printf("Fee: %d won (Discount %d%%)\n", fee, discount);

        // Add the amount paid after the discount.
        total = total + fee;

        // Save the first car even if its fee is 0.
        // A later car replaces it only when the fee is greater.
        if (number == 1 || fee > highest)
        {
            highest = fee;
            highestCar = number;
        }

        // Move to the next car.
        number = number + 1;
    }

    // Show the results after all cars are processed.
    printf("\nTotal Revenue: %d won\n", total);
    printf("Highest Fee: Car %d (%d won)\n", highestCar, highest);

    return 0;
}