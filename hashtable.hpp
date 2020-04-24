// **********************************************************
// * Name: Christelle Nieves                                *                                *
// * Assignment: Assignment 5: Hash Table Password Server   *
// * Date: April 12, 2020 	                                *
// **********************************************************

#ifndef HASHTABLE_HASHTABLE_HPP
#define HASHTABLE_HASHTABLE_HPP

#include <iostream>
#include <list>
#include <vector>
#include <iterator>
#include <functional>
#include <utility>
#include <fstream>
#include <sstream>

#include "hashtable.h"

using namespace std;
using namespace cop4530;

// Constructor
template <typename K, typename V>
HashTable<K, V>::HashTable(size_t size)
{
	vector_size = prime_below(size);
	table.resize(vector_size);
	count = 0;
}

// Destructor
template <typename K, typename V>
HashTable<K, V>::~HashTable()
{
	clear();
}

// Check if key k is in the hash table
template <typename K, typename V>
bool HashTable<K, V>::contains(const K & k)
{
	size_t index = myhash(k);
	auto itr = table[index].begin();

	while (itr != table[index].end())
	{
		if (itr->first == k)
		{
			return true;
		}

		itr++;
	}

	return false;
}

// Check if key-value pair is in the hash table
template <typename K, typename V>
bool HashTable<K, V>::match(const pair<K, V> & kv)
{
	if (contains(kv.first))
	{

		int index = myhash(kv.first);
		for (auto itr = table[index].begin(); itr != table[index].end(); itr++)
		{
			if (itr->first == kv.first)
			{
				if (itr->second == kv.second)
				{
					return true;
				}
			}
		}
	}

	return false;
}

// Add key-value pair kv into the hash table.
// Do not add if kv is already in the table.
// If key is in hash table but with different val, val will be updated to new val.
// Return true if kv is inserted/updated, false otherwise.
template <typename K, typename V>
bool HashTable<K, V>::insert(const pair<K, V> & kv)
{
	// If the pair is already in the hash table, return false.
	if (match(kv))
	{
		return false;
	}

	// If the key is found, update the value
	if (contains(kv.first))
	{
		// The index for the key
		int index = myhash(kv.first);

		for (auto itr = table[index].begin(); itr != table[index].end(); itr++)
		{
			// If we find the pair with the matching key, replace the value
			if (itr->first == kv.first)
			{
				auto newValue = table[index].erase(itr);
				table[index].insert(newValue, kv);
			}
		}

		return true;
	}

	table[myhash(kv.first)].push_back(kv);
	count++;

	if (count > table.size())
	{
		rehash();
	}

	return true;
}

// Move version of insert
template <typename K, typename V>
bool HashTable<K, V>::insert(pair<K, V> && kv)
{
	const pair<K, V> newPair;
	newPair = move(kv);
	bool result = insert(newPair);

	return result;
}

// Delete the key k and the corresponding val if it is in the hash table
// Return true if k is deleted, false otherwise
template <typename K, typename V>
bool HashTable<K, V>::remove(const K & k)
{
	if (!contains(k))
	{
		return false;
	}

	int index = myhash(k);

	for (auto itr = table[index].begin(); itr != table[index].end(); itr++)
	{
		if (itr->first == k)
		{
			itr = table[index].erase(itr);
			count--;
			return true;
		}
	}

	return false;
}

// Delete all elements in the hash table
template <typename K, typename V>
void HashTable<K, V>::clear()
{
	makeEmpty();
}

// Display all entries in the hash table.
// If an entry contains multiple key-val pairs, separate them by a semicolon
template <typename K, typename V>
void HashTable<K, V>::dump()
{
	// Outer loop loops through the vector
	for (int i = 0; i < table.size(); i++)
	{
		// If the list at this vector index is not empty, print its contents
		if (!table.at(i).empty())
		{
			cout << "v[" << i << "]: ";
			int index = 0;

			// Iterate through the list at vector index i
			for (auto itr = table.at(i).begin(); itr != table.at(i).end(); ++itr)
			{
				// Increment the index counter each time we loop
				index++;
				cout << itr->first << " " << itr->second;

				// If the index counter is not at the last index of the list, print a ":"
				if (index != table.at(i).size())
				{
					cout << " : ";
				}
			}
			cout << endl;
		}
	}
}

// Load the contents of the file with name filename into the hash table
template <typename K, typename V>
bool HashTable<K, V>::load(const char *filename)
{
	// Open the file using the given filename
	ifstream file;
	file.open(filename);

	// Return false if the file could not be opened
	if (!file.is_open())
	{
		return false;
	}
	else
	{
		string line;

		// Parse the file and store all contents as pairs
		while(getline(file,line))
		{
			pair<string, string> newPair;
			stringstream ss(line);
			string lhs;
			string rhs;

			ss >> lhs; // Get the username
			ss >> rhs; // Get the password

			newPair.first = lhs; // Put the username into the pair
			newPair.second = rhs; // Put the password into the pair

			insert(newPair);  // Insert the key value pair into the hash table
		}
	}

	// Close the file and return true since we were able to load the file
	file.close();
	return true;
}

// Write all elements in the hash table into a file with name filename
// Each line contains pair of key-val pair separated by a white space
template <typename K, typename V>
bool HashTable<K, V>::write_to_file(const char *filename)
{
	ofstream file;
	file.open(filename);

	if (!file.is_open())
	{
		return false;
	}

	for (int i = 0; i < table.size(); i++)
	{
		if (!table.at(i).empty())
		{
			for (auto itr = table.at(i).begin(); itr != table.at(i).end(); itr++)
			{
				file << itr->first << " " << itr->second << "\n";
			}
		}
	}
	file.close();

	return true;
}

// Delete all elements in the hash table
template <typename K, typename V>
void HashTable<K, V>::makeEmpty ()
{
	table.clear();
	count = 0;
	table.resize(prime_below(101));
	vector_size = prime_below(101);
}

// Rehash function.
// Called when the num of elements in the hash table is greater than size of vector
template <typename K, typename V>
void HashTable<K, V>::rehash()
{
	// Double the hash table size
	int newSize = prime_below(vector_size * 2);
	table.resize(newSize);
	vector_size = newSize;
}

// Return the index of the vector entry where k should be stores
template <typename K, typename V>
size_t HashTable<K, V>::myhash(const K & k)
{
	// Use the std::hash class to determine the hash value
	hash<K> h;
	size_t val = h(k) % table.size();
	return val;
}

// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
	if (n > max_prime)
	{
		cerr << "** input too large for prime_below()\n";
		return 0;
	}
	if (n == max_prime)
	{
		return max_prime;
	}
	if (n <= 1)
	{
		cerr << "** input too small \n";
		return 0;
	}

	// now: 2 <= n < max_prime
	vector <unsigned long> v (n+1);
	setPrimes(v);
	while (n > 2)
	{
		if (v[n] == 1)
			return n;
		--n;
	}

	return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n)
template <typename K, typename V>
void HashTable<K, V>::setPrimes(vector<unsigned long>& vprimes)
{
	int i = 0;
	int j = 0;

	vprimes[0] = 0;
	vprimes[1] = 0;
	int n = vprimes.capacity();

	for (i = 2; i < n; ++i)
		vprimes[i] = 1;

	for( i = 2; i*i < n; ++i)
	{
		if (vprimes[i] == 1)
			for(j = i + i ; j < n; j += i)
				vprimes[j] = 0;
	}
}

#endif //HASHTABLE_HASHTABLE_HPP
