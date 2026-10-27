#include <stdio.h>

// Original prices of the three items

#define RED_POTION_PRICE 1000     // Price of Red Potion
#define MAGIC_SCROLL_PRICE 2000   // Price of Magic Scroll
#define ELIXIR_PRICE 3000         // Price of Elixir

// Function declarations

void printMenu(void);          // Show the items and their prices
int getPrice(int item);        // Return the price of the selected item
void printItemName(int item);  // Print the name of the selected item


int main(void)
{
    int balance = 0;       // Money available for purchases
    int item = 0;          // Number selected by the user
    int price;             // Price to pay for the selected item
    int purchaseCount = 0; // Number of completed purchases
    int isDiscount;        // 1 when the next purchase is discounted

    // Read the amount of money inserted into the machine
    
    printf("Insert coins (Current Balance): ");
    scanf_s("%d", &balance);

    // Show the menu before asking the user to choose an item
    
    printMenu();

    while (1)
    {
        printf("Select an item: ");
        scanf_s("%d", &item);

        // Return the remaining money when the user selects 0
        
        if (item == 0)
        {
            printf("Returning %d G. Goodbye!\n", balance);
            break;
        }

        // Find the original price; 0 means the item number is not on the menu
        
        price = getPrice(item);

        if (price == 0)
        {
            printf("Invalid item number.\n\n");
            continue;
        }

        // Use the next purchase number to check for the 50% discount
        
        isDiscount = (purchaseCount + 1) % 3 == 0;

        if (isDiscount)
        {
            price = price / 2;
        }

        // If the balance is too low, choose again without counting a purchase
        
        if (balance < price)
        {
            printf("Not enough balance!\n\n");
            continue;
        }

        // Subtract the price and add 1 to the number of completed purchases
       
        balance = balance - price;
        purchaseCount = purchaseCount + 1;

        if (isDiscount)
        {
            printf("*** GOBLIN'S BLESSING! 50%% DISCOUNT! ***\n");
        }

        // Print the item name and show how much money is left
        
        printf("[Purchased] ");
        printItemName(item);

        if (isDiscount)
        {
            printf(" for %d G. Balance: %d G\n\n", price, balance);
        }
        else
        {
            printf(". Balance: %d G\n\n", balance);
        }
    }

    return 0;
}


// Print the menu using the original item prices

void printMenu(void)
{
    printf("\n--- Goblin's Vending Machine ---\n");
    printf("1. Red Potion (%d G)\n", RED_POTION_PRICE);
    printf("2. Magic Scroll (%d G)\n", MAGIC_SCROLL_PRICE);
    printf("3. Elixir (%d G)\n", ELIXIR_PRICE);
    printf("0. Exit\n");
    printf("--------------------------------\n");
}


// Return the price of the item number, or 0 for an invalid number

int getPrice(int item)
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


// Print the name that matches the selected item number

void printItemName(int item)
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