#include <stdio.h>


int main(void)

{

	int time = 0;
	int hour = 0;
	int minute = 0;
	int sec = 0;
	
	printf("Enter total time in seconds : ");

	scanf_s("%d", &time);	

	hour = time / 3600;
	minute = (time % 3600) / 60;
    sec = time % 60;


	printf("%d seconds is %d hours %d minutes %d seconds.\n", time, hour, minute, sec);

	printf("Digital format : %02d:%02d:%02d\n", hour, minute, sec);

	return 0;
}