#define _CRT_SECURE_NO_DEPRECATE
#include"linkedlist.h"

//Function to load player data from file into the linked list
void loadFromFile(nodeT** top)
{
	FILE* inp;
	player playerData;
	int numInputs;
	nodeT* temp;

	inp = fopen("rugby.txt", "r");

	if (inp == NULL)
	{
		printf("Can not load previous data as the file could not be opened\n");
	}
	else
	{
		//Loop to read data until the end of file
		while (!feof(inp))
		{
			//Reading data from file into player data struct
			numInputs = fscanf(inp, "%d %s %s %d %lf %lf %s %s %[^.]. %[^.]. %[^.].", &playerData.IRFUvalue, playerData.firstName, playerData.secondName, &playerData.age, &playerData.height, &playerData.weight, playerData.club, playerData.email, playerData.position, &playerData.tackles, &playerData.metres);

			if (numInputs == EOF)
			{
				fclose(inp);
				return;
			}

			//Printing the loaded data
			printf("%d %s %s %d %.2lf %.2lf %s %s %s %s %s\n", playerData.IRFUvalue, playerData.firstName, playerData.secondName, playerData.age, playerData.height, playerData.weight, playerData.club, playerData.email, playerData.position, playerData.tackles, playerData.metres);
			if (numInputs == 11)
			{
				temp = (nodeT*)malloc(sizeof(nodeT));

				//Copying data into a new node
				temp->playerData.IRFUvalue = playerData.IRFUvalue;
				strcpy(temp->playerData.firstName, playerData.firstName);
				strcpy(temp->playerData.secondName, playerData.secondName);
				temp->playerData.age = playerData.age;
				temp->playerData.height = playerData.height;
				temp->playerData.weight = playerData.weight;
				strcpy(temp->playerData.club, playerData.club);
				strcpy(temp->playerData.email, playerData.email);
				strcpy(temp->playerData.position, playerData.position);
				strcpy(temp->playerData.tackles, playerData.tackles);
				strcpy(temp->playerData.metres ,playerData.metres);


				temp->NEXT = *top;
				*top = temp;
			}
		}

		fclose(inp);
	}
}

//Function to add a new player to linked list
void addPlayer(nodeT** top)
{
	nodeT* temp;
	nodeT* current;
	temp = (nodeT*)malloc(sizeof(nodeT));

	do {
		printf("Please enter your IRFU Number\n");
		scanf("%d", &temp->playerData.IRFUvalue);

		if (search(top, temp->playerData.IRFUvalue))
		{
			printf("IRFU number is in use, enter a new IRFU number");
		}

	} while (search(top, temp->playerData.IRFUvalue));

	printf("Please enter your first name\n");
	scanf("%s", temp->playerData.firstName);

	printf("Please enter your surnmame\n");
	scanf("%s", temp->playerData.secondName);

	printf("Please enter your age\n");
	scanf("%d", &temp->playerData.age);

	printf("Please enter your height\n");
	scanf("%lf", &temp->playerData.height);

	printf("Please enter your weight\n");
	scanf("%lf", &temp->playerData.weight);

	printf("Please enter your club\n");
	scanf("%s", temp->playerData.club);
	
	checkEmail(temp);

	checkPosition(temp);

	checkTackles(temp);

	checkMetres(temp);

	if (*top == NULL || (*top)->playerData.IRFUvalue > temp->playerData.IRFUvalue)
	{
		temp->NEXT = *top;
		*top = temp;
		return;
	}
	current = *top;

	while (current->NEXT != NULL && current->NEXT->playerData.IRFUvalue < temp->playerData.IRFUvalue)
	{
		current = current->NEXT;
	}
	temp->NEXT = current->NEXT;
	current->NEXT = temp;
}

//Function to save linked list data to a file
void saveList(nodeT* top)
{
	FILE* outp;
	nodeT* temp = top;

	outp = fopen("rugby.txt", "w");

	if (outp == NULL)
	{
		printf("The backup file could not be saved\n");
	}

	else
	{
		while (temp != NULL)
		{
			fprintf(outp, "%d %s %s %d %.2lf %.2lf %s %s %s. %s. %s.\n", temp->playerData.IRFUvalue, temp->playerData.firstName, temp->playerData.secondName, temp->playerData.age, temp->playerData.height, temp->playerData.weight, temp->playerData.club, temp->playerData.email, temp->playerData.position, temp->playerData.tackles, temp->playerData.metres);
			temp = temp->NEXT;
		}

		fclose(outp);
	}
}

