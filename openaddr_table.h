#pragma once

#include <iostream>
#include <string>
#include <math.h>
#include <random>
#include <map>
#include <time.h>
#include <fstream>

using namespace std;

/*
 A hashtable that is capable of utilizing midsquare hashing or key mod tablesize hashing while using an open addressing Collision Resolution Scheme. 
*/

namespace openaddr_table {

	template <typename V>
	class hashtable {
	public:

		//A Node struct used for storing the key-value pairs into an array. 
		struct Node {

			V value;
			int key;
			int index;
			//bool collision = false;

			Node(int key, V value, int index) {
				this->key = key;
				this->value = value;
				this->index = index;
			}

			Node() {}

		};

		//Hashtable class constuctors 
		hashtable(unsigned int size)
		{
			table = new Node*[size]();
			table_size = size;
		}

		hashtable(unsigned int size, bool midsquare_hashing, string filename)
		{
			table = new Node*[size]();
			table_size = size;
			this->midsquare_hashing = midsquare_hashing;
			this->filename = filename;

			try
			{
				file.exceptions(ifstream::badbit | ifstream::failbit);
				file.open(filename);
				file << 0 << ',' << 0 << endl; 
			}
				
			catch (const ifstream::failure& e)
			{
				cout << "Tried opening file with windows syntax, Attempting Linux syntax: " << endl;
				file.open(filename);
			}
		}

		hashtable(unsigned int size, bool midsquare_hashing)
		{
			table = new Node*[size]();
			table_size = size;
			this->midsquare_hashing = midsquare_hashing;
		}

		hashtable() {
			table_size = 0;
		}

		~hashtable()
		{
			delete[] table;
			file.flush();
			file.close();

			cout << "File Closed" << endl; 
		}

		//Mutators
		void add(const int &key, const V &value);
		Node* get(const int &key);

		//Accessors
		unsigned int get_table_size() { return table_size; }
		unsigned int get_num_collisions() { return num_collisions; }
		float get_load_factor() { return load_factor; }

		//Hashing Function
		int midsquare_hash(int key);	//mid-square hashing function for Experiment 1. 

	private:
		ofstream file;
		string filename;
		Node** table;	//An array of Node pointers. 
		unsigned int num_elements = 0;
		unsigned int num_collisions = 0;
		unsigned int table_size;
		const int max_bits = 16;
		float load_factor = 0;
		bool midsquare_hashing = false; //By default use key-mod-table hashing. 
	};

	template <typename V>
	int hashtable<V>::midsquare_hash(int key)
	{
		//For this hashing function. Utilizing reinterpreted cast will be useful in getting an integer value from the key. I need to be careful of not creating hash values that are out of bounds. 
		//If the passed through type is a string, the ascii value used for hashing will be generated from an average of ascii values per character
		//If the type is a char, the ascii value will be used
		//And if a float or double is used, it will be casted to an int
		//Therefore, for the sake of the experiment, I'll limit the key values to 200. 

		//127^2 = 40,000
		//The table size for experiment will be 127. 
		//127 in binary is 1111111, 7 bits. 

		int key_bits = log2(((table_size-1) * 3) * ((table_size-1) * 3)) + 1;
		int table_bits = log2(table_size-1) + 1;
		int difference = key_bits - table_bits;

		if (difference % 2 != 0)
			difference += 1;

		int half = difference / 2;
		int key_squared = key * key;
		key_squared = key_squared >> half;
		key_squared = key_squared % table_size;


		return key_squared;
	}

	template <typename V>
	void hashtable<V>::add(const int &key, const V &value)
	{
		int hash;


		if (num_elements == table_size)
		{
			cout << "Table full" << endl;
			return;
		}

		if (midsquare_hashing)
			hash = midsquare_hash(key);
		else
			hash = key % table_size;


		Node* node = new Node(key, value, hash);

		num_elements++;

		load_factor = (float)num_elements / (float)table_size;

		if (!table[hash])
		{
			this->table[hash] = node;
			return;
		}

		else {
			int index = hash;
			num_collisions++;
			while (table[index] && index)
			{
				index++;

				if (index == table_size - 1)
					index = 0;
			}
			table[index] = node; 
		}

		try
		{
			file << load_factor << ',' << num_collisions << endl; 
		}
		catch(const ifstream::failure& e)
		{
			cout << "Error writing to file" << endl; 
		}
		
	}

	template <typename V>
	typename hashtable<V>::Node* hashtable<V>::get(const int &key) {

		Node* node = table[midsquare_hash(key)];

		


		// if (node->next)	//indicating that there is a collision. 
		// {
		// 	while (node->next)
		// 	{
		// 		if (node->key == key)
		// 		{
		// 			return node;
		// 		}

		// 		node = node->next;
		// 	}
		// }


		return node;
	}

}
