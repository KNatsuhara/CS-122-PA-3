#include "header.h"

/*
Function: menu()
Date Created: 2/24/2020
Description: Prints the menu that the user can choose to select from and returns
an integer that is between 1 and 12.
Input Parameters: void
Returns: Integer
*/
int menu()
{
	int option = 0;
	do
	{
		printf("What action would you like to perform?\n");
		printf("1. Load\n");
		printf("2. Store\n");
		printf("3. Display\n");
		printf("4. Insert\n");
		printf("5. Delete\n");
		printf("6. Edit\n");
		printf("7. Sort\n");
		printf("8. Rate\n");
		printf("9. Play\n");
		printf("10. Shuffle\n");
		printf("11. Print List\n");
		printf("12. Exit\n");
		printf("Select an option: ");
		scanf("%d", &option);
	} while (option < 1 || option > 12);
	return option;
}

/*
Function: runOption(int option, int* pEXIT)
Date Created: 2/24/2020
Description: This function takes in an integer inputted by the user and then
plays the case statement in the switch conditional and then plays the function accordingly
Input Parameters: void
Returns: void
*/
void runOption(int option, int* pEXIT)
{
	int test = 0;
	switch (option)
	{
	case 1: //Loads all records for MoviePlayList.csv
		load();
		break;
	case 2: //Stores all records in MoviePlayList.csv
		store();
		break;
	case 3: //Displays a record given the director or year of the film
		display();
		break;
	case 4: //Insert AND Insert test
		printf("1. Insert\n2. Test Insert\n");
		test = optionTest();
		switch (test)
		{
		case 1:
			insert();
			break;
		case 2:
			insertTest();
			break;
		}
		break;
	case 5: //Delete AND Delete test
		printf("1. Delete\n2. Test Delete\n");
		test = optionTest();
		switch (test)
		{
		case 1:
			delete();
			break;
		case 2:
			deleteTest();
			break;
		}
		break;
	case 6: //Edits a film based on the director inputted by the user
		edit();
		break;
	case 7: //Sort
		sort();
		break;
	case 8: //Rates a film based on the title of the film inputted by the user.
		rate();
		break;
	case 9: //Plays all films from start to finish in the list given the film title to start from
		play();
		break;
	case 10: //Shuffle AND shuffle test
		printf("1. Shuffle\n2. Shuffle Test\n");
		test = optionTest();
		switch (test)
		{
		case 1:
			shuffle();
			break;
		case 2:
			shuffleTest();
			break;
		}
		break;
	case 11:
		printList();
		break;
	case 12: //Exit: Loads all files into the moviePlayList.csv and exits out of program
		store();
		*pEXIT = 1;
		break;
	}
}

/*
Function: isEmpty()
Date Created: 2/24/2020
Description: Checks if the linked list is empty and returns 1 if the list is empty
Input Parameters: int option, int* pEXIT
Returns: Integer
*/
int isEmpty()
{
	Node* current = head; //Set current to head pointer
	int status = 0;
	if (current == NULL) //Checks to see if the list is empty
		status = 1;
	return status;
}

/*
Function: getData(FILE* infile)
Date Created: 2/24/2020
Description: The file reads a line in the moviePlayList.csv and then 
adds to Record data.
Input Parameters: FILE* infile
Returns: Record struct
*/
Record getData(FILE* infile) //Gets data from moviePlayList.csv
{
	char delim[2] = ",";
	char line[300];
	char trash[300];
	char* token;
	Record data; //Initializes a new struct Record called data

	fgets(line, 300, infile); //Reads the first line in the .csv file

	token = strtok(line, delim); //1. Reads the title of the film and adds it to data
	strcpy(data.title, token);

	token = strtok(NULL, delim); //2. Reads the directors name and adds it to data
	strcpy(data.director, token);

	token = strtok(NULL, delim); //3. Reads the description and adds it to data
	strcpy(data.description, token);

	token = strtok(NULL, delim); //4. Reads the genre of the film and adds it to data
	strcpy(data.genre, token);

	token = strtok(NULL, ":");  //5. Reads the hours of the film and adds it to data as an integer
	data.duration.hours = atoi(token);

	token = strtok(NULL, delim); //6. Reads the minutes  of the film and adds it to data as an integer
	data.duration.minutes = atoi(token);

	token = strtok(NULL, delim); //7. Reads the year the film was released and adds it to data
	data.year = atoi(token);

	token = strtok(NULL, delim); //8. Reads the the number of plays the film has and adds it to data
	data.plays = atoi(token);

	token = strtok(NULL, delim); //9. Reads the the rating of the film has and adds it to data
	data.rating = atoi(token);

	return data;
}

