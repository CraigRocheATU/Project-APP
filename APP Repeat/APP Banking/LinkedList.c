#define _CRT_SECURE_NO_DEPRECATE
#include "LinkedList.h"

//Function used to load exsisting accounts for the text file
void loadFromFile(nodeT** top)
{
	FILE* inp;
	account accData;
	nodeT* temp;
	int rating;

	inp = fopen("accounts.txt", "r");

	if (inp == NULL)
	{
		printf("Cannot load accounts\n");
		return;
	}

	//Read account data from file
	while (fscanf(inp, "%d %19s %19s %[^\n] %lf %39s %d",
		&accData.accNum, accData.firstName, accData.secondName,
		accData.address, &accData.initBal, accData.email, &rating) == 7)
	{
		//Validate service rating
		if (rating < 1 || rating > 5)
		{
			printf("Invalid service rating: %d\n", rating);
			continue;
		}
		accData.serviceRating = rating;

		temp = (nodeT*)malloc(sizeof(nodeT));
		if (temp == NULL)
		{
			printf("Failed to allocate memory\n");
			fclose(inp);
			return;
		}

		temp->accData = accData;
		temp->NEXT = *top;
		*top = temp;
	}

	if (feof(inp))
	{
		printf("End of file reached.\n");
	}
	//else
	//{
		//printf("Error reading file.\n");
	//}

	fclose(inp);
}

//Function used to search for account number in the linked list
int search(nodeT* top, int searchNum)
{
	nodeT* temp = top;
	int found = 0;

	while (temp != NULL)
	{
		if (searchNum == temp->accData.accNum)
		{
			found = 1;
			break;
		}
		temp = temp->NEXT;
	}

	return found;
}

//Function used to validate and enter email
void checkEmail(nodeT* temp) {
	int found = 0;
	do {
		printf("Please enter your email\n");
		scanf("%s", temp->accData.email);

		while (getchar() != '\n');

		if (strchr(temp->accData.email, '@') != NULL && strstr(temp->accData.email, ".com") != NULL)
		{
			found = 1;
		}

		else
		{
			printf("Invalid email, @ and .com not present");
		}
	} while (!found);
}

//Function used to add a new account
void addAccount(nodeT** top)
{
	nodeT* temp;
	nodeT* current;
	temp = (nodeT*)malloc(sizeof(nodeT));

	if (temp == NULL)
	{
		printf("Failed to allocate memory for new account\n");
		return;
	}

	do {
		printf("Please enter Account Number\n");
		scanf("%d", &temp->accData.accNum);
		while (getchar() != '\n');

		if (search(*top, temp->accData.accNum))
		{
			printf("Account Number is in use, please enter a new Account Number\n");
		}
	} while (search(*top, temp->accData.accNum));

	printf("Please enter first name\n");
	scanf("%s", temp->accData.firstName);

	printf("Please enter surname\n");
	scanf("%s", temp->accData.secondName);
	while (getchar() != '\n'); 

	printf("Please enter address\n");
	fgets(temp->accData.address, sizeof(temp->accData.address), stdin);
	if (temp->accData.address[strlen(temp->accData.address) - 1] == '\n') {
		temp->accData.address[strlen(temp->accData.address) - 1] = '\0';
	}

	printf("Please enter Initial Balance\n");
	scanf("%lf", &temp->accData.initBal);
	while (getchar() != '\n');

	checkEmail(temp);

	// Create input for rating service
	int ratChoice;
	printf("How would you rate the pace of service in the bank?\n");
	printf("1. Excellent\n");
	printf("2. VeryGood\n");
	printf("3. Satisfactory\n");
	printf("4. Disappointing\n");
	printf("5. Bad\n");
	printf("Enter a choice from above\n");
	scanf("%d", &ratChoice);
	while (getchar() != '\n');

	
	if (ratChoice < 1 || ratChoice > 5)
	{
		printf("Invalid choice. Setting rating to 'Unknown'.\n");
		temp->accData.serviceRating = UNKNOWN;
	}
	else
	{
		temp->accData.serviceRating = ratChoice;
	}

	// Insert new node into linked list
	if (*top == NULL || (*top)->accData.accNum > temp->accData.accNum)
	{
		temp->NEXT = *top;
		*top = temp;
		return;
	}

	current = *top;
	while (current->NEXT != NULL && current->NEXT->accData.accNum < temp->accData.accNum)
	{
		current = current->NEXT;
	}
	temp->NEXT = current->NEXT;
	current->NEXT = temp;
}

//Function used to save linked list to text file
void saveList(nodeT* top)
{
	FILE* outp;
	nodeT* temp = top;

	outp = fopen("accounts.txt", "a ");

	if (outp == NULL)
	{
		printf("The backup file could not be saved\n");
		return;
	}

	while (temp != NULL)
	{
		fprintf(outp, "%d %s %s %s %.2lf %s %d\n",
			temp->accData.accNum, temp->accData.firstName, temp->accData.secondName,
			temp->accData.address, temp->accData.initBal, temp->accData.email,
			temp->accData.serviceRating);

		temp = temp->NEXT;
	}

	fclose(outp);
}

