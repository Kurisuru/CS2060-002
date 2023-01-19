// Fig. 3.8: fig03_08.c
// Class average program with sentinel-controlled iteration
#include <stdio.h>


int main( void )
{
   // initialize variables
   unsigned int counter = 0; // number of grades entered
   int grade = 0; // grade value
   int total = 0; // sum of grades
   float average = 0; // number with decimal point for average
   
   // get first grade from user
   printf( "%s", "Enter grade, -1 to end: " ); 
   scanf( "%d", &grade ); 
   
   // loop while sentinel value not yet read from user
   while ( grade != -1 ) {
      total += grade; 
      counter += 1; 
      // get next grade from user
      printf( "%s", "Enter grade, -1 to end: " ); 
      scanf("%d", &grade);                 
   } // end while

   // if user entered at least one grade
   if ( counter != 0 ) {

      // calculate average of all grades entered
      average = ( float ) total / counter; // avoid truncation
      printf( "Class average is %.2f\n", average );  

   } // end if   
   else { // if no grades were entered, output message
      puts( "No grades were entered" );
   } // end else
} // end function main



/**************************************************************************
 * (C) Copyright 1992-2013 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/
