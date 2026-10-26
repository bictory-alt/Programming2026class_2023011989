#include <stdio.h>

#define G 9.81  // gravity

// define function prototypes

void printMenu(void);
int inputMenu(void);
double inputPositive(const char prompt[]);
double calcKE(double m, double v);
double calcPE(double m, double h);
void printEnergy(double e);
void printTable(double m, double h0);
void clearBuffer(void);

int main(void)
{
	int choice;
	double m, v, h, e;

	// show menu only one time

	printMenu();


	// repeat until user choose to exit (choice 0)

	while (1)
	{
		choice = inputMenu();

		if (choice == 0)
		{
			printf("Exiting the program...\n");
			break;

		}

		else if (choice == 1)
		{
			// kinetic energy

			m = inputPositive("Mass (kg) : ");
			v = inputPositive("Speed (m/s) : ");
			e = calcKE(m, v);
			printEnergy(e);
		}

		else if (choice == 2)
		{
			// potential energy

			m = inputPositive("Mass (kg) : ");
			h = inputPositive("Height (m) : ");
			e = calcPE(m, h);
			printEnergy(e);
		}
		else if (choice == 3)
		{
			// free-fall table

			m = inputPositive("Mass (kg) : ");
			h = inputPositive("Height (m) : ");
			printTable(m, h);
		}
		else
			// if number is not in the menu
		{
			printf("Please select 0, 1, 2, or 3.\n");

		}

	}
	return 0;
}

// only output functions

void printMenu(void)
{
	printf("===== Mechanical Energy Calculator =====\n");
	printf("1. Kinetic energy  2. Potential energy  3. Free-fall table  0. Exit\n");
}

// input the menu number from the user no parameter, but return the number

int inputMenu(void)
{
	int choice;
	int result;

	printf("Select : ");
	result = scanf_s("%d", &choice);
	
  // if	it isn't a number, clear the buffer and return -1

	if (result != 1)
	{
		clearBuffer();
		return -1;
	}
	return choice; 
}

  // get the value which is bigger than 0 (parameter is the message to print) (helped by AI)
double inputPositive(const char prompt[])
{
	
	double value;
	int result;

	printf("%s", prompt);

	// if the value is wrong, ask again
	
	while (1)
	{
		result = scanf_s("%lf", &value);

		if (result != 1)
		{
			// if user didn't type a number
			
			clearBuffer();
			printf("  -> Please enter a number. Enter again: ");
		}
		else if (value <= 0)
		{
			// zero or minus value is not allowed
			
			printf("  -> Value must be positive. Enter again: ");
		}
		else
		{
			return value;
		}
	}
}

// calculate kinetic energy KE = 1/2 * m * v^2

double calcKE(double m, double v)
{
	return 0.5 * m * v * v;
}

// calculate potential energy PE = m * g * h

double calcPE(double m, double h)
{
	return m * G * h;
}

// print the energy, if energy is 1000 J or more then kJ too (only parameter)

void printEnergy(double e)
{
	if (e >= 1000)
		printf("  Energy = %.3f J (%.3f kJ)\n\n", e, e / 1000);
	else
		printf("  Energy = %.3f J\n\n", e);
}

// print the free fall table, h0 is divided by 5 so there are 6 rows

void printTable(double m, double h0)
{
	int i;
	double h, pe, ke;

	printf("%8s %10s %10s %10s\n", "h(m)", "PE(J)", "KE(J)", "Total(J)");

	for (i = 0; i <= 5; i++)
	{
		h = h0 * (5 - i) / 5.0;   // height from h0 to 0
		pe = calcPE(m, h);
		ke = m * G * (h0 - h);    // KE = mg(h0 - h)

		printf("%8.3f %10.3f %10.3f %10.3f\n", h, pe, ke, pe + ke);
	}

	printf("\n");
}

// remove the remain characters in the buffer

void clearBuffer(void)
{
	while (getchar() != '\n')
	{
	}
}
