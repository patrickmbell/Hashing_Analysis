#pragma once

#include <iostream>
#include <string>
#include <math.h>
#include <random>
#include <map>
#include <time.h>

using namespace std;

/*

	Experiment Two is Key Mod Table Hashing and Chaining Collisions 

*/
namespace experiment_2 {

	template <typename V>
	class hashtable {
	public:

		//A Node struct used for storing the key-value pairs into an array. 
		struct Node {

			Node* next = nullptr; //The Nodes next pointer if a collision occurs and requires chaining 

			V value;
			int key;
			int index;
			bool collision = false;

			Node(int key, V value, int index) {
				this->key = key;
				this->value = value;
				this->index = index;

			}

			Node() {}

		};

		//Constructors
		hashtable(unsigned int size)
		{
			table = new Node*[size]();
			table_size = size;

		}

		hashtable() {
			table_size = 0;
		}

		~hashtable()
		{
			delete[] table;
		}

		//Accessors
		unsigned int get_table_size() { return table_size; }
		unsigned int get_num_collisions() { return num_collisions; }
		float get_load_factor() { return load_factor; }
		
		//Mutators
		void add(const int &key, const V &value);
		Node* get(const int &key);


		//Hashing Function
		int key_mod_table(int key);	//mid-square hashing function for Experiment 1. 

	private:
		Node** table;	//An array of Node pointers. 
		unsigned int num_elements = 0;
		unsigned int num_collisions = 0;
		unsigned int table_size;
		const int max_bits = 16;
		float load_factor = 0;
		unsigned int num_array_elements = 0;


	};

	template <typename V>
	int hashtable<V>::key_mod_table(int key)
	{
		//For this hashing function. Utilizing reinterpreted cast will be useful in getting an integer value from the key. I need to be careful of not creating hash values that are out of bounds. 
		//If the passed through type is a string, the ascii value used for hashing will be generated from an average of ascii values per character
		//If the type is a char, the ascii value will be used
		//And if a float or double is used, it will be casted to an int
		//Therefore, for the sake of the experiment, I'll limit the key values to 200. 

		//127^2 = 40,000
		//The table size for experiment will be 127. 
		//127 in binary is 1111111, 7 bits. 
	
		return key % table_size; 
	}

	template <typename V>
	void hashtable<V>::add(const int &key, const V &value)
	{
		int hash;


		if (num_array_elements == table_size)
		{
			cout << "Table full" << endl;
			return;
		}

		hash = key_mod_table(key);

		Node* node = new Node(key, value, hash);

		num_elements++;

		load_factor = (float)num_elements / (float)table_size;

		if (!table[hash])
		{
			this->table[hash] = node;
			num_array_elements++;
			return;
		}

		else {

			Node* temp = table[hash];

			if (!temp->collision)
			{
				cout << "Collision Detectected! Key: " << key << " Index: " << hash;
				cout << " Load: " << this->load_factor << endl;

				temp->collision = true;

				num_collisions++;

			}



			while (temp->next)
			{
				temp = temp->next;
			}
			temp->next = node;

		}

	}
	
	template <typename V>
	typename hashtable<V>::Node* hashtable<V>::get(const int &key) {

		Node* node = table[key_mod_table(key)];

		if (node->next)	//indicating that there is a collision. 
		{
			while (node->next)
			{
				if (node->key == key)
				{
					return node;
				}

				node = node->next;
			}
		}


		return node;
	}

}
