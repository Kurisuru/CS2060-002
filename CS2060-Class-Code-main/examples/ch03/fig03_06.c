// Fig. 3.6: fig03_06.c
// Class average program with counter-controlled iteration

#include <stdio.h>

//const to hold number of grades so not hard coded
const unsigned int NUMBER_GRADES = 10;

int main( void )
{
   //initialize variables 
   unsigned int counter = 0; // number of grade entered
   int grade =0 ; // grade value
   int total =0; // sum of grades entered by user
   double average =0; // average of grades
   
  printf("Enter %u grades.\n", NUMBER_GRADES);
  
   //enter and sum grades
   while ( counter < NUMBER_GRADES) {
       counter = counter + 1;
      printf("Enter grade %d: ",  counter); 
      scanf( "%d", &grade ); 
      total += grade; 
      
   } // end while
   
   //cast to float to get acurate average from integer division
   average = (double)total / NUMBER_GRADES; 
   printf( "Class average is %.2lf\n", average ); 

   return 0; //return value of main function
} // end function main