//Function used to load login records
void loadLogins(login logins[])
{
	FILE* inp;
	int numInputs;
	int i = 0;

	inp = fopen("login.txt", "r");

	if (inp == NULL)
	{
		printf("Cannot load previous data as the file could not be opened\n");
		return;
	}

	while (!feof(inp) && i < MAX_RECORDS)
	{
		numInputs = fscanf(inp, "%6s %6s", logins[i].username, logins[i].password);
		if (numInputs == 2)
		{
			i++;
		}
	}
	fclose(inp);
}

//Function used to validate password and username
int validateLogin(login logins[])
{
	char username[MAX_USERNAME_LENGTH];
	char password[MAX_PASSWORD_LENGTH];

	printf("Enter username: ");
	scanf("%6s", username);

	printf("Enter password: ");
	getPassword(password, MAX_PASSWORD_LENGTH - 1);
	printf("\n");

	for (int i = 0; i < MAX_RECORDS; i++)
	{
		if (strcmp(username, logins[i].username) == 0 && strcmp(password, logins[i].password) == 0)
		{
			return 1;
		}
	}
	return 0;
}

//Function used to hide key strokes
void getPassword(char* password, int maxLength)
{
	int i = 0;
	char ch;

	while (i < maxLength)
	{
		ch = _getch();

		if (ch == '\r')
		{
			break;
		}
		else if (ch == '\b')
		{
			if (i > 0)
			{
				printf("\b \b");
				i--;
			}
		}
		else if (ch >= 32 && ch <= 126)
		{
			printf("*");
			password[i] = ch;
			i++;
		}
	}

	password[i] = '\0';
}

//Function used to display accounts with a balance of less than 100
void displayBal(nodeT* top)
{
	nodeT* temp = top;
	int found = 0;

	const char* ratingNames[] = { "Excellent", "VeryGood", "Satisfactory", "Disappointing", "Bad" };

	while (temp != NULL)
	{
		if (temp->accData.initBal < 100)
		{
			printf("Account Number = %d\n", temp->accData.accNum);
			printf("First Name = %s\n", temp->accData.firstName);
			printf("Surname = %s\n", temp->accData.secondName);
			printf("Address = %[\n]\n", temp->accData.address);
			printf("Initial Balance = %.2lf\n", temp->accData.initBal);
			printf("Email = %s\n", temp->accData.email);
			printf("Service Rating = %s\n", ratingNames[temp->accData.serviceRating]);
			found = 1;
		}

		temp = temp->NEXT;
	}

	if (!found)
	{
		printf("There are no accounts with a balance lower than £100\n");
	}
}

//Function used to display account details based on an inputted name or account number
void displayAcc(nodeT* top)
{
	int accNum;
	char firstName[20], secondName[20];
	char fullName[40];
	nodeT* current = top;
	int found = 0;
	int choice;

	const char* ratingNames[] = { "Excellent", "VeryGood", "Satisfactory", "Disappointing", "Bad" };

	printf("Enter 1 to search by account number and Enter 2 to search by full name\n");
	scanf("%d", &choice);
	while (getchar() != '\n');

	if (choice == 1)
	{
		printf("Enter account number\n");
		scanf("%d", &accNum);
		
		while (current != NULL) 
		{
			if (current->accData.accNum == accNum) 
			{
				printf("Name: %s %s, Account Number: %d, Address: %s, Balance: %.2lf, Email: %s, Rating: %s\n",
					current->accData.firstName, current->accData.secondName, current->accData.accNum,
					current->accData.address, current->accData.initBal, current->accData.email,
					ratingNames[current->accData.serviceRating]);
				return;
			}
			current = current->NEXT;
		}
		printf("Account not found.\n");
	}
	else if (choice == 2)
	{
		printf("Enter first name\n");
		scanf("%s", firstName);

		printf("Enter last name\n");
		scanf("%s", secondName);

		sprintf(fullName, "%s %s", firstName, secondName);

		while (current != NULL)
		{
			char recordFullName[40];

			sprintf(recordFullName, "%s %s", current->accData.firstName, current->accData.secondName);

			if (strcmp(recordFullName, fullName) == 0)
			{
				printf("Name: %s %s, Account Number: %d, Address: %s, Balance: %.2lf, Email: %s, Rating: %s\n",
					current->accData.firstName, current->accData.secondName, current->accData.accNum,
					current->accData.address, current->accData.initBal, current->accData.email,
					ratingNames[current->accData.serviceRating]);
				found = 1;
				break;
			}

			current = current->NEXT;
		}

		if (!found)
		{
			printf("Account not found");
		}
	}

}

