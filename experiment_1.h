#pragma once

#include <iostream>

using namespace std;

/*Experiment One will be a hash table using mid square hashing and chaining*/
namespace experiment_1 {
	
	template <typename K, typename V>
	class hashtable {
	public:
		
		struct Node {
			int load_factor;
			bool collision; 
			Node* next; 

			V data; 
		};

		hashTable(unsigned int size)
		{
			table = new T[size];
			table_size = 0;

		}
		~hashTable()
		{
			delete[] table; 
		}
	
	private:
		T* table; 
		unsigned int num_elements=0;
		unsigned int table_size; 

		midsquare_hash(const K);


	};

}