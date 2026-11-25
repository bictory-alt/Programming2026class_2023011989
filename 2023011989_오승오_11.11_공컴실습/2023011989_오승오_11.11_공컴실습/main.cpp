# include <stdio.h>

#define DATA_ARRAY_SIZE 5

// should remember these functions - final exam
int main(void)
{
	        const int nSize_Data = 7; // it also can be used as a constant size of the array (not used in this code) - final exam
	
	int arr_Data[DATA_ARRAY_SIZE] = { 75, 82, 83, 60, 50 }; // if not clean initialized, the value of the array will be garbage value
	int *ptData = arr_Data;
	int nSizeData = sizeof(arr_Data) / sizeof(arr_Data[0]);

		printf("nSizeData = %d\n", nSizeData);

	for (int i = 0; i < DATA_ARRAY_SIZE; i++)
	{
		// this function is used to print the value of the array and the pointer, important to note
		printf("arr_Data[%d] = %d\n", i, arr_Data[i]);  // just print the value of the "i" th element of the array
		printf("arr_Data[%d] = %d\n", i, *(arr_Data + i)); // if array name is used as a pointer, * should be used
		printf("ptData[%d] = %d\n", i, ptData[i]);
		printf("ptData[%d] = %d\n", i, *(ptData + i));
	}
	
	for (int i = 0; i < DATA_ARRAY_SIZE; i++)
	{
		// print the adress of the array
		printf("arr_Data[%d] = %x\n", i, &arr_Data[i]);  // & is used to point the adress of the "i" th element of the array (scanf is same)
		printf("arr_Data[%d] = %x\n", i, (arr_Data + i)); // (arr_Data + i) is the address (first address of the array + i)
		printf("ptData[%d] = %x\n", i, &ptData[i]);
		printf("ptData[%d] = %x\n", i, (ptData + i)); // when "&" is used ?? 
	}
	return 0;
}

