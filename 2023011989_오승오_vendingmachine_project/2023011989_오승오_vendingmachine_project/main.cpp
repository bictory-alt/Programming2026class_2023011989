#include <stdio.h>

int main(void)
{
    int number = -1;
    int money = 0;
    int coin = 0;
    int price = 0;
    int change = 0;

    int coin500 = 0;
    int coin100 = 0;
    int count = 0;
    int sales = 0;

    while (number != 0)
    {
        // Show the menu
        printf("\n==== Drink Vending Machine ====\n");
        printf("1. Coke(1200 won)  2. Sprite(1100 won)  ");
        printf("3. Coffee(800 won)  0. Exit\n");
        printf("Select: ");
        scanf_s("%d", &number);

        // Reset the price and money
        price = 0;
        money = 0;

        switch (number)
        {
        case 1:
            price = 1200;
            break;

        case 2:
            price = 1100;
            break;

        case 3:
            price = 800;
            break;

        case 0:
            break;

        default:
            printf("Invalid selection.\n");
            break;
        }

        if (price > 0)
        {
            // Keep inserting money until it is enough
            while (money < price)
            {
                printf("Insert (Current %d won / Need %d won): ",
                    money, price - money);
                scanf_s("%d", &coin);

                if (coin == 100 || coin == 500 || coin == 1000)
                {
                    money = money + coin;
                }
                else
                {
                    printf("%d won is not accepted.\n", coin);
                    printf("Please insert 100, 500, or 1000 won.\n");
                }
            }

            // Calculate the change
            change = money - price;

            printf("Here is your drink! Change: %d won\n", change);

            if (change == 0)
            {
                printf("No change.\n");
            }
            else
            {
                coin500 = change / 500;
                coin100 = (change % 500) / 100;

                // Show one o for each coin
                printf("500 won: ");

                while (coin500 > 0)
                {
                    printf("o");
                    coin500 = coin500 - 1;
                }

                printf("\n");
                printf("100 won: ");

                while (coin100 > 0)
                {
                    printf("o");
                    coin100 = coin100 - 1;
                }

                printf("\n");
            }

            // Count the drink and add its price
            count = count + 1;
            sales = sales + price;
        }
    }

    printf("Today's sold: %d, Revenue: %d won\n", count, sales);

    return 0;
}