//Not currently working throws exception
//Function to delete player from the linked list
void deletePlayer(nodeT** top)
{
	nodeT* temp = *top;
	nodeT* prevTemp = NULL;
	int searchNum = 0;

	printf("Please enter the IRFU number of the player you want to delete\n");
	scanf("%d", &searchNum);

	if (search(&temp, searchNum))
	{
		while (temp != NULL && temp->playerData.IRFUvalue != searchNum)
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
		printf("Player has been deleted\n");
	}
	else 
	{
		printf("Player not found.\n");
	}
}

//Function to display all players in the linked list
void display(nodeT* top)
{
	nodeT* temp = top;

	while (temp != NULL)
	{
		printf("The IRFU value at this node is %d\n", temp->playerData.IRFUvalue);
		printf("The surname at this node is %s\n", temp->playerData.secondName);
		printf("The age at this node is %d\n", temp->playerData.age);
		printf("The height at this node is %.2lf\n", temp->playerData.height);
		printf("The weight at this node is %.2lf\n", temp->playerData.weight);
		printf("The club name at this node is %s\n", temp->playerData.club);
		printf("The email at this node is %s\n", temp->playerData.email);
		printf("The position at this node is %s\n", temp->playerData.position);
		printf("The tackles at this node are %s\n", temp->playerData.tackles);
		printf("The metres at this node is %s\n", temp->playerData.metres);
		temp = temp->NEXT;
	}
}

//Function to count the number of nodes in the linked list
int length(nodeT* top)
{
	nodeT* temp = top;
	int count = 0;

	while (temp != NULL)
	{
		/*printf("The value at this node is %d\n", temp->playerData.IRFUvalue);*/
		count++;
		temp = temp->NEXT;
	}

	return count;
}

//Function to search for a player in the linked list
int search(nodeT** top, int searchNum)
{
	nodeT* temp = *top;
	int found = 0;

	while (temp != NULL)
	{
		if (temp->playerData.IRFUvalue == searchNum)
		{
			found = 1;
			break;
		}
		temp = temp->NEXT;
	}

	return found;
}

//Function to check and input the email for a player
void checkEmail(nodeT* temp) {
	int found = 0;
	do {
		printf("Please enter your email\n");
		scanf("%s", temp->playerData.email);
		while (getchar() != '\n');

		if (strchr(temp->playerData.email, '@') != NULL && strstr(temp->playerData.email, ".com") != NULL)
		{
			found = 1;
		}

		else
		{
			printf("Invalid email, @ and .com not present");
		}
	} while (!found);
}

//Function to check and input the position for a player
void checkPosition(nodeT* temp)
{
	int found = 0;
	do {
		printf("Please enter your position from the following options:\n");
		printf("Prop\n");
		printf("Hooker\n");
		printf("Second Row\n");
		printf("Half Back\n");
		printf("Centres\n");
		printf("Wingers / Full Back\n");
		scanf("%[^\n]s", temp->playerData.position);
		while (getchar() != '\n');
		

		if (strcmp(temp->playerData.position, "Prop") == 0 ||
			strcmp(temp->playerData.position, "Hooker") == 0 ||
			strcmp(temp->playerData.position, "Second Row") == 0 ||
			strcmp(temp->playerData.position, "Half Back") == 0 ||
			strcmp(temp->playerData.position, "Centres") == 0 ||
			strcmp(temp->playerData.position, "Wingers / Full Back") == 0)
		{
			found = 1;
		}
		else
		{
			printf("Invalid position. Please try again.\n");
		}

	} while (!found);
}

//Function to check and input the tackles for a player
void checkTackles(nodeT* temp)
{
	int found = 0;
	do {
		printf("Please enter the number of tackles missed from the following options:\n");
		printf("Never\n");
		printf("Less than three times per match\n");
		printf("Less than five times per match\n");
		printf("More than five times per match\n");
		scanf("%[^\n]s", temp->playerData.tackles);
		while (getchar() != '\n');
		

		if (strcmp(temp->playerData.tackles, "Never") == 0 ||
			strcmp(temp->playerData.tackles, "Less than three times per match") == 0 ||
			strcmp(temp->playerData.tackles, "Less than five times per match") == 0 ||
			strcmp(temp->playerData.tackles, "More than five times per match") == 0)
		{
			found = 1;
		}

		else
		{
			printf("Invalid Input. Please try again.\n");
		}

	} while (!found);
}

