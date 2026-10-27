#include <stdio.h>

// Constants for input validation (no magic numbers)
#define BIRTH_DATE_DIGITS 8        // A birth date must have exactly 8 digits (YYYYMMDD)
#define EARLIEST_DATE 19000101     // Earliest birth date accepted by this program
#define LATEST_DATE 20261028       // Latest birth date accepted (fixed reference date: report due date)

// Error codes returned by readBirthDate() (a real birth date is never negative)
#define INPUT_END (-1)             // No more input can be read (e.g., Ctrl+Z)
#define INPUT_EMPTY (-2)           // Only Enter or spaces were entered
#define INPUT_NOT_DIGIT (-3)       // A non-digit character or a space between digits was found
#define INPUT_WRONG_LENGTH (-4)    // The number of digits is not 8

// Function declarations
int readBirthDate(void);
int isLeapYear(int year);
int getDaysInMonth(int year, int month);
int isValidDate(int birthDate);
int sumDigits(int number);
void printFortune(int number);


int main()
{
    int birthDate;
    int number;
    int sum;

    // Ask again until a valid birth date is entered
    while (1)
    {
        printf("Enter your 8-digit birthdate (YYYYMMDD): ");
        birthDate = readBirthDate();

        if (birthDate == INPUT_END)
        {
            printf("\nNo more input. The program will end.\n");
            return 1;    // Abnormal end: no valid birth date was entered
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

        // The format is correct, so check whether the date really exists
        if (isValidDate(birthDate) == 1)
        {
            break;
        }
    }

    // Copy the birth date for calculation

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


// Read one whole line character by character and check its format.
// Leading and trailing spaces are allowed.
// Returns the 8-digit birth date, or one of the error codes (negative numbers).
int readBirthDate(void)
{
    char inputChar;
    int digitCount = 0;           // Number of digits read (stops at 9, which means "too many")
    int birthDate = 0;            // Number made from the first 8 digits only
    int hasInvalidChar = 0;       // 1 if a wrong character was found in this line
    int hasSpaceAfterDigit = 0;   // 1 if a space appeared after a digit
    int hasReadAnyChar = 0;       // 1 if at least one character was read in this line

    while (1)
    {
        // scanf_s returns 1 when it reads one character; any other value means the input has ended
        if (scanf_s("%c", &inputChar, 1) != 1)
        {
            if (hasReadAnyChar == 0)
            {
                return INPUT_END;
            }
            break;    // The input ended in the middle of a line: check what was read so far
        }
        hasReadAnyChar = 1;

        if (inputChar == '\n')
        {
            break;    // End of the line
        }

        // Do not stop early on a wrong character: keep reading so the rest of the line is not left behind
        if (inputChar >= '0' && inputChar <= '9')
        {
            if (hasSpaceAfterDigit == 1)
            {
                hasInvalidChar = 1;    // A space between digits, e.g., "2004 1225"
            }

            if (digitCount < BIRTH_DATE_DIGITS)
            {
                birthDate = birthDate * 10 + (inputChar - '0');    // '7' - '0' = 7
            }

            if (digitCount <= BIRTH_DATE_DIGITS)
            {
                digitCount++;    // Counting stops at 9, so a very long input cannot overflow
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
            hasInvalidChar = 1;    // Letters, signs, symbols, Korean characters, etc.
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

// Return 1 if the year is a leap year, otherwise 0
int isLeapYear(int year)
{
    // Divisible by 4 but not by 100, or divisible by 400
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
    {
        return 1;
    }

    return 0;
}

// Return the number of days in the month (0 for an impossible month)
int getDaysInMonth(int year, int month)
{
    int days;

    switch (month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        days = 31;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        days = 30;
        break;
    case 2:
        if (isLeapYear(year) == 1)
        {
            days = 29;
        }
        else
        {
            days = 28;
        }
        break;
    default:
        days = 0;
        break;
    }

    return days;
}

// Check the month, the day, and the allowed range. Print the reason and return 0 if invalid.
int isValidDate(int birthDate)
{
    // Split YYYYMMDD into year, month, and day
    int year = birthDate / 10000;
    int month = birthDate / 100 % 100;
    int day = birthDate % 100;

    if (month < 1 || month > 12)
    {
        printf("Error: The month must be between 01 and 12.\n");
        return 0;
    }

    if (day < 1 || day > getDaysInMonth(year, month))
    {
        printf("Error: Day %d does not exist in month %d of year %d.\n", day, month, year);
        return 0;
    }

    // YYYYMMDD numbers are in the same order as dates, so they can be compared directly
    if (birthDate < EARLIEST_DATE)
    {
        printf("Error: The birthdate must be on or after %d.\n", EARLIEST_DATE);
        return 0;
    }

    if (birthDate > LATEST_DATE)
    {
        printf("Error: The birthdate cannot be later than %d.\n", LATEST_DATE);
        return 0;
    }

    return 1;
}

// Calculate the sum of the digits

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

// Print the fortune message for the destiny number

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
