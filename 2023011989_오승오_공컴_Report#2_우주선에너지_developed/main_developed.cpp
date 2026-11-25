#include <stdio.h>

// Largest positive long long value in Visual Studio (64 bits)
#define MAX_ENERGY 9223372036854775807LL

// Stop an excessively long line instead of waiting for its remaining characters
#define MAX_INPUT_CHARS 256

// Negative return values describe input problems
#define INPUT_END (-1LL)       // No more input is available
#define INPUT_INVALID (-2LL)   // The line is not one positive integer
#define INPUT_RANGE (-3LL)     // The number is too large to store or calculate
#define INPUT_ERROR (-4LL)     // Reading input failed
#define INPUT_TOO_LONG (-5LL)  // The input line exceeds MAX_INPUT_CHARS

// Read one complete line and return a positive number or an error code
long long readEnergy(void);

// Return the next energy, or INPUT_RANGE if the calculation would overflow
long long nextEnergy(long long energy);

int main(void)
{
    long long energy;
    long long newEnergy;
    long long maxEnergy;
    long long steps = 0;

    // Ask again when the input is invalid.
    while (1)
    {
        printf("Enter the initial engine energy: ");
        if (ferror(stdout) || fflush(stdout) == EOF)
        {
            return 1;
        }

        energy = readEnergy();

        if (energy == INPUT_END)
        {
            printf("\nNo more input. The program will end.\n");
            return 1;
        }
        else if (energy == INPUT_ERROR)
        {
            printf("\nInput error. The program will end.\n");
            return 1;
        }
        else if (energy == INPUT_INVALID)
        {
            printf("Error: Enter one positive integer (for example, 6 or +6).\n");
            continue;
        }
        else if (energy == INPUT_RANGE)
        {
            printf("Error: Enter a number from 1 to %lld.\n", MAX_ENERGY);
            continue;
        }
        else if (energy == INPUT_TOO_LONG)
        {
            // End here because the rest of this long line has not been read.
            printf("Error: Input is too long. Use at most %d characters per line. The program will end.\n",
                MAX_INPUT_CHARS);
            return 1;
        }

        break;
    }

    // Include the initial energy when finding the highest value.
    maxEnergy = energy;
    if (printf("Sequence: %lld", energy) < 0)
    {
        return 1;
    }

    while (energy != 1)
    {
        // Check before adding 1 to the step count.
        if (steps == MAX_ENERGY)
        {
            printf("\nError: The step count is too large.\n");
            return 1;
        }

        newEnergy = nextEnergy(energy);
        if (newEnergy == INPUT_RANGE)
        {
            printf("\nError: The next energy exceeds %lld. Calculation stopped.\n",
                MAX_ENERGY);
            return 1;
        }

        energy = newEnergy;
        steps = steps + 1;
        if (printf(" -> %lld", energy) < 0)
        {
            return 1;
        }

        if (energy > maxEnergy)
        {
            maxEnergy = energy;
        }
    }

    // Print success only when the energy really reaches 1.
    printf("\nEscape successful!\n");
    printf("Total steps: %lld\n", steps);
    printf("Maximum altitude reached: %lld\n", maxEnergy);
    if (ferror(stdout) || fflush(stdout) == EOF)
    {
        return 1;
    }
    return 0;
}

long long readEnergy(void)
{
    char inputChar;
    long long value = 0;
    int digit;
    int hasReadAnyChar = 0;
    int hasDigit = 0;
    int hasPlus = 0;
    int hasSpaceAfterNumber = 0;
    int hasInvalidChar = 0;
    int isTooLarge = 0;
    int characterCount = 0;

    // Read to the end of the line, even after finding a wrong character.
    while (1)
    {
        if (scanf_s("%c", &inputChar, 1u) != 1)
        {
            if (ferror(stdin))
            {
                return INPUT_ERROR;
            }
            if (hasReadAnyChar == 0)
            {
                return INPUT_END;
            }
            break; // Check a final line even if it has no newline.
        }

        hasReadAnyChar = 1;
        if (inputChar == '\n')
        {
            break;
        }

        // Count only characters before the newline. The count never exceeds 256.
        if (characterCount == MAX_INPUT_CHARS)
        {
            return INPUT_TOO_LONG;
        }
        characterCount = characterCount + 1;

        if (inputChar >= '0' && inputChar <= '9')
        {
            if (hasSpaceAfterNumber)
            {
                hasInvalidChar = 1;
            }
            hasDigit = 1;
            digit = inputChar - '0';

            // Check before multiplying by 10 and adding the next digit.
            if (isTooLarge == 0)
            {
                if (value > (MAX_ENERGY - digit) / 10)
                {
                    isTooLarge = 1;
                }
                else
                {
                    value = value * 10 + digit;
                }
            }
        }
        else if (inputChar == '+' && hasPlus == 0 && hasDigit == 0 &&
            hasSpaceAfterNumber == 0 && hasInvalidChar == 0)
        {
            hasPlus = 1; // Allow one plus sign directly before the digits.
        }
        else if (inputChar == ' ' || inputChar == '\t' || inputChar == '\r' ||
            inputChar == '\v' || inputChar == '\f')
        {
            // Leading and trailing spaces are allowed, but internal spaces are not.
            if (hasDigit || hasPlus)
            {
                hasSpaceAfterNumber = 1;
            }
        }
        else
        {
            hasInvalidChar = 1;
        }
    }

    if (hasInvalidChar || hasDigit == 0)
    {
        return INPUT_INVALID;
    }
    if (isTooLarge)
    {
        return INPUT_RANGE;
    }
    if (value == 0)
    {
        return INPUT_INVALID;
    }
    return value;
}

long long nextEnergy(long long energy)
{
    if (energy % 2 == 0)
    {
        return energy / 2;
    }
    else
    {
        // Check the limit before calculating 3 * energy + 1.
        if (energy > (MAX_ENERGY - 1) / 3)
        {
            return INPUT_RANGE;
        }
        return energy * 3 + 1;
    }
}