//Funtion used to add to account balance
void lodgeToAcc(nodeT* top)
{
	int accNum;
	double amount;
	nodeT* temp = top;
	int found = 0;

	printf("Enter account number: ");
	scanf("%d", &accNum);
	while (getchar() != '\n');

	while (temp != NULL)
	{
		if (temp->accData.accNum == accNum)
		{
			printf("Enter amount to lodge: ");
			scanf("%lf", &amount);
			while (getchar() != '\n');

			temp->accData.initBal += amount;

			printf("Amount lodged successfully. New balance: %.2lf\n", temp->accData.initBal);
			
			found = 1;
			break;
		}

		temp = temp->NEXT;
	}

	if (!found)
	{
		printf("Account number not found\n");
	}

}

//Function used to subtract from account balance
void withdrawFromAcc(nodeT* top)
{
	int accNum;
	double amount;
	nodeT* temp = top;
	int found = 0;

	printf("Enter account number\n");
	scanf("%d", &accNum);
	while (getchar() != '\n');

	while (temp != NULL)
	{
		if (temp->accData.accNum == accNum)
		{
			printf("Enter amount you want to withdraw\n");
			scanf("%lf", &amount);
			while (getchar() != '\n');

			if (amount > temp->accData.initBal)
			{
				printf("Insufficient funds\n");
			}
			else
			{
				temp->accData.initBal -= amount;
				printf("New Balance: %.2lf\n", temp->accData.initBal);
			}

			found = 1;
			break;
		}

		temp = temp->NEXT;
	}

	if (!found)
	{
		printf("Account number not found\n");
	}
}

//Function used to delete an account
void deleteAccount(nodeT** top)
{
	nodeT* temp = *top;
	nodeT* prevTemp = NULL;
	int searchNum = 0;

	printf("Enter account number you wish to delete\n");
	scanf("%d", &searchNum);

	if (search(temp, searchNum))
	{
		while (temp != NULL && temp->accData.accNum != searchNum)
		{
			prevTemp = temp;
			temp = temp->NEXT;
		}
		if (prevTemp == NULL)
		{
			*top = temp->NEXT;
		}
		else
		{
			prevTemp->NEXT = temp->NEXT;
		}

		free(temp);
		printf("Account has been deleted\n");
	}
	else
	{
		printf("Account not found\n");
	}
}

//Function used to print a report of the accounts
void printReport(nodeT* top)
{
	FILE* outp;
	nodeT* temp = top;

	const char* ratingNames[] = { "Excellent", "VeryGood", "Satisfactory", "Disappointing", "Bad" };

	outp = fopen("reports.txt", "w");

	if (outp == NULL)
	{
		printf("The backup file could not be saved\n");
	}

	else
	{
		while (temp != NULL)
		{
			fprintf(outp, "Account Number: %d\n", temp->accData.accNum);
			fprintf(outp, "First Name: %s\n", temp->accData.firstName);
			fprintf(outp, "Second Name: %s\n", temp->accData.secondName);
			fprintf(outp, "Address: %s\n", temp->accData.address);
			fprintf(outp, "Initial Balance: %.2lf\n", temp->accData.initBal);
			fprintf(outp, "Email: %s\n", temp->accData.email);
			fprintf(outp, "Service Rating: %s\n", ratingNames[temp->accData.serviceRating]);
			fprintf(outp, "------------------------------\n");

			temp = temp->NEXT;
		}

		fclose(outp);
		printf("Report generated successfully\n");
	}
}

//Function used to generate statistics based off of service ratings
void generateStats(nodeT* top) {
	int totalCount = 0;
	int countExcellent = 0;
	int countVeryGood = 0;
	int countSatisfactory = 0;
	int countDisappointing = 0;
	int countBad = 0;

	nodeT* temp = top;

	while (temp != NULL) {
		switch (temp->accData.serviceRating) {
		case EXCELLENT:
			countExcellent++;
			break;
		case VERY_GOOD:
			countVeryGood++;
			break;
		case SATISFACTORY:
			countSatisfactory++;
			break;
		case DISAPPOINTING:
			countDisappointing++;
			break;
		case BAD:
			countBad++;
			break;
		default:
			break;
		}
		totalCount++;
		temp = temp->NEXT;
	}

	double percentExcellent = (totalCount > 0) ? (100.0 * countExcellent / totalCount) : 0.0;
	double percentVeryGood = (totalCount > 0) ? (100.0 * countVeryGood / totalCount) : 0.0;
	double percentSatisfactory = (totalCount > 0) ? (100.0 * countSatisfactory / totalCount) : 0.0;
	double percentDisappointing = (totalCount > 0) ? (100.0 * countDisappointing / totalCount) : 0.0;
	double percentBad = (totalCount > 0) ? (100.0 * countBad / totalCount) : 0.0;

	printf("Statistics based on service ratings:\n");
	printf("a. Percentage of people who felt the service was Excellent: %.2f%%\n", percentExcellent);
	printf("b. Percentage of people who felt the service was Very Good: %.2f%%\n", percentVeryGood);
	printf("c. Percentage of people who felt the service was Satisfactory: %.2f%%\n", percentSatisfactory);
	printf("d. Percentage of people who felt the service was Disappointing: %.2f%%\n", percentDisappointing);
	printf("e. Percentage of people who felt the service was Bad: %.2f%%\n", percentBad);
}
