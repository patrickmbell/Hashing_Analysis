#pragma once

#include <iostream>
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
			string key; 
			int index; 

			Node(string key, V value, int index) {
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
			table = new Node*[size];
			table_size = size;

		}

		hashtable() {
			table_size = 0; 
		}

		~hashtable()
		{
			delete[] table; 
		}
	
		void print_table(){
			Node* temp = iter.head;
			while (temp)
			{
				cout << temp->key << " " << temp->value << " " << temp->index << endl; 
				temp = temp->next; 
			}
		}

		void add(const string &key, const V &value);
		int midsquare_hash(int key);	//mid-square hashing function for Experiment 1. 
		Node& get(const string &key) {}

	private:
		Node** table;	//An array of Node pointers. 
		unsigned int num_elements=0;
		unsigned int table_size; 
		const int max_bits = 16;
		unsigned int load;
		iterator iter;

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
		//
		//2^16 = 65,536, 17 bits. 

		int operation =( 17-log2(table_size + 0.99) ) / 2;
		
		int key_squared = key * key; 
		key_squared = key_squared >> 5;
		key_squared = key_squared % table_size; 

		//int num_bits = (int) (log2((double)table_size) + 0.99);	//This should work but you can even do + 0.99 and truncate that to get the consisten number of bits. 
		//int key_bits = (int) (log2((double)key_squared) + 0.99);

		//int hash = key_squared % table_size;	

		return key_squared;
	}

	template <typename V>
	void hashtable<V>::add(const string &key, const V &value) 
	{
		int hash; 

		try {
			
				int avg_char = 0;
				for (unsigned int i = 0; i < key.length(); i++)
				{
					int temp = int(key[i]);
					avg_char += temp;
				}
				avg_char = (avg_char) / (key.length() - 1);

				if (avg_char > 200)
				{
					cout << "Error: key value too high\n";
					return;
				}

				hash = midsquare_hash(avg_char);

				Node* temp = new Node(key, value, hash);
				this->table[hash] = temp;

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
				
	
		}
		catch (exception &e)
		{
			cout << "Uh oh!" << endl; 
		}
	}

}
