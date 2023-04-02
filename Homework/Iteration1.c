
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 80

typedef struct organization 
{
	char orgName[SIZE];
	char purpose[SIZE];
	char name[SIZE];
	char email[SIZE];
	char password[SIZE];
	char url[SIZE];
	int totalDonors;
	double totalDonationAmount;
	double totalProcessingAmount;
	double goalAmount;
}Organization;

void setUpOrg(Organization* orgPtr);
void donate(Organization* orgPtr);
void generateUrl(char *email[], const char *orgName[]);
void displayInfo(const Organization* orgPtr);
bool adminSummary(Organization* orgPtr);

int main(void)
{
	Organization org1;
	setUpOrg(&org1);
	return 0;
}

void setUpOrg(Organization* orgPtr)
{
	char inputStr[SIZE];
	char* endPtr = inputStr;

	puts("Enter fundraising  organization name.");
	fgets(orgPtr->orgName, SIZE, stdin);

	puts("Enter fundraiser  purpose.");
	fgets(orgPtr->purpose, SIZE, stdin);

	puts("Enter first and last name.");
	fgets(orgPtr->name, SIZE, stdin);

	puts("Enter the goal amount you want to raise.");
	fgets(inputStr, SIZE, stdin);
	orgPtr->goalAmount = strtod(inputStr, &endPtr);
	//needs validation
	 
	puts("Enter email address.");
	fgets(orgPtr->email, SIZE, stdin);

	puts("Enter password.");
	fgets(orgPtr->password, SIZE, stdin);

	generateUrl(&(orgPtr->url), &(orgPtr->orgName));
	orgPtr->totalDonationAmount = 0;
	orgPtr->totalDonors = 0;
	orgPtr->totalProcessingAmount = 0;

	displayInfo(orgPtr);

}

char fgetsNoNewLine(char *str, int size, FILE *stream)
{
	if (fgets(str, size, stream) != NULL)
	{

	}
}

void donate(Organization* orgPtr)
{

}

void generateUrl(char *email[], const char* orgName[])
{
	*email = "https:donate.com/";
	/*char* bufferPtr;

	bufferPtr = strchr(*orgName, ' ');

	while (bufferPtr != NULL)
	{
		*bufferPtr = '-';
		bufferPtr = strchr(bufferPtr, ' ');
	}*/
	char* orgNameWithDashes[SIZE];
	strncpy(*orgNameWithDashes, *orgName, sizeof(orgNameWithDashes));

	char* tokenPtr = strtok(*orgNameWithDashes, " ");

	//strtok
}

void displayInfo(const Organization* orgPtr)
{
	printf("Thank you %s. The url to raise funds for %s is %s.", 
		orgPtr->name, orgPtr->orgName, orgPtr->url);
}

bool adminSummary(Organization* orgPtr)
{
	bool pass = false;

	return pass;
}

bool validateZipCode(int zipCode)
{
	bool isValid = false;

	return isValid;
}

void validateDonationAmount(double *donateAmountPtr)
{
	
}

bool validateEmail()
{
	bool isValid = false;

	return isValid;
}

bool validatePassword(const char password[])
{
	bool isValid = false;

	return isValid;
}
