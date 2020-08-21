#include "header.h"

/**********************************************************
Programmer: Koji Natsuhara
Class: CptS 122, Spring 2020, Lab Section 3
Programming Assignment: Programming Assignment 3: Doubly Linked List
Date: February 24, 2020
Description: This program will read the records from the moviePlayList.csv
and then insert them into the front of a doubly linked list. After that, the user
can decide what functions they want to use to edit, insert an additional movie, delete
a movie or shuffle the movie play list.
**********************************************************/

int main()
{
	head = NULL;
	int option = 0, EXIT = 0;

	while (EXIT == 0)
	{
		while (EXIT == 0)
		{
			option = menu();
			runOption(option, &EXIT);
			system("pause");
			system("cls");
		}
	}

	return 0;
}

