#include <stdio.h>

// Number of digits required for a birthdate
#define BIRTH_DATE_DIGITS 8

// Codes returned when the input cannot be used
#define INPUT_END (-1)            // No more input is available
#define INPUT_EMPTY (-2)          // The line is empty or contains only spaces
#define INPUT_NOT_DIGIT (-3)      // The line contains an invalid character
#define INPUT_WRONG_LENGTH (-4)   // The number of digits is not 8
#define INPUT_ERROR (-5)          // An error occurred while reading input

// Function declarations
int readBirthDate(void);        // Read one line and check the input format
int sumDigits(int number);      // Add the digits of a number once
void printFortune(int number);  // Print the message for the destiny number


int main()
{
    int birthDate;
    int number;
    int sum;

    // Keep asking until a usable 8-digit input is entered
    while (1)
    {
        printf("Enter your 8-digit birthdate (YYYYMMDD): ");
        birthDate = readBirthDate();

        // End the program if no more input can be read
        if (birthDate == INPUT_END)
        {
            printf("\nNo more input. The program will end.\n");
            return 1;
        }
        else if (birthDate == INPUT_ERROR)
        {
            printf("\nInput error. The program will end.\n");
            return 1;
        }
        else if (birthDate == INPUT_EMPTY)
        {
            printf("Error: Nothing was entered. Please type your birthdate.\n");
            continue;
        }
        else if (birthDate == INPUT_NOT_DIGIT)
        {
            printf("Error: Use digits only. Letters, symbols, signs, and spaces between digits are not allowed.\n");
            continue;
        }
        else if (birthDate == INPUT_WRONG_LENGTH)
        {
            printf("Error: The birthdate must be exactly 8 digits (example: 20041225).\n");
            continue;
        }

        // All zeros cannot produce a destiny number from 1 to 9
        if (birthDate == 0)
        {
            printf("Error: 00000000 cannot produce a destiny number from 1 to 9.\n");
            continue;
        }

        // The input is usable, so leave the input loop
        break;
    }

    // Keep the original input and use number for calculation
    number = birthDate;

    printf("Calculating...\n");

    // Add the digits and repeat if the result has two or more digits
    do
    {
        sum = sumDigits(number);
        printf("Sum of digits: %d\n", sum);

        // Use this sum as the number for the next round
        number = sum;
    } while (sum >= 10);

    printf("Your Destiny Number is %d!\n", sum);
    printf("\n[Destiny Message]\n");
    printFortune(sum);

    return 0;
}


// Read one line and return the number or an input result code
int readBirthDate(void)
{
    char inputChar;
    int digitCount = 0;
    int birthDate = 0;
    int hasInvalidChar = 0;
    int hasSpaceAfterDigit = 0;
    int hasReadAnyChar = 0;

    // Read one character at a time until the line ends
    while (1)
    {
        if (scanf_s("%c", &inputChar, 1u) != 1)
        {
            // Stop if the input stream has a reading error
            if (ferror(stdin))
            {
                return INPUT_ERROR;
            }

            // If no character was read, there is no more input
            if (hasReadAnyChar == 0)
            {
                return INPUT_END;
            }

            // Check the characters already read before input ended
            break;
        }

        hasReadAnyChar = 1;

        // A newline marks the end of the current input line
        if (inputChar == '\n')
        {
            break;
        }

        if (inputChar >= '0' && inputChar <= '9')
        {
            // A digit after a space means there is a space between digits
            if (hasSpaceAfterDigit == 1)
            {
                hasInvalidChar = 1;
            }

            // Build the number using only the first 8 digits
            if (digitCount < BIRTH_DATE_DIGITS)
            {
                birthDate = birthDate * 10 + (inputChar - '0');
            }

            // Stop counting at 9 to prevent the counter from growing
            if (digitCount <= BIRTH_DATE_DIGITS)
            {
                digitCount++;
            }
        }
        else if (inputChar == ' ' || inputChar == '\t' || inputChar == '\r')
        {
            // Spaces before or after the digits are allowed
            if (digitCount > 0)
            {
                hasSpaceAfterDigit = 1;
            }
        }
        else
        {
            // Record invalid characters and continue reading the line
            hasInvalidChar = 1;
        }
    }

    // Return a code describing the first applicable input problem
    if (hasInvalidChar == 1)
    {
        return INPUT_NOT_DIGIT;
    }

    if (digitCount == 0)
    {
        return INPUT_EMPTY;
    }

    if (digitCount != BIRTH_DATE_DIGITS)
    {
        return INPUT_WRONG_LENGTH;
    }

    return birthDate;
}


// Calculate and return the sum of the digits
int sumDigits(int number)
{
    int sum = 0;

    while (number > 0)
    {
        // Add the last digit, then remove it using integer division
        sum = sum + number % 10;
        number = number / 10;
    }

    return sum;
}


// Print the fortune message that matches the destiny number
void printFortune(int number)
{
    switch (number)
    {
    case 1:
        printf("Good times come after hardship.\n");
        break;

    case 2:
        printf("Many people will love you.\n");
        break;

    case 3:
        printf("You will be able to get an A+ in this course.\n");
        break;

    case 4:
        printf("You will definitely get a perfect score on this midterm.\n");
        break;

    case 5:
        printf("You will always be healthy.\n");
        break;

    case 6:
        printf("If you keep trying, your efforts will surely pay off.\n");
        break;

    case 7:
        printf("Everyone you love will do well.\n");
        break;

    case 8:
        printf("Your life will always be full of happiness.\n");
        break;

    case 9:
        printf("Even a difficult situation will eventually come to an end.\n");
        break;

    default:
        printf("No fortune message is available.\n");
        break;
    }
}