/*
Function: insertFront(Record data)
Date Created: 2/24/2020
Description: This function takes in a Record struct and then allocates memory
for the new Record into a Node and then inserts the node to the front of the list
Input Parameters: Record data
Returns: void
*/
void insertFront(Record data) //Insert a node to the front of the list
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	//Node* temp = headPtr;
	Node* temp = head;
	if (head == NULL)
	{
		newNode->data = data;
		newNode->pNext = head;
		newNode->pPrev = NULL;
		head = newNode;
	}
	else
	{
		newNode->data = data;
		newNode->pNext = head;
		newNode->pPrev = NULL;
		temp->pPrev = newNode;
		head = newNode;
	}
}

/*
Function: printList()
Date Created: 2/24/2020
Description: Prints all records in the doubly linked list
Input Parameters: void
Returns: void
*/
void printList() //Print all elements in the list
{
	Node* temp = head;
	while (temp != NULL)
	{
		printf("\n");
		printf("Film Title: %s\n", temp->data.title);
		printf("Director: %s\n", temp->data.director);
		printf("Description: %s\n", temp->data.description);
		printf("Genre: %s\n", temp->data.genre);
		printf("Duration: %d:", temp->data.duration.hours);
		if (temp->data.duration.minutes < 10)
		{
			printf("0");
		}
		printf("%d\n", temp->data.duration.minutes);
		printf("Year Released: %d\n", temp->data.year);
		printf("Number of times Played: %d\n", temp->data.plays);
		printf("Rating: %d\n", temp->data.rating);
		printf("\n");
		temp = temp->pNext;
	}
}

/*
Function: load()
Date Created: 2/24/2020
Description: This function opens the moviePlayList.csv file into read mode
and then reads all the lines of the moviePlayList.csv and inputs them into Records
and then into nodes to then be inserted to the front of the list.
Input Parameters: void
Returns: void
*/
void load()
{
	FILE* infile = fopen("moviePlayList.csv", "r"); //Opens file

	if (infile == NULL) //Checks if file was opened
	{
		printf("File did not open\n");
		return;
	}
	
	char trash[300];
	fgets(trash, 300, infile); //gets rid of the first line in the file
	Record temp;

	while (!feof(infile)) //Runs until it has read all the lines in the .csv file
	{
		temp = getData(infile); //Adds data to record struct temp
		insertFront(temp); //Allocates mem for struct record into a node and inserts it to the front of the list
	}
	printf("Successfully loaded all films\n");
	
	fclose(infile); //Closes file
}

/*
Function: store()
Date Created: 2/24/2020
Description: This function opens the moviePlayList.csv file into write mode
and then prints all the records from the linked list into the file
Input Parameters: void
Returns: void
*/
void store()
{
	FILE* outfile = fopen("moviePlayList.csv", "w"); //Opens moviePlayList.csv
	if (outfile == NULL)
	{
		printf("The outfile did not open\n");
	}

	Node* current = head; //Creates node pointer to head pointer

	if (isEmpty(current))
	{
		printf("There is no list, the list is empty");
	}
	else
	{
		fprintf(outfile, "Film Title, Director, Description, Genre, Running Time, Year, Times Played, Rating\n"); //Prints starting line for outfile
		while (current != NULL)
		{
			if (current->data.year != 0) //Checks to make sure the node is does not have false data and only prints valid data
			{
				fprintf(outfile, "%s,", current->data.title);
				fprintf(outfile, "%s,", current->data.director);
				fprintf(outfile, "%s,", current->data.description);
				fprintf(outfile, "%s,", current->data.genre);
				fprintf(outfile, "%d:", current->data.duration.hours);
				if (current->data.duration.minutes < 10) //Formats how to print hours and minutes (duration of movie)
				{
					fprintf(outfile, "0");
				}
				fprintf(outfile, "%d,", current->data.duration.minutes);
				fprintf(outfile, "%d,", current->data.year);
				fprintf(outfile, "%d,", current->data.plays);
				fprintf(outfile, "%d", current->data.rating);
			}
			if (current->pNext != NULL)
			{
				fprintf(outfile, "\n");
			}
			current = current->pNext;
		}
		printf("Store was successful!\n");
	}
	fclose(outfile); //Close moviePlayList.csv
}

