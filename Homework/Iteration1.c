
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

char *fgetsNoNewLine(char* str, int size, FILE* stream);
void setUpOrg(Organization* orgPtr);
void generateUrl(char url[SIZE], const char orgName[SIZE]);
void displayInfo(const Organization* orgPtr);
bool donate(Organization* orgPtr);
bool adminSummary(Organization* orgPtr);

int main(void)
{
	Organization org1;
	setUpOrg(&org1);
	adminSummary(&org1);
	return 0;
}

void setUpOrg(Organization* orgPtr)
{
	char inputStr[SIZE];
	char* endPtr = inputStr;

	puts("Enter fundraising  organization name.");
	fgetsNoNewLine(orgPtr->orgName, SIZE, stdin);

	puts("Enter fundraiser  purpose.");
	fgetsNoNewLine(orgPtr->purpose, SIZE, stdin);

	puts("Enter first and last name.");
	fgetsNoNewLine(orgPtr->name, SIZE, stdin);

	do
	{
	puts("Enter the goal amount you want to raise.");
		fgets(inputStr, SIZE, stdin);
		orgPtr->goalAmount = strtod(inputStr, &endPtr);
	} while (!(orgPtr->goalAmount>0));
	 
	puts("Enter email address.");
	fgetsNoNewLine(orgPtr->email, SIZE, stdin);

	puts("Enter password.");
	fgetsNoNewLine(orgPtr->password, SIZE, stdin);

	generateUrl(orgPtr->url, orgPtr->orgName);
	orgPtr->totalDonationAmount = 0;
	orgPtr->totalDonors = 0;
	orgPtr->totalProcessingAmount = 0;

	displayInfo(orgPtr);

}

char *fgetsNoNewLine(char *str, int size, FILE *stream)
{
	char* returnVal = NULL;
	char* newlinePtr;
	if (fgets(str, size, stream) != NULL)
	{
		if ((newlinePtr = strchr(str, '\n')) != NULL)
		{
			*newlinePtr = '\0';

		}
		returnVal = str;
		puts(returnVal);
	}
	
	return returnVal;
}

bool donate(Organization* orgPtr)
{
	bool admin = false;
	char donateNum[SIZE];
	while (!admin)
	{
		fgetsNoNewLine(donateNum, SIZE, stdin);
	}
	return admin;
}

void generateUrl(char url[SIZE], const char orgName[SIZE])
{
	strcpy(url, "https:donate.com/");

	char orgNameWithDashes[SIZE] = {""};
	strncpy(orgNameWithDashes, orgName, sizeof(orgNameWithDashes));

	char* tokenPtr = strtok(orgNameWithDashes, " ");

	while (tokenPtr != NULL)
	{
		strcat(url, tokenPtr);
		tokenPtr = strtok(NULL, " ");
		strcat(url, "-");
	}
	
	strcat(url, "?form=popup#");
}

void displayInfo(const Organization* orgPtr)
{
	printf("Thank you %s. The url to raise funds for %s is %s.", 
		orgPtr->name, orgPtr->orgName, orgPtr->url);
}

bool adminSummary(Organization* orgPtr)
{
	bool pass = false;
	int attempts = 2;
	int emailAttempts = 0;
	int passAttempts = 0;
	char emailAttempt[SIZE];


		do
		{
			fgetsNoNewLine(emailAttempt, SIZE, stdin);
			emailAttempts++;
			if (strcmp(orgPtr->email, emailAttempt) == 0)
			{
				puts("passed");
			}
			else
			{
				puts("failed");
			}
		} while ((emailAttempts < attempts) && (strcmp(orgPtr->email, emailAttempt) != 0));
		if (strcmp(orgPtr->email, emailAttempt) == 0)
		{
			passAttempts++;
		}
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
