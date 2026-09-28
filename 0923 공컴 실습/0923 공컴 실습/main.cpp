#include <stdio.h>

int main(void)
{

	int nAge = 0;
	float fHeight = 0.0f;
	char cGrade;
	char strName[50];

	// 정보 주입
	printf("Enter your age, height, grade, and name :\n");
	scanf_s("%d %f %c %s", &nAge, &fHeight, &cGrade, strName);
	sizeof(cGrade), strName, sizeof(strName); 

	printf("Your age is : %d\n", nAge);
	printf("Your height is : %.2f\n", fHeight);
	printf("Your grade is : %c\n", cGrade);
	printf("Your name is : %s\n", strName);

	return 0;


	}