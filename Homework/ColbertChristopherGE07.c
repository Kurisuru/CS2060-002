
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define STRING_SIZE 80

typedef struct pet
{
	char name[STRING_SIZE];
	int age;
	struct pet* nextPetPtr;
}Pet;

char* fgetsNoNewLine(char* str, int size, FILE* stream);
void insertPet(Pet** headPtr, char name[], int age);
void deletePet(Pet** headPtr, char name[]);
void freeRemainingPets(Pet** headPtr);
void printList(Pet* listPtr);
char validateYesNo();

int main(void)
{
	Pet* headPetPtr = NULL;
	char ageToInt[STRING_SIZE];
	int petAge = 0;
	char petName[STRING_SIZE];
	char yesOrNo = ' ';
	char* endPtr;
	
	do
	{
		//Focusing on linked lists so not validating that a number was entered
		printf("%s", "Enter pet name ");
		fgetsNoNewLine(petName, STRING_SIZE, stdin);
		printf("%s", "Enter pet age ");
		fgetsNoNewLine(ageToInt, STRING_SIZE, stdin);
		endPtr = ageToInt;
		petAge = strtod(ageToInt, &endPtr);

		// inserts pet with petName, and petAge
		insertPet(&headPetPtr, petName, petAge);

		// why does insert node pass the address of head pointer but print list does not?
		
		printf("%s", "\nDo you want to add another pet?");

		yesOrNo = validateYesNo();
	} while (yesOrNo == 'y');
	printList(headPetPtr);
	
	//delete pets until n is entered.
	do
	{
		//
		printf("%s", "\nEnter pet in the list to delete ");
		fgetsNoNewLine(petName, STRING_SIZE, stdin);

		//deletes pet held in list with passed string of petName
		deletePet(&headPetPtr, petName);

		// why does deleteNode pass the address of head pointer but print list does not?
		printList(headPetPtr);

		printf("%s", "\nDo you want to delete another pet? ");
		yesOrNo = validateYesNo();

	} while ((yesOrNo == 'y') && (headPetPtr != NULL));

	puts("clearing all remaining pets.");
	freeRemainingPets(&headPetPtr);
	printList(headPetPtr);

	return 0;
}



//prints linked list in alphabetical order
void printList(Pet* listPtr)
{
	// if list has data inside
	if (listPtr != NULL)
	{
		puts("\nThe names in alphabetical order");
		//
		Pet* currentPtr = listPtr;

		// traverse through the list until there is no more data
		while (currentPtr != NULL)
		{
			// display and go to next node
			printf("%s is %d years old\n", currentPtr->name, currentPtr->age);
			currentPtr = currentPtr->nextPetPtr;
		}
	}
	// if list head is NULL, there is no data in the list
	else
	{
		puts("List is empty");
	}
} // printList

//gets input of Y/y or N/n and returns that char
char validateYesNo() {
	char validYesNo;

	do {
		puts("Please enter (y)es or (n)o:");
		validYesNo = getchar();
		while (getchar() != '\n');

		validYesNo = tolower(validYesNo);

	} while (validYesNo != 'y' && validYesNo != 'n');

	return  validYesNo;
} //validateYesNo

//compares 2 strings while ignoring case sensitivity. retures 0 if strings are the same
int strcmpIgnoreCase(const char* str1, const char* str2) 
{
	char lowerStr1[STRING_SIZE];
	char lowerStr2[STRING_SIZE];
	strcpy(lowerStr1, str1);
	strcpy(lowerStr2, str2);

	for (int i = 0; i<sizeof(lowerStr1); i++)
	{
		lowerStr1[i] = tolower(lowerStr1[i]);
	}
	
	for (int i = 0; i < sizeof(lowerStr2); i++)
	{
		lowerStr2[i] = tolower(lowerStr2[i]);
	}

	return strcmp(lowerStr1, lowerStr2);
}//strcmpIgnoreCase

//gets input from a stream and stores it in str.
//removes the new line character from the end of the string
char* fgetsNoNewLine(char* str, int size, FILE* stream)
{
	char* returnVal = NULL;
	char* newlinePtr;
	if (fgets(str, size, stream) != NULL)
	{
		if ((newlinePtr = strchr(str, '\n')) != NULL)
		{
			*newlinePtr = '\0';

		}
		returnVal = str;
	}

	return returnVal;
} //fgetsNoNewLine

//inserts a pet in the linked list alphabetically
void insertPet(Pet** headPtr, char name[], int age)
{
	// allocate memory for new pet
	Pet* newPetPtr = malloc(sizeof(Pet));

	// if memory was allocated, initialize
	if (newPetPtr != NULL)
	{
		//initialize name, age and nextPet
		strcpy(newPetPtr->name, name);
		newPetPtr->age = age;
		newPetPtr->nextPetPtr = NULL;

		
		Pet* previousPtr = NULL;
		Pet* currentPtr = *headPtr;

		//
		while (currentPtr != NULL && strcmpIgnoreCase(currentPtr->name, name) == -1)
		{
			
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPetPtr;
		}

		// if pet needs to be added to first index of list
		if (previousPtr == NULL)
		{
			*headPtr = newPetPtr;
		}
		else
		{
			previousPtr->nextPetPtr = newPetPtr;
		}

		newPetPtr->nextPetPtr = currentPtr;
	}
	// no memory available
	else
	{
		printf("No memory to create Pet for %s\n", name);
	}
} // insertPet

//deletes pet with specified name in list.
void deletePet(Pet** headPtr, char name[])
{
	Pet* previousPtr = NULL;
	Pet* currentPtr = *headPtr;

	//if list has data
	if (*headPtr != NULL)
	{
		//if strings match
		if (strcmp((*headPtr)->name, name) == 0)
		{
			//
			*headPtr = (*headPtr)->nextPetPtr;
			// 
			free(currentPtr);
			currentPtr = NULL;
		}
		else //strings dont match, so traverse until match is found
		{
			
			while (currentPtr != NULL && strcmp(currentPtr->name, name) != 0)
			{
			
				previousPtr = currentPtr;
				currentPtr = currentPtr->nextPetPtr;
			}

				
			if (currentPtr != NULL)
			{
				
				previousPtr->nextPetPtr = currentPtr->nextPetPtr;
				
				free(currentPtr);
				currentPtr = NULL;
			}
			else
			{
				printf("%s is not found on the list!", name);
			}
		}
	}
	//match was not found in list.
	else 
	{
		puts("There aren't any Pets in the list!");
	}

} //deletePet

//deletes all remaining data in linked list.
void freeRemainingPets(Pet** headPtr)
{
	Pet* currentPtr = *headPtr;
	Pet* nextPetPtr = NULL;

	//while list has data, delete data and move to next
	while (currentPtr != NULL)
	{
		nextPetPtr = currentPtr->nextPetPtr;
		free(currentPtr);
		currentPtr = nextPetPtr;
	}

	*headPtr = NULL;
}//freeRemainingPets