/*
* The program randomly generates numbers   
* between 1 and 1000 for the user to guess.
*/


// 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// sets a variable for the minimum number
#define MIN_NUMBER 1

// sets a constant variable for the maximum number 
const int MAX_NUMBER = 100;

// runs the guessGame function
void guessGame(void); 
bool isCorrect(int, int); 


int main(void)
{
    //
   //srand(time(0));

   //
   guessGame(); 

   //
   return 0;
}

// chooses a random number, user guesses until their guess matches the random number
void guessGame(void)
{
    // initializes random number, user guess, and response variables
   int answer = 0; 
   int guess = 0; 
   int response = 0; 

   do {

       // sets a random number in the answer variable
      answer = MIN_NUMBER + rand() % MAX_NUMBER;


      // prompts user for a guess
      printf("Hello, I have a number between %d and %d .\n" 
          "Can you guess my number?\n"
           "Please type your first guess.", MIN_NUMBER, MAX_NUMBER);

      // loop until user types 2 to end game
      do
      {
          // get user guess until it is equal to the random number
          scanf("%d", &guess);
      } while (!isCorrect(guess, answer));
         
      // after user guesses correctly, prompt to end game or start again
      puts("\nExcellent! You guessed the number!\n"
         "Would you like to play again?");

      printf("%s", "Please type ( 1=yes, 2=no ) ");
      scanf("%d", &response);

      puts("");
   } while (response == 1);
} 

// check user guess against answer. if incorrect, give hint
bool isCorrect(int g, int a)
{
    // initialize boolean to determine if guess is correct
    bool found = false;

    // determine if guess is correct, too high, or too low. 
    if (g == a){
        found = true;
    }else  if (g < a)
      printf( "%s", "Too low. Try again.\n? " );
   else
      printf( "%s", "Too high. Try again.\n? " );

    // return 
   return found;
} 

