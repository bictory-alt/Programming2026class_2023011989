#include <stdio.h>

// function declarations
void printMenu(void);
int inputMenu(void);
double inputPositive(char type);
void printResult(double v, double i, double r);
void clearBuffer(void);

int main(void)
{
    int choice;
    double v, i, r;

    // print the menu only once
    printMenu();

    while (1)
    {
        choice = inputMenu();

        if (choice == 0)
        {
            // exit the program
            printf("Program ended.\n");
            break;
        }
        else if (choice == 1)
        {
            // V = I x R
            i = inputPositive('I');
            r = inputPositive('R');
            v = i * r;
            printResult(v, i, r);
        }
        else if (choice == 2)
        {
            // I = V / R
            v = inputPositive('V');
            r = inputPositive('R');
            i = v / r;
            printResult(v, i, r);
        }
        else if (choice == 3)
        {
            // R = V / I
            v = inputPositive('V');
            i = inputPositive('I');
            r = v / i;
            printResult(v, i, r);
        }
        else if (choice == 4)
        {
            // not made yet
            printf("Sweep table is not implemented.\n\n");
        }
        else
        {
            // wrong menu number
            printf("Please select 0, 1, 2, 3, or 4.\n\n");
        }
    }

    return 0;
}

// print the menu (output only)
void printMenu(void)
{
    printf("===== Ohm's Law Calculator =====\n");
    printf("1. Voltage  2. Current  3. Resistance  4. Sweep table  0. Exit\n");
}

// get the menu number from the user (no parameter, returns a value)
int inputMenu(void)
{
    int choice;
    int result;

    printf("Select: ");
    result = scanf_s("%d", &choice);

    // if the user did not type a number
    if (result != 1)
    {
        clearBuffer();
        return -1;
    }

    return choice;
}

// get a value bigger than 0 (takes a parameter and returns a value)
// 'V' = voltage, 'I' = current, 'R' = resistance
double inputPositive(char type)
{
    double value;
    int result;

    // print what to enter
    if (type == 'V')
        printf("Voltage (V): ");
    else if (type == 'I')
        printf("Current (A): ");
    else
        printf("Resistance (ohm): ");

    // keep asking until the input is OK
    while (1)
    {
        result = scanf_s("%lf", &value);

        if (result != 1)
        {
            // if  not a number
            clearBuffer();
            printf("  -> Please enter a number. Enter again: ");
        }
        else if (value <= 0)
        {
            // if 0 or negative
            printf("  -> Value must be positive. Enter again: ");
        }
        else
        {
            return value;
        }
    }
}

// print V, I, R and power P = V x I (takes parameters, returns nothing)
void printResult(double v, double i, double r)
{
    double p = v * i;

    printf("  V = %.3f V,  I = %.3f A,  R = %.3f ohm,  P = %.3f W\n\n",
        v, i, r, p);
}

// remove the leftover characters in the input buffer (helped by AI)
void clearBuffer(void)
{
    while (getchar() != '\n')
    {
    }
}