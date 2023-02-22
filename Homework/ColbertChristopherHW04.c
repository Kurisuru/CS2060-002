#include <stdio.h>
#include <stdbool.h>

#define STUDENTS 4
#define GRADE_CATEGORIES 5
#define CATEGORIES "1. Learning Activity 2. Homework 3. Project 4. Midterm 5. Final "
const double GRADE_CATEGORY_WEIGHT[] = { 0.1, 0.3, 0.3, 0.15, .15 };
#define GRADE_MAX 100
#define GRADE_MIN 0

void printStatements();
void enterGrades(int grades[][GRADE_CATEGORIES], size_t pupils, size_t exams);
int getValidGrade();
void printGrades(const int grades[][GRADE_CATEGORIES], size_t pupils, size_t exams);
void calculateGrades(int finalStudentGrades[], int grades[][GRADE_CATEGORIES], size_t pupils, size_t exams);

int main(void)
{
    int grades[STUDENTS][GRADE_CATEGORIES] = { 0 };
    int finalStudentGrades[STUDENTS] = { 0 };
    printStatements();
    enterGrades(grades, STUDENTS, GRADE_CATEGORIES);
    printGrades(grades, STUDENTS, GRADE_CATEGORIES);
    calculateGrades(finalStudentGrades, grades, STUDENTS, GRADE_CATEGORIES);
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
    puts("");

}

void enterGrades(int grades[][GRADE_CATEGORIES],size_t pupils, size_t exams)
{
    for (size_t row = 0; row < pupils; row++) {
        puts("");
        for (size_t col = 0; col < exams; col++) {
            printf("Enter the grade for student %llu for category %llu: ", row+1, col+1);
            grades[row][col] = getValidGrade();
        }
    }
}

int getValidGrade()
{
    int grade = 0;
    int scanReturn = 0;
    bool isValid = false;
    do
    {
        
        scanReturn = scanf("%d", &grade);
        if (scanReturn == 1)
        {
            if (grade > GRADE_MIN && grade < GRADE_MAX)
            {
                isValid = true;
            }
            else
                puts("invalid");
        }
        else
            puts("You entered an invalid grade, try again");
        while ((getchar()) != '\n');
    } while (!isValid);
    return grade;
}

void printGrades(const int grades[][GRADE_CATEGORIES], size_t pupils, size_t exams)
{
    for (size_t rows = 0; rows < STUDENTS; rows++) {
        puts("");
        printf("Student %llu: ", rows + 1);
        for (size_t cols = 0; cols < GRADE_CATEGORIES; cols++) {
            printf("%d\t", grades[rows][cols]);
        }
    }
}

void calculateGrades(int finalStudentGrades[], int grades[][GRADE_CATEGORIES], size_t pupils, size_t exams)
{
    for (size_t rows = 0; rows < STUDENTS; rows++) {
        puts("");
        printf("Student %llu: ", rows + 1);
        double finalGrade = 0;
        //calculate weighted category grade for student by multiplying the category grades and the weight and then add it to the final grade
        for (size_t cols = 0; cols < GRADE_CATEGORIES; cols++) {
            finalGrade =+ grades[rows][cols] * GRADE_CATEGORY_WEIGHT[cols];
            printf("%lf", finalGrade);
        }
        //save final Grade to student
        finalStudentGrades[rows] = finalGrade;
    }
}