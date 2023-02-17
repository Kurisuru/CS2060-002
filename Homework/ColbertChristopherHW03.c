#include <stdio.h>
#include <stdbool.h>
#define MAX_CHARGE = 10;
#define MIN_CHARGE_HOURS = 3;
#define MIN_CHARGE = 2;
#define ADDITIONAL_HOURS_RATE = 0.75;

int main(void)
{
	double hours = 0;
	double charge = 0;
	double sumCharges = 0;
	double totalHours = 0;
	int totalCars = 0;
	int scanInput = 0;
	bool validInput = false;


	while (hours != -1) {
		printf("%s\n", "Enter the number of hours the car was parked or enter -1 to quit.");
		scanInput = scanf("%f", &hours);
		if (scanInput == 1) {
			//charge = validInput(hours);
	}
}

double validInput(int t); {
	double hours = 0;
	bool isValid = false;
	if ((t>0&&userInput<=24)||userInput==-1) {

	}
	return hours;
}

double calculateCharge(double calcHours); {
	double calcCharge = 0;
	if (calcHours > MIN_CHARGE_HOURS) {

	}
	return calcCharge;
}

void displaySummary(int totalHours, int totalCars); {

}