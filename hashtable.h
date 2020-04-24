// **********************************************************
// * Name: Christelle Nieves                                *                             *
// * Assignment: Assignment 5: Hash Table Password Server   *
// * Date: April 12, 2020 	                                *
// **********************************************************

#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#include <iostream>
#include <list>
#include <vector>
#include <iterator>
#include <functional>
#include <utility>
#include <fstream>

using namespace std;

namespace cop4530
{
	// max_prime is used by the helpful functions provided
	// to you.
	static const unsigned int max_prime = 1301081;
	// the default_capacity is used if the initial capacity
	// of the underlying vector of the hash table is zero.
	static const unsigned int default_capacity = 11;

	template <typename K, typename V>
	class HashTable
	{
	public:
		std::vector<std::list< std::pair<K, V> > > table; // The hash table
		size_t count = 0;
		size_t vector_size = 0;

		HashTable(size_t size = 101); // Constructor
		~HashTable(); // Destructor
		bool contains(const K & k); // Check if key is in hash table
		bool match(const pair<K, V> & kv); // Check if key-value pair is in hash table
		bool insert(const pair<K, V> & kv); // Add key-val pair into hash table if not already in hash table
		bool insert(pair<K, V> && kv); // Move version of insert
		bool remove(const K & k); // Delete key k and corresponding value if it is in the hash table
		void clear(); // Delete all elements in the hash table
		bool load(const char *filename); // Load the content of the file into the hash table
		void dump(); // Display all entries in the hash table
		bool write_to_file(const char *filename); // Write all elements in hash table into a file with name filename

	private:
		void makeEmpty(); // Delete all elements in the hash table. Called by clear()
		void rehash(); // Rehash function. Called when num of elements in hash table is greater than size of vector
		size_t myhash(const K & k); // Return index of vector entry where k should be stored
		unsigned long prime_below(unsigned long);
		void setPrimes(vector<unsigned long> &);
	};

}

#include "hashtable.hpp"

#endif //HASHTABLE_HASHTABLE_H
