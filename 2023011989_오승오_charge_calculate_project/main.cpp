#include <stdio.h>

int main(void)
{
    int price = 0;
    int quantity = 0;
    int cash = 0;

    int total = 0;
    int discount = 0;
    int payment = 0;
    int change = 0;

    int bill1000 = 0;
    int coin500 = 0;
    int coin100 = 0;
    int coin50 = 0;
    int rest = 0;

    // Enter the price, quantity and cash
    printf("Unit Price (won) : ");
    scanf_s("%d", &price);

    printf("Quantity (pcs) : ");
    scanf_s("%d", &quantity);

    printf("Received Cash (won) : ");
    scanf_s("%d", &cash);

    // Calculate the payment and change
    total = price * quantity;
    discount = total / 10;
    payment = total - discount;
    change = cash - payment;

    // Calculate the bills and coins
    bill1000 = change / 1000;
    coin500 = (change % 1000) / 500;
    coin100 = (change % 500) / 100;
    coin50 = (change % 100) / 50;
    rest = change % 50;

    // Print the result
    printf("\n");
    printf("Total Price : %d won\n", total);
    printf("Discount (10%%) : -%d won\n", discount);
    printf("Payment Amount : %d won\n\n", payment);

    printf("Change : %d won\n", change);
    printf("1000-won bill : %d bill(s)\n", bill1000);
    printf("500-won : %d coin(s)\n", coin500);
    printf("100-won : %d coin(s)\n", coin100);
    printf("50-won : %d coin(s)\n", coin50);
    printf("Remainder : %d won\n", rest);

    return 0;
}