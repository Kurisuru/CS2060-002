
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
bool validateZipCode(int zipCode);
bool responseValidation(char* response);

int main(void)
{
	Organization org1;
	setUpOrg(&org1);
	donate(&org1);
	return 0;
}

void setUpOrg(Organization* orgPtr)
{
	char inputStr[SIZE];
	char emailResponse[SIZE];
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
	 
	do
	{
		puts("Enter email address.");
		fgetsNoNewLine(orgPtr->email, SIZE, stdin);
		do
		{
			puts("Is this email correct? (y)es or (n)o");
			fgetsNoNewLine(emailResponse, SIZE, stdin);
		} while (!responseValidation(emailResponse));
	} while (!(strcmp(emailResponse, "Y") == 0) && !(strcmp(emailResponse, "y") == 0));
	

	puts("Enter password.");
	fgetsNoNewLine(orgPtr->password, SIZE, stdin);

	generateUrl(orgPtr->url, orgPtr->orgName);
	orgPtr->totalDonationAmount = 0;
	orgPtr->totalDonors = 0;
	orgPtr->totalProcessingAmount = 0;

	displayInfo(orgPtr);

}

bool responseValidation(char* response)
{
	bool isValid = false;

	if ((strcmp(response, "Y") == 0) || (strcmp(response, "y") == 0))
	{
		isValid = true;
	}
	if ((strcmp(response, "N") == 0) || (strcmp(response, "n") == 0))
	{
		isValid = true;
	}

	return isValid;
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
	}
	
	return returnVal;
}

bool donate(Organization* orgPtr)
{
	bool admin = false;
	char donateNum[SIZE];
	char donaterName[SIZE];
	char zipCodeString[SIZE];
	char inputStr[SIZE];
	int zipCode = 0;
	char* endPtr;
	double donateAmount = 0;
	time_t rawtime;
	struct tm* info;
	info = localtime(&rawtime);


	while (!admin)
	{
		
		printf("\n\n%s", orgPtr->url);
		puts("MAKE A DIFFERENCE BY YOUR DONATION");
		printf("Organization: %s\nPurpose: %s\n", orgPtr->orgName, orgPtr->purpose);
		printf("We have currently raised %.2lf\n", orgPtr->totalDonationAmount);
		if (orgPtr->totalDonationAmount >= orgPtr->goalAmount)
		{
			puts("We have reached our goal but can still use the donations.");
		}
		else
		{
			printf("We are %.2lf towards our goal of %.2lf\n", ((orgPtr->totalDonationAmount / orgPtr->goalAmount) * 100), orgPtr->goalAmount);
		}


		donateAmount = 0;
		while ((!(donateAmount > 0)) && !admin)
		{
			puts("Enter the amount you want to donate.");
			fgetsNoNewLine(donateNum, SIZE, stdin);
			if ((strcmp(donateNum, "q") == 0) || (strcmp(donateNum, "Q") == 0))
			{
				admin = adminSummary(orgPtr);
			}

			donateAmount = strtod(donateNum, &endPtr);
		}
		
		if (!admin)
		{
			orgPtr->totalDonationAmount += donateAmount;
			orgPtr->totalDonors++;
			orgPtr->totalProcessingAmount += (donateAmount * 0.029);
			puts("Please enter your first and last name.");
			fgetsNoNewLine(donaterName, SIZE, stdin);
			do
			{
				puts("Please enter your zip code.");
				fgetsNoNewLine(zipCodeString, SIZE, stdin);
				zipCode = strtod(zipCodeString, &endPtr);
			} while (!validateZipCode(zipCode));
			printf("Thank you for your donation.There is a 2.9%% credit card processing fee of %.2lf. % .2lf will be donated.", (donateAmount * 0.029), donateAmount);
			do
			{
				puts("Do you want a reciept? (y)es or (n)o");
				fgetsNoNewLine(inputStr, SIZE, stdin);
			} while (!responseValidation(inputStr));
			if (strcmp(inputStr, "Y") == 0 || strcmp(inputStr, "y") == 0)
			{
				printf("Organization: %s\nDonation Amount: %.2lf\nDonation Date: ", orgPtr->orgName, donateAmount);
				printf("%d/%d/%d - ", info->tm_mon, info->tm_mday, info->tm_year+1900);
			}
		}
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
	printf("Thank you %s. The url to raise funds for %s is %s.\n", 
		orgPtr->name, orgPtr->orgName, orgPtr->url);
}

bool adminSummary(Organization* orgPtr)
{
	bool pass = false;
	int attempts = 2;
	int emailAttempts = 0;
	int passAttempts = 0;
	char attempt[SIZE];

		//gets email from user, checks to see if it equals 
		do
		{
			puts("enter admin email.");
			fgetsNoNewLine(attempt, SIZE, stdin);
			emailAttempts++;
			if (strcmp(orgPtr->email, attempt) == 0)
			{
				//puts("passed");
			}
		} while ((emailAttempts < attempts) && (strcmp(orgPtr->email, attempt) != 0));
		if (strcmp(orgPtr->email, attempt) == 0)
		{
			do
			{
				puts("enter admin password.");
				fgetsNoNewLine(attempt, SIZE, stdin);
				passAttempts++;
				if (strcmp(orgPtr->password, attempt) == 0)
				{
					pass = true;
					printf("Organization: %s\n total donations: %d\n", orgPtr->orgName, orgPtr->totalDonors);
					printf("Total amount donated: %.2lf\n Total processing fees: %.2lf", orgPtr->totalDonationAmount, orgPtr->totalProcessingAmount);
					
				}
				else
				{
					//puts("failed");
				}
			} while ((passAttempts < attempts) && (strcmp(orgPtr->password, attempt) != 0));
		}
	return pass;
}

bool validateZipCode(int zipCode)
{
	bool isValid = false;
	char zipCodeString[SIZE];
	char* endPtr;

	if (zipCode >= 10000 && zipCode <= 99999)
	{
		isValid = true;
	}

	return isValid;
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
