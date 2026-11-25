#include <stdio.h>   

// Function declarations


int sumDigits(int number);       // Returns the sum of all digits of number
void printFortune(int number);   // Prints the fortune message for a number from 1 to 9


int main()
{
    int birthDate;    // Birth date entered by the user (YYYYMMDD)
    int number;       // Number whose digits are added in each round
    int sum;          // Sum of the digits in the current round

    
    // Ask the user for the birth date and read it as an integer
    
    printf("Enter your 8-digit birth date: ");
    scanf_s("%d", &birthDate);    

    // Copy the birth date for calculation
    // (birthDate keeps the original value, and only number is changed)

    number = birthDate;

    printf("Calculating your destiny number...\n");

    // Repeat until the sum becomes a single digit
    // do-while is used because the digits must be added at least once

    do
    {
        sum = sumDigits(number);              // Add all digits of the current number
        printf("Sum of digits: %d\n", sum);   // Show the result of the first round
        number = sum;                         // The sum becomes the number for the next round
    } while (sum >= 10);    // A sum of 10 or more has two or more digits, so repeat

    // sum is a single digit: The destiny number
    
    printf("Your destiny number is: %d\n", sum);
    printf("\n[Destiny Message]\n");
    printFortune(sum);    // Print the message that matches the destiny number


    return 0;    
}


// Calculate the sum of the digits

int sumDigits(int number)
{
    int sum = 0;    // Start from 0

    // Take off the last digit one by one until no digits are left
    while (number > 0)
    {
        sum = sum + number % 10;    // number % 10 is the last digit 
        number = number / 10;       // Integer division removes the last digit 
    }

    return sum;    // Send the sum back to main
}

// Print the fortune message for the destiny number
// switch chooses one case by the value of number, and break stops after that case

void printFortune(int number)
{
    switch (number)
    {
    case 1:    // Destiny number 1
        printf("Good times come after hardship.\n");
        break;
    case 2:    // Destiny number 2
        printf("Many people will love you.\n");
        break;
    case 3:    // Destiny number 3
        printf("You will be able to get an A+ in this course.\n");
        break;
    case 4:    // Destiny number 4
        printf("You will definitely get a perfect score on this midterm.\n");
        break;
    case 5:    // Destiny number 5
        printf("You will always be healthy.\n");
        break;
    case 6:    // Destiny number 6
        printf("If you keep trying, your efforts will surely pay off.\n");
        break;
    case 7:    // Destiny number 7
        printf("Everyone you love will do well.\n");
        break;
    case 8:    // Destiny number 8
        printf("Your life will always be full of happiness.\n");
        break;
    case 9:    // Destiny number 9
        printf("Even a difficult situation will eventually come to an end.\n");
        break;
    default:   // Any other value (e.g., 0) has no message
        printf("No fortune message is available.\n");
        break;
    }
}


// Before checking errors caused by exception input values

// MUST BE DEVELOPED TO ADRESS EXCEPTIONAL INPUT CASES