// **********************************************************
// * Name: Christelle Nieves                                *                                *
// * Assignment: Assignment 5: Hash Table Password Server   *
// * Date: April 12, 2020 	                                *
// **********************************************************

#include<iostream>
#include<utility>
#include <crypt.h>
#include "passserver.h"

using namespace std;

// Function prototypes
void Menu();

int main()
{
	// Get the hash table capacity from the user
	int capacity;
	cout << "Please enter your preferred hash table capacity: ";
	cin >> capacity;

	// Create the password server using the capacity
	PassServer server(capacity);

	// Display menu and get menu choice from user
	Menu();
	char choice;
	cin >> choice;

	// Continue displaying menu until user decides to quit the program
	while (choice != 'x')
	{
		switch(choice)
		{
			// Load file
			case 'l':
			{
				string filename;
				bool success;

				// Get filename from user
				cout << "Enter the password file name to load from: ";
				cin >> filename;

				// Convert filename to const char and load the file
				const char * name = filename.c_str();
				success = server.load(name);

				// If file could not load, display error message
				if (!success)
				{
					cout << "Error: could not load file" << endl;

				}

				break;
			}
			// Add user
			case 'a':
			{
				string username;
				string password;

				// Get the username and password from the user
				cout << "Enter username: ";
				cin >> username;
				cout << "Enter password: ";
				cin >> password;

				// Create a pair with the username and password
				pair<string, string> userpass;
				userpass.first = username;
				userpass.second = password;

				// Add the user to the hash table
				bool added = server.addUser(userpass);

				// If user could not be added, display error message.
				if (!added)
				{
					cout << "Error: user could not be added." << endl;
				}
				else
				{
					cout << "User added." << endl;
				}

				break;
			}
			// Remove user
			case 'r':
			{
				string username;

				// Get username from the user
				cout << "Enter the username: ";
				cin >> username;

				// Remove the user from the hash table
				bool removed = server.removeUser(username);

				// If user could not be removed, show error message.
				if (!removed)
				{
					cout << "Error: User could not be removed." << endl;
				}
				else
				{
					cout << "User removed." << endl;
				}
				break;
			}
			// Change password
			case 'c':
			{
				string username;
				string newPassword;
				string currentPassword;

				// Get the username, current password, and new password from the user.
				cout << "Enter the username: ";
				cin >> username;
				cout << "Enter current password: ";
				cin >> currentPassword;
				cout << "Enter new password: ";
				cin >> newPassword;

				// Create a par with the username and current password
				pair<string, string> currentData;
				currentData.first = username;
				currentData.second = currentPassword;

				// Change the password to the new password
				bool changed = server.changePassword(currentData, newPassword);

				// If password could not be changed, display error message
				if (!changed)
				{
					cout << "Error: Password could not be changed." << endl;
				}
				else
				{
					cout << "Password changed." << endl;
				}
				break;
			}
			// Find user
			case 'f':
			{
				string username;

				// Get username
				cout << "Enter the username: ";
				cin >> username;

				// Attempt to find the user in the hash table
				bool found = server.find(username);

				// If user could not be found, display error message.
				if (!found)
				{
					cout << "Error: User not found." << endl;
				}
				else
				{
					cout << "User found." << endl;
				}
				break;
			}
			// Dump hash table
			case 'd':
			{
				server.dump();
				break;
			}
			// Hash table size
			case 's':
			{
				cout << "Size of hash table(Number of pairs): " << server.size() << endl;
				break;
			}
			// Write to password file
			case 'w':
			{
				string filename;

				// Get the filename
				cout << "Enter the filename: ";
				cin >> filename;

				// Convert filename to const char and write the file
				const char * name = filename.c_str();
				bool written = server.write_to_file(name);

				// If file was not written, show error message
				if (!written)
				{
					cout << "Error: Could not write to file." << endl;
				}
				else
				{
					cout << "File written." << endl;
				}
				break;
			}
			// Exit the program
			case 'x':
			{
				cout << "Goodbye." << endl;
				break;
			}
			default:
				break;
		}

		// Get the user's next menu choice
		Menu();
		cin >> choice;
	}

	return 0;
}

void Menu()
{
	cout << "\n\n";
	cout << "l - Load From File" << endl;
	cout << "a - Add User" << endl;
	cout << "r - Remove User" << endl;
	cout << "c - Change User Password" << endl;
	cout << "f - Find User" << endl;
	cout << "d - Dump HashTable" << endl;
	cout << "s - HashTable Size" << endl;
	cout << "w - Write to Password File" << endl;
	cout << "x - Exit program" << endl;
	cout << "\nEnter choice : ";
}
