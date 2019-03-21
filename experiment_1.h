#pragma once

#include <iostream>
#include <string>
#include <math.h>
#include <random>
#include <map>
#include <time.h>

using namespace std;

/*Experiment One will be a hash table using mid square hashing and chaining*/
namespace experiment_1 {
	
	template <typename V>
	class hashtable {
	public:
		
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

			Node(){}

		};

		//Might get rid of this. 
		struct iterator {
			Node* head; 

			~iterator()
			{
				while (head)
				{
					Node* temp = head;
					head = head->next; 
					delete temp;
				}
			}

			void add(Node* node) {

				Node* temp = head; 
				while (temp->next)
				{
					temp = temp->next;
				}

				temp->next = node; 
			}
		};

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
		
		unsigned int get_table_size() { return table_size; }
		unsigned int get_num_collisions() { return num_collisions; }
		unsigned int get_load_factor() { return load_factor; }

		bool is_full() {
			if (num_array_elements == table_size || num_array_elements > table_size)
				return true;

		return false; 
		}

		void add(const int &key, const V &value);
		int midsquare_hash(int key);	//mid-square hashing function for Experiment 1. 
		void test_hashfunction();
		
		Node* get(const int &key) {
			
			Node* node = table[midsquare_hash(key)];
			
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
 


		float load_factor = 0;
	private:
		Node** table;	//An array of Node pointers. 
		unsigned int num_elements=0;
		unsigned int num_collisions = 0;
		unsigned int table_size; 
		const int max_bits = 16;
		unsigned int num_array_elements = 0; 
		

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
		
		
		int half = ( log2((this->table_size*3)*(table_size*3) - 1) - log2( table_size - 1 ) ) / 2;
		
		int key_squared = key * key; 
		key_squared = key_squared >> half;
		key_squared = key_squared % table_size; 
		


		return key_squared;
	}

	template <typename V>
	void hashtable<V>::test_hashfunction() {

		unsigned int i = 0;
		multimap<int, bool> map;

		mt19937 seed(time(0));
		uniform_int_distribution<int> range(0, size * 3);	//200 being the max key value I've decided upon 


		while (load_factor <= 1)
		{
			int rand_key = range(seed);


			auto search = map.find(rand_key);
			while (search != map.end())
			{
				rand_key = range(seed);
				search = map.find(rand_key);
			}

			map.emplace(rand_key, true);

			table.add(rand_key, "BDP");

		}
	}

	template <typename V>
	void hashtable<V>::add(const int &key, const V &value) 
	{
		int hash; 
	

			if(num_array_elements == table_size)
			{
				cout << "Table full" << endl;
				return; 
			}

			hash = midsquare_hash(key);

			Node* node = new Node(key, value, hash);

			num_elements++; 

			load_factor = (float) num_elements / (float) table_size; 

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

			/*
			if (this->num_elements == 0)
			{
				this->iter.head = temp;
				num_elements++; 
				return;
			}
			else {
				iter.add(temp);
				num_elements++; 
			}
			*/


	}

}
