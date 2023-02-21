#include <stdio.h>

#define STUDENTS 4
#define GRADE_CATEGORIES 5
#define CATEGORIES "1. Learning Activity 2. Homework 3. Project 4. Midterm 5. Final "
const double GRADE_CATEGORY_WEIGHT[] = { 0.1, 0.3, 0.3, 0.15, .15 };

void printStatements();
void enterGrades(double grades[][GRADE_CATEGORIES]);

int main(void)
{
    printStatements();

}

void printStatements()
{
    puts("This program will calculate the grades for these categories");
    puts(CATEGORIES);
    puts("The weights for these categories are");
    for(int i = 0; i < GRADE_CATEGORIES; i++) {
        printf("Category %d weight is %.2f\n", i+1, GRADE_CATEGORY_WEIGHT[i]);
    }

    puts("The correct order to enter grades for each student is: ");
    puts(CATEGORIES);

}

void enterGrades(double grades[][GRADE_CATEGORIES])
{

}

