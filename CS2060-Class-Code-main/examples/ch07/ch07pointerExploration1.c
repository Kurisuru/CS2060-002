/*******************
 Understanding pointers

 Add comments to explain the code
**************/

#include <stdio.h>


int main ()
{
	// Initalize houseNum
	int houseNum = 13;
	int calcHouseNum1 = 0;
	int calcHouseNum2 = 0;
	int *houseNumPtr = &houseNum;
	//int stored at adress of houseNum
	printf("houseNum %d\n", houseNum);
	//address of houseNum
	printf("&houseNum %p\n\n", &houseNum);
	//int stored at adress of houseNum
	printf ("*houseNumPtr  %d\n", *houseNumPtr);
	//address of housenum
	printf ("houseNumPtr %p\n\n", houseNumPtr);
	//address of pointer to houseNum
	printf ("&houseNumPtr %p\n\n", &houseNumPtr);
	//int of houseNum plus int of houseNum
	calcHouseNum1 =  *houseNumPtr + *houseNumPtr;

	printf("*houseNumPtr + *houseNumPtr is %d\n\n", calcHouseNum1);
	//2 times the int stored in houseNum
	calcHouseNum2 = 2 * (*houseNumPtr);

	printf("2 * (*houseNumPtr) is %d\n\n", calcHouseNum2);
	//the & and the * of a pointer can be switch an still display the address of the pointer
	printf("\n&*houseNumPtr = %p"
		"\n*&houseNumPtr = %p\n", &*houseNumPtr, *&houseNumPtr);
			
	return 0;
}