/*
Function: edit()
Date Created: 2/24/2020
Description: Prompts the user to input the name of a director of a movie they 
would like to edit. This allows them to edit any element of the record that the
user desires. Within a certain limit for the year, rating and number of plays
Input Parameters: void
Returns: void
*/
void edit()
{
	char delim[2] = "\n";
	char* token;
	char sDirector[50];
	char temp[300];
	int tempNum = 0;
	int option = 0, option2 = 0;
	Node* current = head;

	printf("What is the name of the director you want to search up?: ");
	getchar();
	fgets(sDirector, sizeof(sDirector), stdin);
	token = strtok(sDirector, delim);
	strcpy(sDirector, token);

	while (current != NULL)
	{
		if (strcmp(sDirector, current->data.director) == 0) //compares the director and runs if statement when the director inputted by the user is the same as the node's
		{
			printRecord(current); //Prints the record that matches the directors name with the user's desired director's name
			printf("Is this the film you want to edit? (1 for Yes and 2 for No): ");
			scanf("%d", &option);
			if (option == 1)
			{
				printf("1. Film Title\n2. Director\n3. Description\n4. Genre\n5. Hours\n6. Minutes\n7. Year\n8. Times Played\n9. Rating\n");
				do
				{
					printf("What field do you want to edit?: ");
					scanf("%d", &option2);
				} while (option2 > 9 || option < 1);

				switch (option2)
				{
				case 1: //Film Title
					printf("Enter the new Film Title: ");
					getchar();
					fgets(temp, sizeof(temp), stdin);
					token = strtok(temp, delim);
					strcpy(current->data.title, token);
					printf("This is the new Film Title: %s\n", current->data.title);
					break;
				case 2: //Director
					printf("Enter the new Director: ");
					getchar();
					fgets(temp, sizeof(temp), stdin);
					token = strtok(temp, delim);
					strcpy(current->data.director, token);
					printf("This is the new Director: %s\n", current->data.director);
					break;
				case 3: //Description
					printf("Enter the new Description: ");
					getchar();
					fgets(temp, sizeof(temp), stdin);
					token = strtok(temp, delim);
					strcpy(current->data.description, token);
					printf("This is the new Description: %s\n", current->data.description);
					break;
				case 4: //Genre
					printf("Enter the new Genre: ");
					getchar();
					fgets(temp, sizeof(temp), stdin);
					token = strtok(temp, delim);
					strcpy(current->data.genre, token);
					printf("This is the new Genre: %s\n", current->data.genre);
					break;
				case 5: //Hours
					printf("Enter the new amount of hours in the film: ");
					scanf("%d", &tempNum);
					current->data.duration.hours = tempNum;
					printf("This is the new amount of hours in the film: %d\n", current->data.duration.hours);
					break;
				case 6: //Minutes
					printf("Enter the new amount of minutes in the film: ");
					do
					{
						scanf("%d", &tempNum);
					} while (tempNum < 0 || tempNum > 60);
					current->data.duration.minutes = tempNum;
					printf("This is the new amount of minutes in the film: %d\n", current->data.duration.minutes);
					break;
				case 7: //Year
					printf("Enter the new year that the film was released: ");
					scanf("%d", &tempNum);
					current->data.year = tempNum;
					printf("This is the new Year the film was released: %d\n", current->data.year);
					break;
				case 8: //Times Played
					printf("Enter the new amount of times this film has been played: ");
					do
					{
						scanf("%d", &tempNum);
					} while (tempNum < 0);
					current->data.plays = tempNum;
					printf("This is the new amount of times this film has been played: %d\n", current->data.plays);
					break;
				case 9: //Rating
					do
					{
						printf("Enter the new rating (1-5) for this film: ");
						scanf("%d", &tempNum);
					} while (tempNum > 5 || tempNum < 1);

					current->data.rating = tempNum;
					printf("This is the new the new rating (1-5) for this film: %d\n", current->data.rating);
					break;
				}
			}
		}
		current = current->pNext;
	}
}

