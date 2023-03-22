
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define LENGTH 13

bool exploreValidateInt(const char* buff, int* intToReturn);
bool validateInt(char* buff, int* const validInt);
void printLimits();

int main(void)
{
	char inputStr[LENGTH]; // create char arintray
	size_t inputLength = 0;
	int returnInt = 0;

	printLimits();

	for (unsigned int counter = 1; counter < 6; counter++)
	{

		do
		{
			
			puts("\nEnter an integer");
			fgets(inputStr, LENGTH, stdin);
			inputLength = strnlen(inputStr, LENGTH);

			if (inputLength > 0 && inputStr[inputLength - 1] == '\n')
			{
				inputStr[inputLength - 1] = '\0';
				inputLength--;
			}
		} while (!exploreValidateInt(inputStr,&returnInt));
	}

}



void printLimits()
{
	printf("The number of bits in a byte %d\n", CHAR_BIT);

	printf("The minimum value of SIGNED CHAR = %d\n", SCHAR_MIN);
	printf("The maximum value of SIGNED CHAR = %d\n", SCHAR_MAX);
	printf("The maximum value of UNSIGNED CHAR = %d\n", UCHAR_MAX);

	printf("The minimum value of SHORT INT = %d\n", SHRT_MIN);
	printf("The maximum value of SHORT INT = %d\n", SHRT_MAX);

	printf("The minimum value of INT = %d\n", INT_MIN);
	printf("The maximum value of INT = %d\n", INT_MAX);

	printf("The minimum value of CHAR = %d\n", CHAR_MIN);
	printf("The maximum value of CHAR = %d\n", CHAR_MAX);

	printf("The minimum value of LONG = %ld\n", LONG_MIN);
	printf("The maximum value of LONG = %ld\n", LONG_MAX);
}


bool exploreValidateInt(const char* buff, int*intToReturn)
{
	bool returnVal = false;
	// declare pointer to a char that will be passed to strotol
	char* end;
	//The errno is set to zero at program startup and set to ERANGE if out of range when  strtol tries to convert to double
	errno = 0;
	//store integer when it is valid
	int validInt = 0;
	//perform int test on passed value, and store if it was successful
	long intTest = strtol(buff, &end, 10);
	//no valid integers were found within the string entered
	if (end == buff) {
		fprintf(stderr, "%s: not a decimal number\n", buff);
	}
	//string has a valid int, but contains something else after the valid int
	else if ('\0' != *end) {
		fprintf(stderr, "%s: extra characters at end of input: %s\n", buff, end);
	}
	//scanned number is either at the top or bottom value of what can be considered a long
	else if ((LONG_MIN == intTest || LONG_MAX == intTest) && ERANGE == errno) {
		fprintf(stderr, "%s out of range of type long\n", buff);
	}
	//scanned number is greater than what a long can be
	else if (intTest > INT_MAX) {
		fprintf(stderr, "%ld greater than INT_MAX\n", intTest);
	}
	//scanned number is less than what a long can be
	else if (intTest < INT_MIN) {
		fprintf(stderr, "%ld less than INT_MIN\n", intTest);
	}
	//only a valid integer was scanned 
	else {
		*intToReturn = (int)intTest;
		printf("%d is integer value ", *intToReturn);
		returnVal = true;
	}
	return returnVal;
}
