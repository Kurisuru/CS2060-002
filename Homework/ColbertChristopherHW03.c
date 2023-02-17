#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#define MIN_CHARGE_VAL 2
#define MIN_CHARGE_HOURS 3
#define MIN_HOURS_ALLOWED 0
#define MAX_CHARGE_VAL 10
#define MAXIMUM_HOURS_ALLOWED 24
#define ADDITIONAL_HOURS_RATE 0.75
#define SENTINEL_VAL -1


double getValidHours();
double calculateCharge(double);
void displaySummary(int, int);

int main(void)
{
	double sumCharges = 0;
	double totalHours = 0;
	int totalCars = 0;
    totalHours = getValidHours();
}

double getValidHours()
{
	double hours = 0;
    int scanReturn = 0;
	bool isValid = false;
    do
    {
        if (getchar() != "\n") 
        {
        }
            printf("%s\n", "Enter the number of hours the car was parked or enter -1 to quit.");
            scanReturn = scanf("%lf", &hours);
            if (scanReturn == 1)
            {
                if (hours > MIN_HOURS_ALLOWED && hours <= MAXIMUM_HOURS_ALLOWED)
                    isValid = true;
                else if (hours == SENTINEL_VAL)
                    isValid = false;
            }
    } while (!isValid);
	return hours;
}

double calculateCharge(double calcHours) 
{
    double charge = 0;
    if (calcHours < MIN_CHARGE_HOURS)
        charge = MIN_CHARGE_VAL;
    else
        charge = (ceil(calcHours) - MIN_CHARGE_HOURS) * ADDITIONAL_HOURS_RATE + MIN_CHARGE_VAL;
    return charge;
}
void displaySummary(int totalHours, int totalCars) 
{

}
/*#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void guessGame(void); // function prototype
int isCorrect(int, int); // function prototype

int main(void)
{
    // srand( time( 0 ) ); // seed random number generator
     //update with your name
    puts("Hello Chris");
    guessGame();

} // end main

// guessGame generates numbers between 1 and 1000
// and checks user's guess
void guessGame(void)
{
    int answer; // randomly generated number
    int guess; // user's guess
    int response; // 1 or 2 response to continue game

    // loop until user types 2 to quit game
    do {
        // generate random number between 1 and 1000
        // 1 is shift, 1000 is scaling factor
        answer = 1 + rand() % 1000;

        // prompt for guess
        puts("I have a number between 1 and 1000.\n"
            "Can you guess my number?\n"
            "Please type your first guess.");
        printf("%s", "? ");
        scanf("%d", &guess);

        // loop until correct number
        while (!isCorrect(guess, answer))
            scanf("%d", &guess);

        // prompt for another game
        puts("\nExcellent! You guessed the number!\n"
            "Would you like to play again?");
        printf("%s", "Please type ( 1=yes, 2=no )? ");
        scanf("%d", &response);

        puts("");
    } while (response == 1);
} // end function guessGame

// isCorrect returns true if g equals a
// if g does not equal a, displays hint
int isCorrect(int g, int a)
{
    // guess is correct
    if (g == a)
        return 1;

    // guess is incorrect; display hint
    if (g < a)
        printf("%s", "Too low. Try again.\n? ");
    else
        printf("%s", "Too high. Try again.\n? ");

    return 0;
} // end function */