/*
Function: printRecord()
Date Created: 2/24/2020
Description: Prints a single record where the Node* pList is pointing towards
Input Parameters: Node *pList
Returns: void
*/
void printRecord(Node *pList)
{
	printf("\n\n");
	printf("Film Title: %s\n", pList->data.title);
	printf("Director: %s\n", pList->data.director);
	printf("Description: %s\n", pList->data.description);
	printf("Genre: %s\n", pList->data.genre);
	printf("Duration: %d:", pList->data.duration.hours);
	if (pList->data.duration.minutes < 10)
	{
		printf("0");
	}
	printf("%d\n", pList->data.duration.minutes);
	printf("Year Released: %d\n", pList->data.year);
	printf("Number of times Played: %d\n", pList->data.plays);
	printf("Rating: %d\n", pList->data.rating);
	printf("\n\n");
}

/*
Function: display()
Date Created: 2/24/2020
Description: Prompts the user to look up a movie based on the year it was released
or by the name of the director. The function will then search for that movie and then show
the number of movies that matches with the user's search.
Input Parameters: void
Returns: void
*/
void display()
{
	char delim[2] = "\n";
	char* token;
	char sDirector[50];
	char line[50];
	char tempDirector[50];
	int option = 0, sYear = 0;
	Node* current = head;

	do
	{
		printf("Do you want to search for the movie based on the Director = 1 or Year = 2?: ");
		scanf("%d", &option);
	} while (option < 1 || option > 2);

	switch (option)
	{
	case 1:
		printf("What is the name of the director you want to search up?: ");
		getchar();
		fgets(sDirector, sizeof(sDirector), stdin);
		token = strtok(sDirector, delim);
		strcpy(sDirector, token);

		while (current != NULL)
		{
			//compares the director and runs if statement when the director inputted by the user is the same as the node's
			if (strcmp(sDirector, current->data.director) == 0)
			{
				printRecord(current);
			}
			current = current->pNext;
		}
		break;
	case 2:
		printf("What is the year you want to search up?: ");
		scanf("%d", &sYear);
		while (current != NULL)
		{
			//compares the year and runs if statement when the year inputted by the user is the same as the node's
			if (current->data.year == sYear)
			{
				printRecord(current);
			}
			current = current->pNext;
		}
		break;
	}
}

/*
Function: rate()
Date Created: 2/24/2020
Description: Prompts the user to input the film title that they want to search up and
then asks them to input an integer between 1-5 they want to give the movie.
Input Parameters: void
Returns: void
*/
void rate()
{
	char delim[2] = "\n";
	char* token;
	char sFilmTitle[50];
	int tempNum = 0;
	int option = 0;
	Node* current = head;

	printf("What is the Title of the Film you want to search up?: ");
	getchar();
	fgets(sFilmTitle, sizeof(sFilmTitle), stdin);
	token = strtok(sFilmTitle, delim);
	strcpy(sFilmTitle, token);

	while (current != NULL)
	{
		//compares the title and runs if statement when the title inputted by the user is the same as the node's
		if (strcmp(sFilmTitle, current->data.title) == 0)
		{
			printRecord(current);
			printf("Is this the film you want to rate? (1 for Yes and 2 for No): ");
			scanf("%d", &option);
			if (option == 1)
			{
				do
				{
					printf("What rating (1-5) do you want to give %s?:", current->data.title);
					scanf("%d", &tempNum);
				} while (tempNum > 5 || tempNum < 1);
				current->data.rating = tempNum;
				printf("You have changed %s to a rating of %d!\n", current->data.title, current->data.rating);
			}
		}
		current = current->pNext;
	}
}

/*
Function: play()
Date Created: 2/24/2020
Description: Prompts the user to input a film title that they want to start to watch
and then proceeds to play the rest of the list starting from the one they searched up
Input Parameters: void
Returns: void
*/
void play()
{
	Node* current = head;
	char filmTitle[50];
	int sPlaying = 0;
	char delim[2] = "\n";
	char* token;
	int played = 0;

	printf("Enter a film title to start with: "); //Gets film  choice
	getchar();
	fgets(filmTitle, 50, stdin);
	token = strtok(filmTitle, delim);
	strcpy(filmTitle, token);

	while (current != NULL) //Searches for the film
	{
		if (played == 1)
		{
			printf("Playing %s...\n", current->data.title);
			delay(3);
			current->data.plays += 1;
			printf("The film has finished playing!\n");
			
		}
		if (strcmp(filmTitle, current->data.title) == 0 && played != 1)
		{
			played = 1;
			printf("Playing %s...\n", current->data.title);
			delay(3);
			current->data.plays += 1;
			printf("The film has finished playing!\n");
		}
		current = current->pNext;
	}
	printf("All the films have finised playing!\n");
}

