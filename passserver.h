// **********************************************************
// * Name: Christelle Nieves                                *                               *
// * Assignment: Assignment 5: Hash Table Password Server   *
// * Date: April 12, 2020 	                                *
// **********************************************************

#ifndef HASHTABLE_PASSSERVER_H
#define HASHTABLE_PASSSERVER_H


#include <list>
#include <vector>
#include <iterator>
#include <functional>
#include <utility>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include <crypt.h>

#include "hashtable.h"

using namespace std;
using namespace cop4530;


class PassServer
{
public:
	PassServer(size_t size = 101);  // Constructor
	~PassServer();  // Destructor
	bool load(const char *filename);    // Load password file into hash table object
	bool addUser(std::pair<string, string> & kv); // Add new username and password
	bool addUser(std::pair<string, string> && kv); // Move version of addUser
	bool removeUser(const string &k);   // Delete existing user with username k
	bool changePassword(const std::pair<string, string> &p, const string &newpassword); // Change existing user's password
	bool find(const string & user); // Check if a user exists
	void dump(); // Show structure and contents of hash table to screen
	size_t size(); // Return the number of pairs in the hash table
	bool write_to_file(const char *filename); // Save username/psswd combination to a file

private:
	string encrypt(const string &str); // Encrypt str and return encrypted string

	// Attributes
	HashTable<string, string> data;

};

#endif //HASHTABLE_PASSSERVER_H