//Function to check and input the metres for a player
void checkMetres(nodeT* temp)
{
	int found = 0;
	do {
		printf("Please enter the number of metres the player makes in the game from the following options:\n");
		printf("None\n");
		printf("Less than 10\n");
		printf("Less than 20\n");
		printf("More than 20\n");
		scanf("%[^\n]s", temp->playerData.metres);
		while (getchar() != '\n');
		

		if (strcmp(temp->playerData.metres, "None") == 0 ||
			strcmp(temp->playerData.metres, "Less than 10") == 0 ||
			strcmp(temp->playerData.metres, "Less than 20") == 0 ||
			strcmp(temp->playerData.metres, "More than 20") == 0)
		{
			found = 1;
		}

		else
		{
			printf("Invalid Input. Please try again.\n");
		}

	} while (!found);
}

//Function to display the details of a specific player
void displayPlayer(nodeT* top)
{
	nodeT* temp = top;
	int searchNum = 0;

	printf("Input IRFU Value for player you are looking\n");
	scanf("%d", &searchNum);

	while(temp != NULL)
	{


		if (search(&temp, searchNum))
		{
			printf("The IRFU value at this node is %d\n", temp->playerData.IRFUvalue);
			printf("The surname at this node is %s\n", temp->playerData.secondName);
			printf("The age at this node is %d\n", temp->playerData.age);
			printf("The height at this node is %.2lf\n", temp->playerData.height);
			printf("The weight at this node is %.2lf\n", temp->playerData.weight);
			printf("The club name at this node is %s\n", temp->playerData.club);
			printf("The email at this node is %s\n", temp->playerData.email);
			printf("The position at this node is %s\n", temp->playerData.position);
			printf("The tackles at this node are %s\n", temp->playerData.tackles);
			printf("The metres at this node is %s\n", temp->playerData.metres);
			return;
		}
		temp = temp->NEXT;
	}
	printf("Player was not found");
}

//Function to update the details of a specific player
void updatePlayer(nodeT* top)
{
	nodeT* temp = top;
	int searchNum = 0;
	
	printf("Please enter the IRFU number of the player you are looking to update\n");
	scanf("%d", &searchNum);
	while (getchar() != '\n');

	if (search(&temp, searchNum))
	{
		printf("Please enter your surnmame\n");
		scanf("%s", temp->playerData.secondName);

		printf("Please enter your age\n");
		scanf("%d", &temp->playerData.age);

		printf("Please enter your height\n");
		scanf("%lf", &temp->playerData.height);

		printf("Please enter your weight\n");
		scanf("%lf", &temp->playerData.weight);

		printf("Please enter your club\n");
		scanf("%s", temp->playerData.club);

		checkEmail(temp);

		checkPosition(temp);

		checkTackles(temp);

		checkMetres(temp);
	}

	else
	{
		printf("Player not found");
	}
}

//Function to count the player based off certain criteria and calculate percentages
statistics countPlayerByValue(nodeT* top)
{
	nodeT* temp = top;
	int totalNumber = length(top);
	int count = 0;
	char check = 0;
	double calculation = 0;
	statistics statistics;

	printf("Please enter a letter ranging from a - h\na. percentage of players who miss no tackles\nb. percentage of players who miss less than 3 tackles per match\nc. percentage of players who miss less than 5 tackles per match\nd. percentage of players who miss more than 5 tackles per match\ne. percentage of players who make no metres in a game\nf. percentage of players who make less than 10 metres in a game\ng. percentage of players who make less than 20 metres in a game\nh. percentage of players who make more than 20 metres in a game\n");
	scanf(" %c", &check);

	while (temp != NULL)
	{
		if (check == 'a' && strcmp(temp->playerData.tackles, "Never") == 0)
		{
			count++;
		}

		else if (check == 'b' && strcmp(temp->playerData.tackles, "Less than three times per match") == 0)
		{
			count++;
		}

		else if (check == 'c' && strcmp(temp->playerData.tackles, "Less than five times per match") == 0)
		{
			count++;
		}

		else if (check == 'd' && strcmp(temp->playerData.tackles, "More than five times per match") == 0)
		{
			count++;
		}

		else if (check == 'e' && strcmp(temp->playerData.metres, "None") == 0)
		{
			count++;
		}

		else if (check == 'f' && strcmp(temp->playerData.metres, "Less than 10") == 0)
		{
			count++;
		}

		else if (check == 'g' && strcmp(temp->playerData.metres, "Less than 20") == 0)
		{
			count++;
		}

		else if (check == 'h' && strcmp(temp->playerData.metres, "More than 20") == 0)
		{
			count++;
		}

		temp = temp->NEXT;
	}
	
	if (totalNumber > 0)
	{
		calculation = (count * 100.0) / totalNumber;

		switch (check) 
		{
		case 'a': statistics.statA = calculation; break;
		case 'b': statistics.statB = calculation; break;
		case 'c': statistics.statC = calculation; break;
		case 'd': statistics.statD = calculation; break;
		case 'e': statistics.statE = calculation; break;
		case 'f': statistics.statF = calculation; break;
		case 'g': statistics.statG = calculation; break;
		case 'h': statistics.statH = calculation; break;
		}
		printf("%.2lf\n", calculation);
	}

	else
	{
		printf("No player was found");
	}
	return statistics;
}