/*
Function: delay()
Date Created: 2/24/2020
Description: Creates a delay in the console program for however many seconds the 
function is set to
Input Parameters: int numSec
Returns: void
*/
void delay(int numSec)
{
	int milliSec = 1000 * numSec; //Converts time into Milliseconds
	clock_t sTime = clock(); //Storing start time
	while (clock() < sTime + milliSec); //looping till required time is finished
}

/*
Function: insert()
Date Created: 2/24/2020
Description: This function will prompt the user to input the fields of a Record struct
and then add the new Node to the front of the list.
Input Parameters: void
Returns: void
*/
void insert()
{
	char delim[2] = "\n";
	char* token;
	char sDirector[50];
	char temp[300];
	int tempNum = 0;
	int option = 0, option2 = 0;
	
	Record newData;

	printf("Enter the new Film Title: "); //Film Title
	getchar();
	fgets(temp, sizeof(temp), stdin);
	token = strtok(temp, delim);
	strcpy(newData.title, token);
	printf("This is the new Film Title: %s\n", newData.title);

	printf("Enter the new Director: "); //Director
	fgets(temp, sizeof(temp), stdin);
	token = strtok(temp, delim);
	strcpy(newData.director, token);
	printf("This is the new Director: %s\n", newData.director);

	printf("Enter the new Description: "); //Description
	fgets(temp, sizeof(temp), stdin);
	token = strtok(temp, delim);
	strcpy(newData.description, token);
	printf("This is the new Description: %s\n", newData.description);

	printf("Enter the new Genre: "); //Genre
	fgets(temp, sizeof(temp), stdin);
	token = strtok(temp, delim);
	strcpy(newData.genre, token);
	printf("This is the new Genre: %s\n", newData.genre);

	printf("Enter the new amount of hours in the film: "); //Hours
	do
	{
		scanf("%d", &tempNum);
		newData.duration.hours = tempNum;
	} while (tempNum < 0 || tempNum > 12);
	printf("This is the new amount of hours in the film: %d\n", newData.duration.hours);

	printf("Enter the new amount of minutes in the film: "); //Minutes
	do
	{
		scanf("%d", &tempNum);
		newData.duration.minutes = tempNum;
	} while (tempNum < 0 || tempNum > 60);
	printf("This is the new amount of minutes in the film: %d\n", newData.duration.minutes);

	printf("Enter the new year that the film was released: "); //Year
	do
	{
		scanf("%d", &tempNum);
		newData.year = tempNum;
	} while (tempNum < 0);
	printf("This is the new Year the film was released: %d\n", newData.year);

	printf("Enter the new amount of times this film has been played: "); //Times Played
	do
	{
		scanf("%d", &tempNum);
		newData.plays = tempNum;
	} while (tempNum < 0);
	printf("This is the new amount of times this film has been played: %d\n", newData.plays);

	do  //Rating
	{
		printf("Enter the new rating (1-5) for this film: ");
		scanf("%d", &tempNum);
	} while (tempNum > 5 || tempNum < 1);

	newData.rating = tempNum;
	printf("This is the the new rating (1-5) for this film:: %d\n", newData.rating);

	insertFront(newData); //Inserts the new movie record to the front of the linked list
}

