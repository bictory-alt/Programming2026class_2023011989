#include <stdio.h>


int main(void)
{

	int number = -1;
    int money = 0;
	int coin = 0;
	
	
	while (number != 0)
	{ 
	

	printf("====Drink Vending Machine====");
	printf("1. Coke(1200원), 2. Sprite(1000원), 3. Coffee(800원), 0. Exit");

	scanf_s("%d", &number);
	printf("You selected.. : %d", number);
	 
	  switch(number)
	  {
		  number 1 : 
		  
		  
		  while (money < 1200)
		  {
			  scanf_s("%d", &coin);


			  if (coin == 100 || coin == 500 || coin == 1000)
			  {
				  money = money + coin;

				  printf("(Current Amount %dwon / Needed Amount %dwon) : %d", money, 1200 - money, coin);

			  else
			  {  printf("%d won is not accepted.", coin);
			  }

		  }

		    

	 

	

	




 
}

