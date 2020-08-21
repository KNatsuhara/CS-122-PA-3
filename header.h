#ifndef HEADER_H
#define HEADER_H
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct duration
{
	int hours;
	int minutes;
} Duration;

typedef struct record
{
	char title[100];
	char director[100];
	char description[200];
	char genre[100];
	int year;
	int plays;
	int rating;
	Duration duration;
} Record;

typedef struct node
{
	Record data;
	struct node* pNext;
	struct node* pPrev;
} Node;


Node* head; //global variable

int menu(); //Prints out menu and returns an integer
void runOption(int option, int* pEXIT); //Runs the following functions for linked list
int isEmpty(); //Checks if the linked list is empty
Record getData(FILE* infile); //Gets data from moviePlayList.csv
void insertFront(Record data); //Insert a node to the front of the list
void printList(); //Print all elements in the list
void load(); //Reads all lines from .csv and inserts them as nodes to the front of the list
void store(); //Goes through linked list and prints them to moviePlaylist.csv
void edit(); //Search through the linked list and asks if the user wants to edit that movie and choose which field to modify
void printRecord(Node* pList); //Prints a single record based on the current node inputed in the list
void display(); //Displays a record depending on what the user inputs as a director or year
void rate(); //Asks for a title from the user and then asks if the user wants to change the rating of that movie
void play(); //Plays all movie until the end of the list
void delay(int numSec); //Creates a delay which will run for how many seconds the function is set to
void insert(); //Prompts the user to input a new record movie and inserts the record to the front of the list
void delete(); //Prompts the user for a movie title and then removes the matching record from the list
void shuffle(); //Plays the movie list in a randomly selected order
void getRandomNums(int* random); //Returns random distinct numbers in an array
int lengthOfList(); //Returns the length of the linked list
int checkArr(int* result, int check, int size); //Checks to see if an integer is already repeated in the array
void sort(); //Sorts list by director, film title, rating, and number of times played
int printSortMenu(); //Gets option from user on how they want to sort the list
void sortDirector(); //Sorts the list by director A-Z
void sortFilmTitle(); //Sorts the list by film title A-Z
void sortRating(); //Sorts the list by rating 1-5
void sortPlays(); //Sorts list by number of plays (most played to least played)
int optionTest(); //Returns an integer between 1 and 2
void insertTest(); //Inserts Bohemian Rhapsody into the linked list
void deleteTest(); //Deletes Bohemian Rhapsody from the linked list
void shuffleTest(); //Shows the random shuffle list and plays the movies accordingly
#endif