/*
Function: delete()
Date Created: 2/24/2020
Description: This function will prompt the user to input a the name of a film and
then search for said film and then ask the user if they want to confirm that the film should
be deleted from the linked list.
Input Parameters: void
Returns: void
*/
void delete()
{
	char delim[2] = "\n";
	char* token;
	char sFilmTitle[50];
	int endNum = 0;
	int option = 0;
	Node* current = head;
	Node* temp;
	Node* temp2;

	printf("What is the Title of the Film you want to delete?: ");
	getchar();
	fgets(sFilmTitle, sizeof(sFilmTitle), stdin);
	token = strtok(sFilmTitle, delim);
	strcpy(sFilmTitle, token);

	while (current != NULL && endNum == 0)
	{
		//compares the title and runs if statement when the title inputted by the user is the same as the node's
		if (strcmp(sFilmTitle, current->data.title) == 0)
		{
			printRecord(current);
			printf("Is this the film you want to delete? (1 for Yes and 2 for No): ");
			scanf("%d", &option);
			if (option == 1)
			{
				temp = current->pPrev;
				temp2 = current->pNext;
				if (current->pPrev == NULL) //Checks to see if the node is the first in the list
				{
					head = current->pNext; //Sets the head pointer to the 2nd node making it the first
					temp2->pPrev = NULL; //Sets the 2nd node pNext to NULL
					free(current); //Deletes memory
					endNum = 1;
				}
				else if(current->pNext == NULL)
				{
					temp->pNext = NULL; //Sets the node current node to point to the 2nd next node
					free(current); //Deletes memory
					endNum = 1;
				}
				else
				{
					temp->pNext = temp2; //Sets the node current node to point to the 2nd next node
					temp2->pPrev = temp; //sets the 2nd next node pPrev to node current
					free(current); //Deletes memory
					endNum = 1;
				}
				printf("You have deleted this movie from the list!\n");
			}
		}
		if (endNum == 0)
		{
			current = current->pNext;
		}
	}
}

/*
Function: shuffle()
Date Created: 2/24/2020
Description: This function will play the linked list of movies in a random order.
Input Parameters: void
Returns: void
*/
void shuffle()
{
	int length = lengthOfList();
	int rand[100]; //Limit to a linked list size of 100 nodes
	Node* current = head;
	int index = 0;

	getRandomNums(rand); //Create an array with indexes = (the number of nodes in linked lists) filled with random distinct integers

	for (int i = 0; i < length; i++)
	{
		index = rand[i];
		for (int j = 0; j < index; j++)
		{
			current = current->pNext; //Run through the list and go to each node with whatever number is next in the array
		}
		printf("Playing %s...\n", current->data.title);
		delay(1);
		current->data.plays += 1;
		printf("The film has finished playing!\n");
		current = head; //Restart the current pointer to the head pointer and repeat the traversal
	}
	printf("All the films have finised playing!\n");
}

/*
Function: getRandomNums(int* random)
Date Created: 2/24/2020
Description: Will generate an array of integers that are random and distinct from each other
while also being within the bounds of the size of the linked list.
Input Parameters: void
Returns: int* random
*/
void getRandomNums(int* random) //Returns random distinct numbers in an array
{
	srand(time(NULL));
	int x = 0, length = 0;
	length = lengthOfList();
	int duration = length;
	x = (rand() % length); //Generates a random integer for x
	for (int i = 0; i < length; i++) //Checks if the x integer is already in the array or not
	{
		while (checkArr(random, x, length) == 0)
		{
			x = (rand() % length);
		}
		random[i] = x;
	}
}

/*
Function: lengthOfList()
Date Created: 2/24/2020
Description: Will go through the linked list while temp != NULL and
then return the size of the linked list.
Input Parameters: void
Returns: Integer
*/
int lengthOfList() //Returns the length of the linked list
{
	Node* temp = head;
	int count = 0;
	while (temp != NULL)
	{
		count++;
		temp = temp->pNext;
	}
	return count;
}

/*
Function: checkArr(int* result, int check, int size)
Date Created: 2/24/2020
Description: Will check to see if an integer is already repeated in the array and return 0 if the
integer is alread in the array or return 1 if the integer is distinct
Input Parameters: void
Returns: Integer
*/
int checkArr(int* result, int check, int size) //Checks to see if an integer is already repeated in the array
{
	for (int i = 0; i < size; i++)
	{
		if (check == result[i])
		{
			return 0;
		}
	}
	return 1;
}

/*
Function: sort()
Date Created: 2/24/2020
Description: Sorts the based on director(A-Z), Sort based on Film Name(A-Z), 
Sort based on Rating(1-5), Sort based on times played(largest - smallest)
Input Parameters: void
Returns: void
*/
void sort() //Sorts the based on director(A-Z), Sort based on Film Name(A-Z), Sort based on Rating(1-5), Sort based on times played(largest - smallest)
{
	int option = 0;
	option = printSortMenu();
	switch (option)
	{
	case 1:
		sortDirector();
		break;
	case 2:
		sortFilmTitle();
		break;
	case 3:
		sortRating();
		break;
	case 4:
		sortPlays();
		break;
	}
	printList();
}

