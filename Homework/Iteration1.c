
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define SIZE 80
#define PROCESSING_FEE 0.031
#define FOLDER_PATH "C:\\CS2060Files\\"

typedef struct organization 
{
	char orgName[SIZE];
	char purpose[SIZE];
	char name[SIZE];
	char email[SIZE];
	char password[SIZE];
	char url[SIZE];
	char filePath[SIZE];
	int totalDonors;
	double totalDonationAmount;
	double totalProcessingAmount;
	double goalAmount;
	struct organization *nextOrgPtr;
}Organization;

Organization* selectOrg(Organization** headPtr, char orgToDonate[]);
char *fgetsNoNewLine(char* str, int size, FILE* stream);
char validateYesNo();
int strcmpIgnoreCase(const char* str1, const char* str2);
void setUpOrg(Organization* orgPtr);
void generateUrl(char url[], const char orgName[]);
void insertOrg(Organization** orgPtr);
void displayInfo(const Organization* orgPtr);
void printOrgs(Organization* headPtr, bool details);
void createRecieptFile(char filePath[], const char orgName[]);
void freeRemainingOrgs(Organization** headPtr);
void orgSummary(Organization* headPtr);
bool donate(Organization* orgPtr);
bool newDonate(Organization* orgPtr);
bool adminSummary(Organization* orgPtr);
bool validateZipCode(int zipCode);
bool validatePassword(const char password[]);
bool validateEmail(const char email[]);

int main(void)
{
	Organization* headPtr = NULL;
	char yesOrNo = ' ';
	printOrgs(headPtr, false);
	do
	{

		insertOrg(&headPtr);
		printOrgs(headPtr, false);
		puts("Do you want to create another organization?");
		yesOrNo = validateYesNo();
	} while (yesOrNo == 'y');

	char orgToDonate[SIZE];
	bool quit = false;
	do
	{
		Organization *temp = NULL;
		printOrgs(headPtr, true);
		puts("What organization would you like to donate to?");
		fgetsNoNewLine(orgToDonate, sizeof(orgToDonate), stdin);
		temp = selectOrg(&headPtr, orgToDonate);
		if(temp != NULL)
		{ 
			quit = newDonate(temp);
		}
		
	} while (!quit);

	orgSummary(headPtr);
	freeRemainingOrgs(&headPtr);

	return 0;
}

//finds organization with name user selects
Organization* selectOrg(Organization **headPtr, char orgToDonate[]) {
	Organization* temp = NULL;
	if (*headPtr != NULL)
	{
		Organization* currentPtr = *headPtr;

		while (currentPtr != NULL && (strcmp(currentPtr->orgName,orgToDonate) != 0)) {
			currentPtr = currentPtr->nextOrgPtr;
		}//while
		if (currentPtr != NULL && strcmp(currentPtr->orgName, orgToDonate) == 0)
		{
			temp = currentPtr;
		}
	}
	else
	{
		puts("The list is empty");
	}
	return temp;
}

