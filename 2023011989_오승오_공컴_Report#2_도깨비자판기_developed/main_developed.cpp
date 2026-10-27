#include <stdio.h>

// Original prices shown on the menu
#define RED_POTION_PRICE 1000     // Price of Red Potion
#define MAGIC_SCROLL_PRICE 2000   // Price of Magic Scroll
#define ELIXIR_PRICE 3000         // Price of Elixir

// Largest balance stored by this program (64-bit long long)
#define MAX_BALANCE 9223372036854775807LL

// Negative return values describe input and output problems
#define INPUT_END (-1LL)          // No more input is available
#define INPUT_INVALID (-2LL)      // The line is not one nonnegative whole number
#define INPUT_RANGE (-3LL)        // The number exceeds MAX_BALANCE
#define INPUT_ERROR (-4LL)        // Reading input failed
#define OUTPUT_ERROR (-5LL)       // Writing output failed

// Function declarations
void printMenu(void);                 // Show the items and their original prices
int getPrice(long long item);         // Return the original price of an item
void printItemName(long long item);   // Print the name of an item
long long readNumber(void);           // Read and check one whole line
long long readInput(int isBalance);   // Ask again until a usable number is entered


int main(void)
{
    long long balance;
    long long item;
    long long purchaseCount = 0;  // Count only completed purchases
    int price;
    int isDiscount;

    // 1 means that the input is the amount of money
    balance = readInput(1);
    if (balance < 0)
    {
        if (balance == INPUT_END)
        {
            printf("\nNo more input. The program will end.\n");
        }
        else if (balance == INPUT_ERROR)
        {
            printf("\nInput error. The program will end.\n");
        }
        return 1;
    }

    printMenu();

    while (1)
    {
        // 0 means that the input is a menu number from 0 to 3
        item = readInput(0);

        if (item == OUTPUT_ERROR)
        {
            return 1;
        }
        if (item == INPUT_ERROR)
        {
            printf("\nInput error. Returning %lld G. The program will end.\n", balance);
            fflush(stdout);
            return 1;
        }
        if (item == INPUT_END)
        {
            printf("\nNo more input. Returning %lld G. Goodbye!\n", balance);
            break;
        }

        if (item == 0)
        {
            printf("Returning %lld G. Goodbye!\n", balance);
            break;
        }

        // Start with the original price each time a new item is selected
        price = getPrice(item);
        isDiscount = (purchaseCount + 1) % 3 == 0;

        if (isDiscount)
        {
            price = price / 2;
        }

        // A failed purchase does not change the balance or the purchase count
        if (balance < price)
        {
            printf("Not enough balance!\n\n");
            continue;
        }

        balance = balance - price;

        // Each purchase costs at least 500 G and no money is added, so this count stays in range
        purchaseCount = purchaseCount + 1;
        if (isDiscount)
        {
            printf("*** GOBLIN'S BLESSING! 50%% DISCOUNT! ***\n");
        }

        printf("[Purchased] ");
        printItemName(item);

        if (isDiscount)
        {
            printf(" for %d G. Balance: %lld G\n\n", price, balance);
        }
        else
        {
            printf(". Balance: %lld G\n\n", balance);
        }
    }

    // Check buffered output as well as messages already written
    if (ferror(stdout) || fflush(stdout) == EOF)
    {
        return 1;
    }

    return 0;
}


// Print the menu using the original prices
void printMenu(void)
{
    printf("\n--- Goblin's Vending Machine ---\n");
    printf("1. Red Potion (%d G)\n", RED_POTION_PRICE);
    printf("2. Magic Scroll (%d G)\n", MAGIC_SCROLL_PRICE);
    printf("3. Elixir (%d G)\n", ELIXIR_PRICE);
    printf("0. Exit\n");
    printf("--------------------------------\n");
}


// Return the original price; readInput checks the menu number before this call
int getPrice(long long item)
{
    switch (item)
    {
    case 1:
        return RED_POTION_PRICE;
    case 2:
        return MAGIC_SCROLL_PRICE;
    case 3:
        return ELIXIR_PRICE;
    default:
        return 0;
    }
}


// Print the item name after a purchase is completed
void printItemName(long long item)
{
    switch (item)
    {
    case 1:
        printf("Red Potion");
        break;
    case 2:
        printf("Magic Scroll");
        break;
    case 3:
        printf("Elixir");
        break;
    }
}


// Read one line without storing it in an array
long long readNumber(void)
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

    while (1)
    {
        if (scanf_s("%c", &inputChar, 1u) != 1)
        {
            if (ferror(stdin) || feof(stdin) == 0)
            {
                return INPUT_ERROR;
            }
            if (hasReadAnyChar == 0)
            {
                return INPUT_END;
            }
            break;  // Check a final line even when it has no newline
        }

        hasReadAnyChar = 1;
        if (inputChar == '\n')
        {
            break;
        }

        if (inputChar >= '0' && inputChar <= '9')
        {
            if (hasSpaceAfterNumber)
            {
                hasInvalidChar = 1;
            }
            hasDigit = 1;
            digit = inputChar - '0';

            // Check the range before multiplying by 10 and adding the next digit
            if (isTooLarge == 0)
            {
                if (value > (MAX_BALANCE - digit) / 10)
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
            hasPlus = 1;  // Allow one plus sign directly before the digits
        }
        else if (inputChar == ' ' || inputChar == '\t' || inputChar == '\r' ||
            inputChar == '\v' || inputChar == '\f')
        {
            // Spaces are allowed before and after the number, but not inside it
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

    // Read the entire line before returning, even if a wrong character was found
    if (hasInvalidChar || hasDigit == 0)
    {
        return INPUT_INVALID;
    }
    if (isTooLarge)
    {
        return INPUT_RANGE;
    }

    return value;
}


// Check the format and the allowed range for each input
long long readInput(int isBalance)
{
    long long value;

    while (1)
    {
        if (ferror(stdout) || fflush(stdout) == EOF)
        {
            return OUTPUT_ERROR;
        }
        if (ferror(stdin))
        {
            return INPUT_ERROR;
        }
        if (feof(stdin))
        {
            return INPUT_END;
        }

        if (isBalance)
        {
            printf("Insert coins (Current Balance): ");
        }
        else
        {
            printf("Select an item: ");
        }

        // Show the prompt before waiting for keyboard input
        if (ferror(stdout) || fflush(stdout) == EOF)
        {
            return OUTPUT_ERROR;
        }

        value = readNumber();
        if (value == INPUT_END || value == INPUT_ERROR)
        {
            return value;
        }

        if (value == INPUT_INVALID)
        {
            printf("Error: Enter one whole number using digits. Negative signs, letters, decimals, and spaces inside the number are not allowed.\n");
            continue;
        }
        if (value == INPUT_RANGE)
        {
            if (isBalance)
            {
                printf("Error: The balance must be from 0 to %lld G.\n", MAX_BALANCE);
            }
            else
            {
                printf("Invalid item number. Choose 0, 1, 2, or 3.\n");
            }
            continue;
        }
        if (isBalance == 0 && value > 3)
        {
            printf("Invalid item number. Choose 0, 1, 2, or 3.\n");
            continue;
        }

        return value;
    }
}