/*
Function: printSortMenu()
Date Created: 2/24/2020
Description: Will print the options that the user can select from and then prompt
them to return an integer between 1 and 4
Input Parameters: void
Returns: Integer
*/
int printSortMenu()
{
	int option = 0;
	do
	{
		printf("1. Sort based on director (A-Z)\n");
		printf("2. Sort based on film name (A-Z)\n");
		printf("3. Sort based on rating (1-5)\n");
		printf("4. Sort based on times played (largest - smallest)\n");
		printf("What option would you like to select?: ");
		scanf("%d", &option);
	} while (option < 1 || option > 4);
	return option;
}

/*
Function: sortDirector()
Date Created: 2/24/2020
Description: Will sort the linked list by Director from A-Z
Input Parameters: void
Returns: void
*/
void sortDirector()
{
	Node* current = head;
	Node* next;
	Record temp;

	for (current = head; current->pNext != NULL; current = current->pNext)
	{
		for (next = current->pNext; next != NULL; next = next->pNext)
		{
			//compares the director and runs if statement when the current record's director is greater(ABC) than the next record's director
			if (strcmp(current->data.director, next->data.director) > 0)
			{
				temp = current->data; //Swaps data between the nodes
				current->data = next->data;
				next->data = temp;
			}
		}
	}
	printf("Finished sorting by director!\n");
}

/*
Function: sortFilmTitle()
Date Created: 2/24/2020
Description: Will sort the linked list by the film title from A-Z
Input Parameters: void
Returns: void
*/
void sortFilmTitle()
{
	Node* current = head;
	Node* next;
	Record temp;

	for (current = head; current->pNext != NULL; current = current->pNext)
	{
		for (next = current->pNext; next != NULL; next = next->pNext)
		{
			//compares the film title and runs if statement when the current record's film title is greater(ABC) than the next record's film title
			if (strcmp(current->data.title, next->data.title) > 0)
			{
				temp = current->data; //Swaps data between the nodes
				current->data = next->data;
				next->data = temp;
			}
		}
	}
	printf("Finished sorting by film title!\n");
}

/*
Function: sortRating()
Date Created: 2/24/2020
Description: Will sort the linked list by the rating of the film (1-5)
Input Parameters: void
Returns: void
*/
void sortRating()
{
	Node* current = head;
	Node* next;
	Record temp;

	for (current = head; current->pNext != NULL; current = current->pNext)
	{
		for (next = current->pNext; next != NULL; next = next->pNext)
		{
			//compares the rating and runs if statement when the current record's rating is greater than the next records rating
			if (current->data.rating > next->data.rating)
			{
				temp = current->data; //Swaps data between the nodes
				current->data = next->data;
				next->data = temp;
			}
		}
	}
	printf("Finished sorting by rating!\n");
}

/*
Function: sortPlays()
Date Created: 2/24/2020
Description: Will sort the linked list by the most number plays to the least number of plays
Input Parameters: void
Returns: void
*/
void sortPlays()
{
	Node* current = head;
	Node* next;
	Record temp;

	for (current = head; current->pNext != NULL; current = current->pNext)
	{
		for (next = current->pNext; next != NULL; next = next->pNext)
		{
			//compares the number of plays and runs if statement when the current record's number of plays is greater than the next record's plays
			if (current->data.plays < next->data.plays)
			{
				temp = current->data; //Swaps data between the nodes
				current->data = next->data;
				next->data = temp;
			}
		}
	}
	printf("Finished sorting by plays!\n");
}

/*
Function: optionTest()
Date Created: 2/24/2020
Description: Will prompt the user to input an integer between 1 and 2
Input Parameters: void
Returns: Integer
*/
int optionTest()
{
	int option = 0;
	printf("What option do you want?: ");
	do
	{
		scanf("%d", &option);
	} while (option < 1 || option > 2);
	return option;
}

