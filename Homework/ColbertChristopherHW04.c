#include <stdio.h>
#include <stdbool.h>

#define STUDENTS 4
#define GRADE_CATEGORIES 5
#define CATEGORIES "1. Learning Activity 2. Homework 3. Project 4. Midterm 5. Final "
const double GRADE_CATEGORY_WEIGHT[] = { 0.1, 0.3, 0.3, 0.15, .15 };
#define GRADE_MAX 105
#define GRADE_MIN 0

void enterGrades(int grades[][GRADE_CATEGORIES], size_t pupils, size_t exams);
int getValidGrade();
void printStatements();
void printGrades(const int GRADES[][GRADE_CATEGORIES], size_t pupils, size_t exams);
void printFinalGrades(const double finalStudentGrades[]);
void calculateGrades(double finalStudentGrades[], int grades[][GRADE_CATEGORIES], size_t pupils, size_t exams);
double calculateClassAverage(double FINAL_STUDENT_GRADES[], int students);

int main(void)
{
    int grades[STUDENTS][GRADE_CATEGORIES] = { 0 };
    double finalStudentGrades[STUDENTS] = { 0 };
    printStatements();
    enterGrades(grades, STUDENTS, GRADE_CATEGORIES);
    printGrades(grades, STUDENTS, GRADE_CATEGORIES);
    calculateGrades(finalStudentGrades, grades, STUDENTS, GRADE_CATEGORIES);
    printFinalGrades(finalStudentGrades);
    printf("\nClass average is %.2lf", calculateClassAverage(finalStudentGrades, STUDENTS));
}

//prints categories for each student, and tells user the order to enter the grades
void printStatements()
{
    puts("This program will calculate the grades for these categories");
    puts(CATEGORIES);
    puts("\nThe weights for these categories are");
    for(int i = 0; i < GRADE_CATEGORIES; i++) {
        printf("Category %d weight is %.2f\n", i+1, GRADE_CATEGORY_WEIGHT[i]);
    }

    puts("\nThe correct order to enter grades for each student is: ");
    puts(CATEGORIES);
    puts("");

}

//enter grades into 2d grade array
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

//validate that grade entered is an integer number between 0 and 105 (inclusive
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
            if (grade >= GRADE_MIN && grade <= GRADE_MAX)
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

//print grades from each category, for each student
void printGrades(const int GRADES[][GRADE_CATEGORIES], size_t pupils, size_t exams)
{
    puts("Grades entered for each student");
    for (size_t rows = 0; rows < STUDENTS; rows++) {
        puts("");
        printf("Student %llu: ", rows + 1);
        for (size_t cols = 0; cols < GRADE_CATEGORIES; cols++) {
            printf("%d\t", GRADES[rows][cols]);
        }
    }
}

//calculate the final grade of each student using the grade category weights
void calculateGrades(double finalStudentGrades[], int grades[][GRADE_CATEGORIES], size_t pupils, size_t exams)
{
    for (size_t rows = 0; rows < STUDENTS; rows++) {
        double finalGrade = 0;
        //calculate weighted category grade for student by multiplying the category grades and the weight and then add it to the final grade
        for (size_t cols = 0; cols < GRADE_CATEGORIES; cols++) {
            finalGrade += grades[rows][cols] * GRADE_CATEGORY_WEIGHT[cols];
        }
        //save final Grade to student
        finalStudentGrades[rows] = finalGrade;
       
    }
}

//prints final weighted grades for each student, and the corresponding letter grade
void printFinalGrades(const double FINAL_STUDENT_GRADES[])
{
    puts("\nFinal grades for students");
    for (size_t i = 0; i < STUDENTS; i++)
    {
        puts("");
        printf("Student %llu: ", i + 1);
        printf("%.2lf", FINAL_STUDENT_GRADES[i]);
        if (FINAL_STUDENT_GRADES[i] >= 90 && FINAL_STUDENT_GRADES[i] <= 105)
        {
            printf(" %c", 'A');
        }
        else if (FINAL_STUDENT_GRADES[i] >= 80 && FINAL_STUDENT_GRADES[i] < 90)
        {
            printf(" %c", 'B');
        }
        else if (FINAL_STUDENT_GRADES[i] >= 70 && FINAL_STUDENT_GRADES[i] < 80)
        {
            printf(" %c", 'C');
        }
        else if (FINAL_STUDENT_GRADES[i] >= 60 && FINAL_STUDENT_GRADES[i] < 70)
        {
            printf(" %c", 'D');
        }
        else if (FINAL_STUDENT_GRADES[i] < 60)
        {
            printf(" %c", 'F');
        }
    }
}

//calculates class average
double calculateClassAverage(double finalStudentGrades[], int students)
{
    double classAverage = 0;
    for (int i = 0; i < students; i++)
    {
        classAverage = classAverage + finalStudentGrades[i];
    }
    classAverage = classAverage / students;
    return classAverage;
}