#pragma once

#include <iostream>

using namespace std;

/*
	I might actually do just the string as the key and use a generic type for the value. 
*/

/*Experiment One will be a hash table using mid square hashing and chaining*/
namespace experiment_1 {
	
	template <typename K, typename V>
	class hashtable {
	public:
		
		struct Node {
			//int load_factor;
			//bool collision; 
			Node* next; //The Nodes next pointer if a collision occurs and requires chaining 

			K key; 
			V value;

		};

		hashtable(unsigned int size)
		{
			table = new Node[size];
			table_size = size;

		}

		hashtable() {
			table_size = 0; 
		}

		~hashtable()
		{
			delete[] table; 
		}
	
	private:
		Node* table;	//An element is inserted into the array, and each node would have a next pointer since this will be done using chaining. 
		unsigned int num_elements=0;
		unsigned int table_size; 

		void hash_function(const K &key);	//mid-square hashing function for Experiment 1. 

		void add(const K &key, const V &value);

		Node& get(const K &key){}

	};

	template <typename K, typename V>
	void hashtable<K,V>::hash_function(const K &key)
	{
		//For this hashing function. Utilizing reinterpreted cast will be useful in getting an integer value from the key. I need to be careful of not creating hash values that are out of bounds. 
	}

	template <typename K, typename V>
	void hashtable<K, V>::add(const K &key, const V &value) 
	{
	
	}

}
