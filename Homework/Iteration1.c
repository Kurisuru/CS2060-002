
#include <stdbool.h>

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
void generateUrl(Organization* orgPtr);
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

	puts("Enter fundraising  organization name.");
	//fgets(orgPtr->orgName, SIZE, stdin);

	puts("Enter fundraiser  purpose.");

	puts("Enter first and last name.");

	puts("Enter the goal amount you want to raise.");

	puts("Enter email address.");

	puts("Enter password.");


}

void donate(Organization* orgPtr)
{

}

void generateUrl(Organization* orgPtr)
{

}

void displayInfo(const Organization* orgPtr)
{

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

//fgets