#include <iostream>
#include <random>
#include <map>
#include <time.h>
#include "experiment_1.h"

using namespace std; 

/*
	Hash functions need to be fast to compute. 
	A collision is when two keys have the same index from the hash function. 
	A hash function should minimize collisions. 
	The load factor is basically how much data we have in the hash table. 

	One method to resolving collisions is to put the keys that collide into a linked list - Chaining. 

	Allocating a large array is how you achieve O(1) time for a hash data structure. 
	We are returned an index from a hash function, then we access that index in O(1) time. 

	Load Factor = (Number of Entries / Total size of array). 

	***This project is testing the performance for four combinations of hash functions and collision resolution schemes.*** 
	Hash functions: Key mod table size, mid square
	Collision resolution schemes: seperate chaining, open addressing

	Create plots for each experiment. Include number of collisions versus load factor for the three table sizes. Each experiment should be conducted for three table sizes. 



*/
template <typename V>
void test_hashfunction(experiment_1::hashtable<V> &table) {

	unsigned int i = 0;
	multimap<int, bool> map;

	mt19937 seed(time(0));
	uniform_int_distribution<int> range(0, 200);	//200 being the max key value I've decided upon 
	unsigned int size = table.get_table_size() ;

	while (i < size)
	{
		int rand_key = range(seed);

		auto search = map.find(rand_key);
		while (search != map.end())
		{
			rand_key = range(seed);
			search = map.find(rand_key);
		}

		map.emplace(rand_key, true);

		table.add(rand_key, "Boogie Down Productions"); 


		i++;
	}


}

int main() {

	experiment_1::hashtable<string> table(60);
	table.add(20, "Patrick");
	table.add(42, "Cheech");
	table.add(187, "Blink");
	table.add(45, "KRS ");
	table.add(90, "Bo! Bo! Bo!");

	test_hashfunction(table);

	//table.print_table();
	cout << "\nNumber of Collisions: " << table.get_num_collisions() << endl;

	//int input;

	// while (true) {

	// 	cin >> input;
	// 	auto node = table.get(input);
	// 	cout << node->index << " " << node->value << endl;
	// }

	return 0; 
}