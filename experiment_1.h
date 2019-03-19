#pragma once

#include <iostream>
#include <math.h>
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

		/*
		class Iterator {	//How cool would this be, making an iterator of the map. 
			

		};
		*/

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
	
		void add(const K &key, const V &value);
		int midsquare_hash(int key);	//mid-square hashing function for Experiment 1. 
		Node& get(const K &key) {}

	private:
		Node* table;	//An element is inserted into the array, and each node would have a next pointer since this will be done using chaining. 
		unsigned int num_elements=0;
		unsigned int table_size; 
		const int max_bits = 16;

	};

	template <typename K, typename V>
	int hashtable<K,V>::midsquare_hash(int key)
	{
		//For this hashing function. Utilizing reinterpreted cast will be useful in getting an integer value from the key. I need to be careful of not creating hash values that are out of bounds. 
		//If the passed through type is a string, the ascii value used for hashing will be generated from an average of ascii values per character
		//If the type is a char, the ascii value will be used
		//And if a float or double is used, it will be casted to an int
		//Therefore, for the sake of the experiment, I'll limit the key values to 200. 

		//200^2 = 40,000
		//The table size for experiment will be 127. 
		//127 in binary is 1111111, 7 bits. 
		//2^16 = 65,536, 16 bits. 

		int key_squared = key * key; 

		int num_bits = (int) (log2((double)table_size) + 0.99);	//This should work but you can even do + 0.99 and truncate that to get the consisten number of bits. 
		int key_bits = (int) (log2((double)key_squared) + 0.99);

		

		return num_bits; 
	}

	template <typename K, typename V>
	void hashtable<K, V>::add(const K &key, const V &value) 
	{
		int hash; 

		try {
			if (std::is_same<K, string>::value)
			{
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

			}
			else {

				if ((int)key > 200)
				{
					cout << "Error: key value too high\n";
					return;
				}

			}
		}
		catch (exception &e)
		{
			cout << "Uh oh!" << endl; 
		}
	}

}
