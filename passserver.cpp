// **********************************************************
// * Name: Christelle Nieves                                *                               *
// * Assignment: Assignment 5: Hash Table Password Server   *
// * Date: April 12, 2020 	                                *
// **********************************************************

#ifndef HASHTABLE_PASSSERVER_CPP
#define HASHTABLE_PASSSERVER_CPP

#include <iterator>
#include <utility>
#include <string>
#include <unistd.h>
#include <cstring>
#include <crypt.h>

#include "passserver.h"

using namespace std;
using namespace cop4530;

// PassServer Constructor
PassServer::PassServer(size_t size)
{
	data = HashTable<string, string>(size);
}

// PassServer Destructor
PassServer::~PassServer()
{
	data.clear();
}

// Load a username/password file into the hash table object
bool PassServer::load(const char *filename)
{
	return data.load(filename);
}

// Add a new username/password pair to the hash table.
// The password passed in is in plaintext & must be encrypted before insertion
bool PassServer::addUser(std::pair<string, string> & kv)
{
	string encryptedPassword = encrypt(kv.second);
	pair<string, string> newPair;
	newPair.first = kv.first;
	newPair.second = encryptedPassword;
	bool result = data.insert(newPair);
	return result;
}

// Move version of addUser
bool PassServer::addUser(std::pair<string, string> && kv)
{
	pair<string, string> newPair = move(kv);
	bool result = data.insert(newPair);
	return result;
}

// Delete an existing user with username k
bool PassServer::removeUser(const string &k)
{
	return data.remove(k);
}

// Change an existing user's password
// Both passwords passed in are in plaintext & should be encrypted before interaction with hash table
// If user is not in the hash table, return false
// If p.second does not match the current password, return false
// Return false if current password and new password are the same
// Return true if password was successfully updated
bool PassServer::changePassword(const pair<string, string> &p, const string &newpassword)
{
	// Return false if the new password and old password are the same
	// Also return false if the hash table does not contain the username
	if (newpassword == p.second || !(data.contains(p.first)))
	{
		return false;
	}

	// Create a pair containing the username and the encrypted current password
	string currentPass = encrypt(p.second);
	pair<string, string> oldPair;
	oldPair.first = p.first;
	oldPair.second = currentPass;

	// If the current username/password pair does not match the current username/password in the table, return false
	if (!data.match(oldPair))
	{
		return false;
	}

	// Create a pair containing the new password
	pair<string, string> newPair;
	string newPass = encrypt(newpassword);

	newPair.first = p.first;
	newPair.second = newPass;

	// Insert the new username/password pair into the hash table
	data.insert(newPair);

	return true;
}

// Check if a user exists (if user is in hash table)
bool PassServer::find(const string & user)
{
	if (data.contains(user))
	{
		return true;
	}
	return false;
}

// Show structure and contents of the hash table to the screen
void PassServer::dump()
{
	data.dump();
}

// Return the number of pairs in the hash table
size_t PassServer::size()
{
	return data.count;
}

// Write the contents of the hash table to a file with name filename
bool PassServer::write_to_file(const char *filename)
{
	return data.write_to_file(filename);
}


// Encrypt str and return the encrypted string
// This function was inspired by a function found on geeksforgeeks.com
string PassServer::encrypt(const string &str)
{
	char salt[] = "$1$########";
	char* password = new char[100];
	const char* encrypted = crypt(str.c_str(), salt);
	strcpy(password, encrypted);

	return password;
}


#endif