#define _CRT_SECURE_NO_DEPRECATE
#include<stdlib.h>
#include<string.h>
#include"linkedlist.h"

int main()
{
    //Initialise head pointer for the linked list
    nodeT* headPtr = NULL;
    int choice;
    int result;
    //Initialise statistics structure with zeros
    statistics stats = {0};
    //Arry to hold login credentials
    login loginRecords[MAX_RECORDS];

    loadLogins(loginRecords);

    //Validate login credentials
    if (validateLogin(loginRecords)) {
        printf("Login successful!\n");
    }
    else {
        printf("Invalid username or password.\n");
        return 0; //Exit program if login fails
    }

//Load player data from file
   loadFromFile(&headPtr);

   //Display menu options
   printf("Please enter 1 to add a player to the list\n");
   printf("Please enter 2 to display all player\n");
   printf("Please enter 3 to display a specific player\n");
   printf("Please enter 4 to update a player from the list\n");
   printf("Please enter 5 to delete a player from the list\n");
   printf("Please enter 6 to calculate player statistics\n");
   printf("Please enter 7 to print report\n");
   printf("Please enter -1 to terminate\n");
   scanf("%d", &choice);

   
   //Process user choice
    while (choice != -1)
    {
        if (choice == 1)
        {
            addPlayer(&headPtr);
        }

        else if (choice == 2)
        {
            display(headPtr);
        }

        else if (choice == 3)
        {
            displayPlayer(headPtr);
        }

        else if (choice == 4)
        {
            updatePlayer(headPtr);
        }

        else if (choice == 5)
        {
            deletePlayer(headPtr);
        }

        else if (choice == 6)
        {
            stats = countPlayerByValue(headPtr);
        }

        else if (choice == 7)
        {
           printReport(headPtr, stats);
        }

        //Prompt for next choice
        printf("Please enter 1 to add a player to the list\n");
        printf("Please enter 2 to display all player\n");
        printf("Please enter 3 to display a specifies player\n");
        printf("Please enter 4 to update a player from the list\n");
        printf("Please enter 5 to delete a player from the list\n");
        printf("Please enter 6 to calculate player statistics\n");
        printf("Please enter 7 to print report\n");
        printf("Please enter -1 to terminate\n");
        scanf("%d", &choice);
    }
    saveList(headPtr);
    return 0;
}

