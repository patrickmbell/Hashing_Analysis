#pragma once

#include <iostream>
#include <string>
#include <math.h>

using namespace std;

/*
	I might actually do just the string as the key and use a generic type for the value. 
*/

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
		//float load_factor=0;
		//iterator iter;

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

		//2^16 = 65,536, 17 bits. 
		
		int half = ( log2((this->table_size*3)*(table_size*3) - 1) - log2( table_size - 1 ) ) / 2;
		
		int key_squared = key * key; 
		key_squared = key_squared >> half;
		key_squared = key_squared % table_size; 
		

		//int num_bits = (int) (log2((double)table_size) + 0.99);	//This should work but you can even do + 0.99 and truncate that to get the consisten number of bits. 
	//	int key_bits = (int) (log2((double)key_squared) + 0.99);

//		int hash = key_squared % table_size;	

		return key_squared;
		//return key % table_size; 
	}
	
	//template <typename V>
	//hashtable<V>::Node& hashtable<V>::get(const int &key) {
	//	hashtable<V>::Node* node = table[midsquare_hash(key)];

	//	return node; 
	//}

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
