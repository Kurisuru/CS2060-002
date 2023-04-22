
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define SIZE 80
#define FOLDER_PATH

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
	struct organization *nextOrgPtr;
}Organization;

char *fgetsNoNewLine(char* str, int size, FILE* stream);
char validateYesNo();
void setUpOrg(Organization* orgPtr);
void generateUrl(char url[], const char orgName[]);
void insertOrg(Organization** orgPtr);
void displayInfo(const Organization* orgPtr);
void printOrgs(Organization* headPtr);
bool donate(Organization* orgPtr);
bool adminSummary(Organization* orgPtr);
bool validateZipCode(int zipCode);
bool responseValidation(char* response);

int main(void)
{
	Organization* headPtr = NULL;
	//priority 1 is linked lists
	//priority 2 is is files
	char yesOrNo = ' ';
	printOrgs(headPtr);
	do
	{
		insertOrg(&headPtr);
		printOrgs(headPtr);
		puts("Do you want to create another organization?");
		yesOrNo = validateYesNo();
	} while (yesOrNo == 'y');



	Organization org1; 
	setUpOrg(&org1);
	bool admin = false;
	do {
		admin = donate(&org1);
	} while (!admin);
	return 0;
}

//finds organization with name user selects
Organization selectOrg(char userString[], Organization **headPtr) {
	Organization *temp = *headPtr;

	return *temp;
}

//prints the list of organization names currently in the linked list
void printOrgs(Organization* headPtr)
{
	if (headPtr != NULL)
	{
		puts("List of Organizations: ");
		Organization* currentPtr = headPtr;

		while (currentPtr != NULL)
		{
			puts(currentPtr->orgName);
			currentPtr = currentPtr->nextOrgPtr;
		}
	}
	else
	{
		puts("List is empty");
	}
}

//inserts new organization into linked list sorted alphabetically
void insertOrg(Organization** headPtr) {
	Organization* newOrgPtr = malloc(sizeof(Organization));
	
	if (newOrgPtr != NULL) {
		setUpOrg(newOrgPtr);
		newOrgPtr->nextOrgPtr = NULL;

		Organization* previousPtr = NULL;
		Organization* currentPtr = *headPtr;

		while (newOrgPtr != NULL && strcmp(currentPtr->orgName, newOrgPtr->orgName)<0) {
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextOrgPtr;
		}//while

		if (previousPtr == NULL)
		{
			*headPtr = newOrgPtr;
		}
		else
		{
			previousPtr->nextOrgPtr = newOrgPtr;
		}
		newOrgPtr->nextOrgPtr = currentPtr;

	}
	else
	{
		puts("No memory to create new organization");
	}
}

//sets up an organization with an org name, purpose, name, goal amount, admin email and password, url, and initializes totals for donations
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

//if response is lower or upper case y or n, return true
//else return false
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

//prompts for a (y)es or a (n)o, returns either y or n (lowercase)
char validateYesNo() {
	char validYesNo;

	do {
		puts("Please enter (y)es or (n)o:");
		validYesNo = getchar();
		while (getchar() != '\n');

		validYesNo = tolower(validYesNo);

	} while (validYesNo != 'y' && validYesNo != 'n');

	return  validYesNo;
} //End validateYesNo


//gets input from a stream and stores it in str.
//removes the new line character from the end of the string
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

bool promptDonateAmount() {

}

bool checkStringMatch(char strToCheckWith[]) {

}

//displays organization information and asks user for a donation amount, once a valid donation amount is enetered, collect name of donator and zipcode
//loop until q or Q are entered, and then the correct email and password are entered.
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
	time(&rawtime);


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
			if (donateNum[0] == 'q' || donateNum[0] == 'Q')
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
				zipCode = atoi(zipCodeString);
			} while (!validateZipCode(zipCode));
			printf("Thank you for your donation.There is a 2.9%% credit card processing fee of %.2lf. % .2lf will be donated.", (donateAmount * 0.029), donateAmount);
			do
			{
				puts("Do you want a reciept? (y)es or (n)o");
				fgetsNoNewLine(inputStr, SIZE, stdin);
			} while (!responseValidation(inputStr));
			if (strcmp(inputStr, "Y") == 0 || strcmp(inputStr, "y") == 0)
			{
				info = localtime(&rawtime);
				printf("Organization: %s\nDonation Amount: %.2lf\nDonation Date: ", orgPtr->orgName, donateAmount);
				printf("%d/%d/%d - ", info->tm_mon+1, info->tm_mday, info->tm_year+1900);
				if ((info->tm_hour) >12)
				{
					printf("%d:%d PM", info->tm_hour-12, info->tm_min);
				}
				else
				{
					printf("%d:%d AM", info->tm_hour, info->tm_min);
				}
			}
		}
	}
	return admin;
}

bool getValidNum(char strNum[], double *num) {

}

//generates a url for the donation organization based on the organization name. the url displays as "https:donate.com/[organization-name]?form=popup#"
void generateUrl(char url[], const char orgName[])
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

//displays org name, name of org owner, and url
void displayInfo(const Organization* orgPtr)
{
	printf("Thank you %s. The url to raise funds for %s is %s.\n", 
		orgPtr->name, orgPtr->orgName, orgPtr->url);
}

//if user enters correct email and password, display org name, and total donors, donation amounts, and processing fees
//return true only if correct email and password are entered
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
			} while ((passAttempts < attempts) && (strcmp(orgPtr->password, attempt) != 0));
		}
	return pass;
}

//return true if zipcode is 5 digits long
bool validateZipCode(int zipCode)
{
	bool isValid = false;

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
