#define _CRT_SECURE_NO_DEPRECATE
#include<stdlib.h>
#include<string.h>
#include <conio.h>
#include"linkedlist.h"

//Main function
int main()
{
	nodeT* headPtr = NULL;
	int choice;

	//Array used to store login records
	login loginRecords[MAX_RECORDS];

	//Calling on function to load login records from a text file
	loadLogins(loginRecords);

	//Gives an output based on if login was successful
	if (validateLogin(loginRecords))
	{
		printf("Login Successful!\n");
	}
	else
	{
		printf("Invalid username or password.\n");
		return 0;
	}

	//Calling on function to load accounts from text file
	loadFromFile(&headPtr);

	//Menu that that takes in user input
	printf("Enter 1 to add an account\n");
	printf("Enter 2 to display accounts with a balance less than £100\n");
	printf("Enter 3 to display account holder details\n");
	printf("Enter 4 to lodge to account\n");
	printf("Enter 5 to withdraw from account\n");
	printf("Enter 6 to delete an account\n");
	printf("Enter 7 to generate statistics\n");
	printf("Enter 8 to print report\n");
	printf("Enter -1 to terminate program\n");
	scanf("%d", &choice);

	//Loop until terminated
	while (choice != -1)
	{
		if (choice == 1)
		{
			addAccount(&headPtr);
		}
		else if (choice == 2)
		{
			displayBal(headPtr);
		}
		else if (choice == 3)
		{
			displayAcc(headPtr);
		}
		else if (choice == 4)
		{
			lodgeToAcc(headPtr);
		}
		else if (choice == 5)
		{
			withdrawFromAcc(headPtr);
		}
		else if (choice == 6)
		{
			deleteAccount(&headPtr);
		}
		else if (choice == 7)
		{
			generateStats(headPtr);
		}
		else if (choice == 8)
		{
			printReport(headPtr);
		}
		else
		{
			//If user input is invalid exit program
			return 0;
		}
		//Displays menu again until program terminated
		printf("Enter 1 to add an account\n");
		printf("Enter 2 to display accounts with a balance less than £100\n");
		printf("Enter 3 to display account holder details\n");
		printf("Enter 4 to lodge to account\n");
		printf("Enter 5 to withdraw from account\n");
		printf("Enter 6 to delete an account\n");
		printf("Enter 7 to generate statistics\n");
		printf("Enter 8 to print report\n");
		printf("Enter -1 to terminate program\n");
		scanf("%d", &choice);
	}
	//Calling on function to save user inputs to text file and then terminate program
	saveList(headPtr);
	return 0;
}