//prints the list of organization names currently in the linked list
void printOrgs(Organization* headPtr, bool details)
{
	if (headPtr != NULL)
	{
		puts("List of Organizations: ");
		Organization* currentPtr = headPtr;
		if (details)
		{
		printf("Organization\t\tGoal Amount\tCurrent Donations\n");
		while (currentPtr != NULL)
		{
			printf("%-15s\t\t%.2lf\t%.2lf\n", currentPtr->orgName, currentPtr->goalAmount, currentPtr->totalDonationAmount);
			currentPtr = currentPtr->nextOrgPtr;
		}
		}
		else
		{
			while (currentPtr != NULL)
			{
				puts(currentPtr->orgName);
				currentPtr = currentPtr->nextOrgPtr;
			}
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

		while (currentPtr != NULL && !(strcmpIgnoreCase(newOrgPtr->orgName, currentPtr->orgName) < 0)) {
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
	 
	char yesOrNo = ' ';
	bool validEmail = false;
	do
	{
		do
		{
		puts("Enter email address.");
		fgetsNoNewLine(orgPtr->email, SIZE, stdin);
		//validEmail = true;
		validEmail = validateEmail(orgPtr->email);
		} while (!validEmail);
		
		puts("Is this email correct?");
		yesOrNo = validateYesNo();
	} while (!(yesOrNo == 'y'));
	
	bool validPass = false;
	do
	{

	puts("Enter password.");
	fgetsNoNewLine(orgPtr->password, SIZE, stdin);
	validPass = validatePassword(orgPtr->password);
	} while (!validPass);

	createRecieptFile(orgPtr->filePath, orgPtr->orgName);
	generateUrl(orgPtr->url, orgPtr->orgName);
	orgPtr->totalDonationAmount = 0;
	orgPtr->totalDonors = 0;
	orgPtr->totalProcessingAmount = 0;

	displayInfo(orgPtr);

}

void freeRemainingOrgs(Organization** headPtr)
{
	Organization* currentPtr = *headPtr;
	Organization* nextOrgPtr = NULL;

	//while list has data, delete data and move to next
	while (currentPtr != NULL)
	{
		nextOrgPtr = currentPtr->nextOrgPtr;
		free(currentPtr);
		currentPtr = nextOrgPtr;
	}

	*headPtr = NULL;
}//freeRemainingOrgs

void orgSummary(Organization* headPtr)
{
	Organization* currentPtr = headPtr;
	FILE *fPtr;
	char fileLocation[SIZE];
	strcpy(fileLocation, FOLDER_PATH);
	strcat(fileLocation, "orgs.txt");
	fPtr = fopen(fileLocation, "w");
	while (currentPtr != NULL)
	{
		fprintf(fPtr, "Organization Name: %s\nTotal Number of Donations: %d\n", currentPtr->orgName, currentPtr->totalDonors);
		fprintf(fPtr, "Total Amount Raised: $%lf\n", currentPtr->totalDonationAmount);
		fprintf(fPtr, "Total Credit Card Processing: $%lf\n\n", currentPtr->totalProcessingAmount);
		printf("Organization Name: %s\nTotal Number of Donations: %d\n", currentPtr->orgName, currentPtr->totalDonors);
		printf("Total Amount Raised: $%lf\n", currentPtr->totalDonationAmount);
		printf("Total Credit Card Processing: $%lf\n\n", currentPtr->totalProcessingAmount);
		currentPtr = currentPtr->nextOrgPtr;
	}
	fclose(fPtr);
}

int strcmpIgnoreCase(const char* str1, const char* str2)
{
	char lowerStr1[SIZE];
	char lowerStr2[SIZE];
	strcpy(lowerStr1, str1);
	strcpy(lowerStr2, str2);

	for (int i = 0; i < sizeof(lowerStr1); i++)
	{
		lowerStr1[i] = tolower(lowerStr1[i]);
	}

	for (int i = 0; i < sizeof(lowerStr2); i++)
	{
		lowerStr2[i] = tolower(lowerStr2[i]);
	}

	return strcmp(lowerStr1, lowerStr2);
}//strcmpIgnoreCase

void createRecieptFile(char filePath[] , const char orgName[])
{
	char orgNameWithDashes[SIZE] = { "" };
	strcpy(filePath, FOLDER_PATH);

	strncpy(orgNameWithDashes, orgName, sizeof(orgNameWithDashes));

	char* tokenPtr = strtok(orgNameWithDashes, " ");

	while (tokenPtr != NULL)
	{
		strcat(filePath, tokenPtr);
		tokenPtr = strtok(NULL, " ");
		if (tokenPtr != NULL)
		{
			strcat(filePath, "-");
		}
	}
	strcat(filePath, ".txt");

	FILE* fPtr;
	fPtr = fopen(filePath, "w");
	fclose(fPtr);
}

void updateReciept(char filePath[], double donateAmount, Organization* orgPtr)
{
	FILE* fPtr;
	fPtr = fopen(orgPtr->filePath, "a");
	time_t rawtime;
	struct tm* info;
	time(&rawtime);

	info = localtime(&rawtime);
	printf("Organization: %s\nDonation Amount: %.2lf\nDonation Date: ", orgPtr->orgName, donateAmount);
	fprintf(fPtr, "Organization: %s\nDonation Amount: %.2lf\nDonation Date: ", orgPtr->orgName, donateAmount);
	printf("%d/%d/%d - ", info->tm_mon + 1, info->tm_mday, info->tm_year + 1900);
	fprintf(fPtr, "%d/%d/%d - ", info->tm_mon + 1, info->tm_mday, info->tm_year + 1900);
	if ((info->tm_hour) > 12)
	{
		printf("%d:%d PM\n\n", info->tm_hour - 12, info->tm_min);
		fprintf(fPtr, "%d:%d PM\n\n", info->tm_hour - 12, info->tm_min);
	}
	else
	{
		printf("%d:%d AM\n\n", info->tm_hour, info->tm_min);
		fprintf(fPtr, "%d:%d AM\n\n", info->tm_hour, info->tm_min);
	}

	fclose(fPtr);
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
			} while (true);
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

bool newDonate(Organization* orgPtr)
{
	bool quit = false;
	double donateAmount = 0;
	double processingFee = PROCESSING_FEE;
	char donateNum[SIZE];
	char* endPtr;

	printf("\n\n%s\n", orgPtr->url);
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

	while (!(donateAmount > 0) && !quit)
	{
		puts("Enter the amount you want to donate.");
		fgetsNoNewLine(donateNum, SIZE, stdin);
		if (tolower(donateNum[0]) == 'q')
		{
			quit = adminSummary(orgPtr);
		}

		donateAmount = strtod(donateNum, &endPtr);
	}

	if (!quit)
	{
		char donaterName[SIZE];
		char zipCodeString[SIZE];
		int zipCode = 0;
		char yesOrNo = ' ';

		orgPtr->totalDonationAmount += donateAmount;
		orgPtr->totalDonors++;
		orgPtr->totalProcessingAmount += (donateAmount * processingFee);
		puts("Please enter your first and last name.");
		fgetsNoNewLine(donaterName, SIZE, stdin);
		do
		{
			puts("Please enter your zip code.");
			fgetsNoNewLine(zipCodeString, SIZE, stdin);
			zipCode = strtol(zipCodeString, &endPtr, 10);
		} while (!validateZipCode(zipCode));
		printf("Thank you for your donation.There is a %lf%% credit card processing fee of %.2lf. % .2lf will be donated.",
			(processingFee*100), (donateAmount * processingFee), donateAmount);
		puts("Do you want a reciept?");
		yesOrNo = validateYesNo();

		//change this into seperate function
		if (yesOrNo == 'y')
		{
			updateReciept(orgPtr->filePath, donateAmount, orgPtr);
		}
	}

	return quit;

}

//generates a url for the donation organization based on the organization name. the url displays as "https:donate.com/[organization-name]?form=popup#"
void generateUrl( char url[], const char orgName[])
{
	strcpy(url, "https:donate.com/");

	char orgNameWithDashes[SIZE] = {""};
	strncpy(orgNameWithDashes, orgName, sizeof(orgNameWithDashes));

	char* tokenPtr = strtok(orgNameWithDashes, " ");

	while (tokenPtr != NULL)
	{
		strcat(url, tokenPtr);
		tokenPtr = strtok(NULL, " ");
		if (tokenPtr != NULL)
		{
		strcat(url, "-");
		}
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
	int attempts = 3;
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

bool validateEmail(const char email[])
{
	bool isValid = false;
	char emailCopy[SIZE] = { "" };
	strcpy(emailCopy, email);
	char* tokenPtr = strtok(emailCopy, "@");
	if (tokenPtr != NULL)
	{
		tokenPtr = strtok(NULL, ".");
		if (tokenPtr != NULL)
		{
			isValid = true;
		}
	}

	return isValid;
}//validateEmail

//returns true if password has at least 1 capital, lowercase, and number, and is at least 7 characters long
bool validatePassword(const char password[])
{
	bool isValid = false;
	bool number = false;
	bool capital = false;
	bool lower = false;
	
	if ((strlen(password)) >= 7)
	{
		for (int i = 0; i < strlen(password); i++)
		{
			if (password[i]>= 'A' && password[i] <= 'Z')
			{
				capital = true;
			}
			if (password[i] >= '0' && password[i] <= '9')
			{
				number = true;
			}
			if (password[i] >= 'a' && password[i] <= 'z')
			{
				lower = true;
			}

		}
		if (number && capital && lower)
		{
			isValid = true;
		}
	}

	return isValid;
}
