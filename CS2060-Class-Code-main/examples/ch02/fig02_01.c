// Fig. 2.1: fig02_01.c
// A first program in C 
#include <stdio.h>

// function main begins program execution 
int main( void )
{
	int length = 0;
	int width = 0;
	int area = 0;
	double average = 0;
	
	printf("%s\n", "Enter the length");
	scanf("%i",&length);

	printf("%s\n", "Enter the width");
	scanf("%i", &width);

	average = ((double)length + (double)width) / 2;
	printf("%s %.1f\n","Average:", average);
	area = length * width;
	printf("%s%i %s%i %s%i", "Length: ", length, "width: ", width, "and area is ", area);
   //printf("%s\n", "Welcome to C!" );

	return 0;
} // end function main 


/**************************************************************************
 * (C) Copyright 1992-2015 by Deitel & Associates, Inc. and               *
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
