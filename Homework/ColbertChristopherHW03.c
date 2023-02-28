#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define MIN_CHARGE_VAL 3
#define MIN_HOURS_AT_FLAT_RATE 3
#define MIN_HOURS_ALLOWED 0
#define MAX_CHARGE_VAL 12
#define MAXIMUM_HOURS_ALLOWED 24
#define ADDITIONAL_HOURS_RATE 0.75
#define SENTINEL_VAL -1

double getValidHours();
double calculateCharge(double);
void displaySummary(double, int, double);

int main(void)
{
    double hours = 0;
    double charge = 0;
	double sumCharges = 0;
	double sumHours = 0;
	int sumCars = 0;

    do//clear buffer
    {
        //collect user input, once the input is valid store it
        hours = getValidHours();
        //if user input is not sentinel value perform calculations and keep looping to get user input
        if (hours != SENTINEL_VAL)
        {
            sumHours += hours;
            charge = calculateCharge(hours);
            sumCharges += charge;
            sumCars++;
            printf("%s\n%d\t%.1lf\t%.2lf\n", "Car\tHours\tCharge", sumCars, hours, charge);
        }
    } while (hours != SENTINEL_VAL);
    displaySummary(sumHours, sumCars, sumCharges);
    return 0;
}

//gets user data until it is valid
double getValidHours()
{
	double hours = 0;
    int scanReturn = 0;
	bool isValid = false;
    do
    {
            printf("%s\n", "Enter the number of hours the car was parked or enter -1 to quit.");
            scanReturn = scanf("%lf", &hours);
            if (scanReturn == 1)
            {
                if ((hours > MIN_HOURS_ALLOWED && hours <= MAXIMUM_HOURS_ALLOWED) || hours == SENTINEL_VAL)
                    isValid = true;
                else
                    puts("Your number must be between 0 and 24 hours");
            }
            else
                puts("You did not enter a number");
        while ((getchar()) != '\n');
    } while (!isValid);
	return hours;
}

//calculate charge based on valid data and global definitions
double calculateCharge(double calcHours) 
{
    double charge = 0;
    if (calcHours < MIN_HOURS_AT_FLAT_RATE)
        charge = MIN_CHARGE_VAL;
    else
        charge = (ceil(calcHours) - MIN_HOURS_AT_FLAT_RATE) * ADDITIONAL_HOURS_RATE + MIN_CHARGE_VAL;
    if (charge >= MAX_CHARGE_VAL)
        charge = MAX_CHARGE_VAL;
    return charge;
}

//display a summary of totaln cars, hours, and charges
void displaySummary(double totalHours, int totalCars, double totalCharges)
{
        puts("Parking Garage Summary");
    if (totalCars > 0)
        printf("%s\n%d\t\t%.1lf\t\t%.2lf", "Total Cars\tTotal Hours\tTotal Charges", totalCars, totalHours, totalCharges);
    else
        puts("There were no cars parked today");
}