//Function to print a report with the player details and statistics
void printReport(nodeT* top, statistics stats)
{
	FILE* outp;
	nodeT* temp = top;

	outp = fopen("report.txt", "w");

	if (outp == NULL)
	{
		printf("The backup file could not be saved\n");
	}

	else
	{
		while (temp != NULL)
		{
			fprintf(outp, "%d %s %s %d %.2lf %.2lf %s %s %s. %s. %s.\n", temp->playerData.IRFUvalue, temp->playerData.firstName, temp->playerData.secondName, temp->playerData.age, temp->playerData.height, temp->playerData.weight, temp->playerData.club, temp->playerData.email, temp->playerData.position, temp->playerData.tackles, temp->playerData.metres);
			
			temp = temp->NEXT;
		}

		fprintf(outp, "Percentage of players who miss no tackles\n", stats.statA);
		fprintf(outp, "%.2lf\n", stats.statA);

		fprintf(outp, "Percentage of players who miss less than 3 tackles per match\n", stats.statB);
		fprintf(outp, "%.2lf\n", stats.statB);

		fprintf(outp, "Percentage of players who miss less than 5 tackles per match\n", stats.statC);
		fprintf(outp, "%.2lf\n", stats.statC);

		fprintf(outp, "Percentage of players who miss more than 5 tackles per match\n", stats.statD);
		fprintf(outp, "%.2lf\n", stats.statD);

		fprintf(outp, "Percentage of players who make no metres in a game\n", stats.statE);
		fprintf(outp, "%.2lf\n", stats.statE);

		fprintf(outp, "Percentage of players who make less than 10 metres in a game\n", stats.statF);
		fprintf(outp, "%.2lf\n", stats.statF);

		fprintf(outp, "Percentage of players who make less than 20 metres in a game\n", stats.statG);
		fprintf(outp, "%.2lf\n", stats.statG);

		fprintf(outp, "Percentage of players who make more than 20 metres in a game\n", stats.statH);
		fprintf(outp, "%.2lf\n", stats.statH);


		fclose(outp);
	}
}

//Function to load login data from a file
void loadLogins(login logins[])
{
	FILE* inp;
	int numInputs;
	int i = 0;

	inp = fopen("login.txt", "r");

	if (inp == NULL)
	{
		printf("Can not load previous data as the file could not be opened\n");
	}

	while (!feof(inp) && i < MAX_RECORDS)
	{
		numInputs = fscanf(inp, "%s %s", logins[i].username, logins[i].password);
		if (numInputs == 2)
		{
			i++;
		}
	}
	fclose(inp);
}

//Function to validate login credentials
int validateLogin(login logins[])
{
	char username[MAX_USERNAME_LENGTH];
	char password[MAX_PASSWORD_LENGTH];

	printf("Enter username: ");
	scanf("%s", username);

	printf("Enter password: ");
	scanf("%s", password);

	for (int i = 0; i < MAX_RECORDS; i++)
	{
		if (strcmp(username, logins[i].username) == 0 && strcmp(password, logins[i].password) == 0)
		{
			return 1;
		}
	}
	return 0;
}