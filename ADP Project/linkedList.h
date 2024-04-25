#define _CRT_SECURE_NO_DEPRECATE //Define to supress warnings for certain functions in Visual Studio
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
#define MAX_RECORDS 3
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Structure the hold player data
typedef struct {
	int IRFUvalue;
	char firstName[20];
	char secondName[20];
	int age;
	double height;
	double weight;
	char club[40];
	char email[40];
	char position[20];
	int tackles[30];
	char metres[20];
}player;

//Structure for a node in the linked list
typedef struct node
{
	player playerData;
    struct node* NEXT;
}nodeT;

//Structure to hold statistics
typedef struct 
{
	double statA;
	double statB;
	double statC;
	double statD;
	double statE;
	double statF;
	double statG;
	double statH;
}statistics;

//Structure to hold login credentials
typedef struct
{
	char username[20];
	char password[20];
}login;

void addPlayer(nodeT** top);
void loadFromFile(nodeT** top);
void saveList(nodeT* top);
void deletePlayer(nodeT* top);
void display(nodeT* top);
void displayPlayer(nodeT* top);
int searchIRFU(nodeT* top);
int promptSearch(nodeT* top);
void checkEmail(nodeT* temp);
void checkPosition(nodeT* temp);
void checkTackles(nodeT* temp);
void checkMetres(nodeT* temp);
void updatePlayer(nodeT* top);
statistics countPlayerByValue(nodeT* top);
void printReport(nodeT* top, statistics stats);
void loadLogins(login logins[]);