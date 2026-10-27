#include <stdio.h>

// Constants for input validation
#define BIRTH_DATE_DIGITS 8       // Number of digits required for input

// Input result codes
#define INPUT_END (-1)            // Input ended before a line was read
#define INPUT_EMPTY (-2)          // The line is empty or contains only spaces
#define INPUT_NOT_DIGIT (-3)      // Invalid character or space between digits
#define INPUT_WRONG_LENGTH (-4)   // The input does not contain exactly 8 digits
#define INPUT_ERROR (-5)          // An input stream error occurred

// Function declarations
int readBirthDate(void);       // Read and check the input format
int sumDigits(int number);     // Return the sum of a number's digits
void printFortune(int number);  // Print the message for the final digit


int main()
{
    int birthDate;
    int number;
    int sum;

    // Retry until the input can produce a destiny number from 1 to 9
    while (1)
    {
        printf("Enter your 8-digit birthdate (YYYYMMDD): ");
        birthDate = readBirthDate();

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

        if (birthDate == 0)
        {
            printf("Error: 00000000 cannot produce a destiny number from 1 to 9.\n");
            continue;
        }

        break;
    }

    number = birthDate;

    printf("Calculating...\n");

    // Repeat until the sum becomes a single digit
    do
    {
        sum = sumDigits(number);
        printf("Sum of digits: %d\n", sum);
        number = sum;
    } while (sum >= 10);

    printf("Your Destiny Number is %d!\n", sum);
    printf("\n[Destiny Message]\n");
    printFortune(sum);

    return 0;
}


// Read and validate a complete input line
int readBirthDate(void)
{
    char inputChar;
    int digitCount = 0;
    int birthDate = 0;
    int hasInvalidChar = 0;
    int hasSpaceAfterDigit = 0;
    int hasReadAnyChar = 0;

    while (1)
    {
        if (scanf_s("%c", &inputChar, 1u) != 1)
        {
            // Do not accept a partial line after an input error
            if (ferror(stdin))
            {
                return INPUT_ERROR;
            }

            if (hasReadAnyChar == 0)
            {
                return INPUT_END;
            }

            break;
        }

        hasReadAnyChar = 1;

        if (inputChar == '\n')
        {
            break;
        }

        if (inputChar >= '0' && inputChar <= '9')
        {
            if (hasSpaceAfterDigit == 1)
            {
                hasInvalidChar = 1;
            }

            if (digitCount < BIRTH_DATE_DIGITS)
            {
                birthDate = birthDate * 10 + (inputChar - '0');
            }

            if (digitCount <= BIRTH_DATE_DIGITS)
            {
                digitCount++;
            }
        }
        else if (inputChar == ' ' || inputChar == '\t' || inputChar == '\r')
        {
            if (digitCount > 0)
            {
                hasSpaceAfterDigit = 1;
            }
        }
        else
        {
            hasInvalidChar = 1;
        }
    }

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


// Add the digits once
int sumDigits(int number)
{
    int sum = 0;

    while (number > 0)
    {
        sum = sum + number % 10;
        number = number / 10;
    }

    return sum;
}


// Print the message for the final digit
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