/*
Function: insertTest()
Date Created: 2/24/2020
Description: This function will automatically add data to a Record Struct and then insert it as a node to the
front of the linked list, this record will be called Bohemian Rhapsody.
Input Parameters: void
Returns: void
*/
void insertTest() //Test insert function
{
	Record testData;
	int testPlays = 0; int testYear = 0; int testRating = 0;
	char testTitle[30] = "Bohemian Rhapsody", testDirector[30] = "Bryan Singer", testGenre[50] = "Drama";
	char testDescription[150] = "Freddie Mercury the lead singer of Queen defies stereotypes and convention to become one of history's most beloved entertainers.";
	int testHour = 2, testMinute = 13;
	testYear = 2018;
	testPlays = -1;
	testRating = 6;
	
	strcpy(testData.title, testTitle);
	strcpy(testData.director, testDirector);
	strcpy(testData.description, testDescription);
	strcpy(testData.genre, testGenre);
	testData.duration.hours = testHour;
	testData.duration.minutes = testMinute;
	testData.year = testYear;
	if (testPlays < 0) //Updating data so that it will not allow for -1 plays
		testPlays = 0;
	if (testRating > 5) //Updating data so that it will not allow for a rating above 5
		testRating = 5;
	testData.plays = testPlays;
	testData.rating = testRating;

	insertFront(testData);
	printf("You have successfully added the test film, Bohemian Rhapsody!\n");
	Node* current = head;
	printRecord(current);
}

/*
Function: deleteTest()
Date Created: 2/24/2020
Description: This function will automatically search for the record called Bohemian Rhapsody and
then delete it from the linked list.
Input Parameters: void
Returns: void
*/
void deleteTest() //Delete test function
{
	char testTitle[30] = "Bohemian Rhapsody";
	printf("Attempting to delete Bohemian Rhapsody!\nSearching...");
	delay(2);
	int endNum = 0, option = 0;
	Node* current = head;
	Node* temp;
	Node* temp2;

	while (current != NULL && endNum == 0)
	{
		//compares the title and runs if statement when the title inputted by the user is the same as the node's
		if (strcmp(testTitle, current->data.title) == 0)
		{
			printRecord(current);
			printf("Is this the film you want to delete? (1 for Yes and 2 for No): ");
			scanf("%d", &option);
			if (option == 1)
			{
				temp = current->pPrev;
				temp2 = current->pNext;
				if (current->pPrev == NULL) //Checks to see if the node is the first in the list
				{
					head = current->pNext; //Sets the head pointer to the 2nd node making it the first
					temp2->pPrev = NULL; //Sets the 2nd node pNext to NULL
					free(current); //Deletes memory
					endNum = 1;
				}
				else if (current->pNext == NULL)
				{
					temp->pNext = NULL; //Sets the node current node to point to the 2nd next node
					free(current); //Deletes memory
					endNum = 1;
				}
				else
				{
					temp->pNext = temp2; //Sets the node current node to point to the 2nd next node
					temp2->pPrev = temp; //sets the 2nd next node pPrev to node current
					free(current); //Deletes memory
					endNum = 1;
				}
				printf("You have deleted this movie from the list!\n");
			}
			printf("You have decided to NOT delete this movie from the list!\n");
			endNum = 1;
		}
	}
}

/*
Function: shuffleTest()
Date Created: 2/24/2020
Description: This function will show the number array at which the order
of the movies will be played.
Input Parameters: void
Returns: void
*/
void shuffleTest()
{
	int length = lengthOfList();
	int rand[100]; //Limit to a linked list size of 100 nodes
	Node* current = head;
	int index = -1;

	getRandomNums(rand); //Create an array with indexes = (the number of nodes in linked lists) filled with random distinct integers
	printf("The random list order is: ");
	for (int i = 0; i < length; i++)
	{
		printf("%d", rand[i]);
		if (i != length - 1)
		{
			printf(",");
		}
		else
		{
			printf("\n");
		}
	}

	for (int i = 0; i < length; i++)
	{
		index = rand[i];
		for (int j = 0; j < index; j++)
		{
			current = current->pNext; //Run through the list and go to each node with whatever number is next in the array
		}
		printf("Playing %s...\n", current->data.title);
		delay(1);
		current->data.plays += 1;
		printf("The film has finished playing!\n");
		current = head; //Restart the current pointer to the head pointer and repeat the traversal
	}
	printf("All the films have finised playing!\n");
}