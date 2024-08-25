#define _CRT_SECURE_NO_DEPRECATE
#define MAX_USERNAME_LENGTH 7
#define MAX_PASSWORD_LENGTH 7
#define MAX_RECORDS 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//Enumeration for service ratings with predefined values
typedef enum {
	UNKNOWN = 0,
	EXCELLENT = 1, 
	VERY_GOOD = 2,
	SATISFACTORY = 3,
	DISAPPOINTING = 4,
	BAD = 5
}Rating;

//Structure used to store account information
typedef struct {
	int accNum;
	char firstName[20];
	char secondName[20];
	char address[60];
	double initBal;
	char email[40];
	Rating serviceRating;
}account;

//Structure used for nodes
typedef struct node {
	account accData;
	struct node* NEXT;
}nodeT;

//Structure used to store login information
typedef struct
{
	char username[MAX_USERNAME_LENGTH];
	char password[MAX_PASSWORD_LENGTH];
}login;

//Functions used in program
int search(nodeT* top, int searchNum);
void checkEmail(nodeT* top);
void addAccount(nodeT** top);
void saveList(nodeT* top);
void loadFromFile(nodeT** top);
void loadLogins(login logins[]);
int validateLogin(login logins[]);
void getPassword(char* password, int maxLength);
void displayBal(nodeT* top);
void lodgeToAcc(nodeT* top);
void deleteAccount(nodeT** top);
void printReport(nodeT* top);
void withdrawFromAcc(nodeT* top);
void displayAcc(nodeT* top);
void generateStats(nodeT* top);

