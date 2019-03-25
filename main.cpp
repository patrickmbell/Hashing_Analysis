#include <iostream>
#include <random>
#include <map>
#include <fstream>
#include <time.h>
#include "chaining_table.h"
#include "openaddr_table.h"

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

//Two functions that test the number of collisions given a collision resolution scheme and hashing function. 
template <typename V>
void test_hashtable(chaining_table::hashtable<V> &table)
{

	unsigned int i = 0;
	multimap<int, bool> map;

	mt19937 seed(time(0));
	uniform_int_distribution<int> range(0, table.get_table_size() * 3);	


	while (table.get_load_factor() <= 1)
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
void test_hashtable(openaddr_table::hashtable<V> &table)
{
	unsigned int i = 0;
	multimap<int, bool> map;

	mt19937 seed(time(0));
	uniform_int_distribution<int> range(0, table.get_table_size() * 3);


	while (table.get_load_factor() < 1)
	{
		int rand_key = range(seed);


		auto search = map.find(rand_key);
		while (search != map.end())
		{
			rand_key = range(seed);
			search = map.find(rand_key);
		}

		//cout << rand_key << endl;

		map.emplace(rand_key, true);

		table.add(rand_key, "BDP");
		
	}

}

int main() {

	/*openaddr_table::hashtable<string> table(64, false, "size_1.csv");
	openaddr_table::hashtable<string> table2(64, true, "size_1.csv");
	chaining_table::hashtable<string> table3(100, true);
	chaining_table::hashtable<string> table4(100, false);*/

	// chaining_table::hashtable<string> table1(90, false, "size_1.csv");
	// chaining_table::hashtable<string> table2(127, false, "size_2.csv");
	// chaining_table::hashtable<string> table3(300, false, "size_3.csv");

	// chaining_table::hashtable<string> table1(30, true, "size_1.csv");
	// chaining_table::hashtable<string> table2(113, true, "size_2.csv");
	// chaining_table::hashtable<string> table3(195, true, "size_3.csv");

	ofstream summary("collisions_summary.txt");



	chaining_table::hashtable<string> table1(47, false, "size_1.csv");
	chaining_table::hashtable<string> table2(100,false, "size_2.csv");
	chaining_table::hashtable<string> table3(250,false, "size_3.csv");

	test_hashtable(table1);
	test_hashtable(table2);
	test_hashtable(table3);


	// summary << "Type: Chaining Table Size: " << table1.get_table_size() << " Number of Collisions: " << table1.get_num_collisions() << endl;
	// summary << "Type: Chaining Table Size: " << table2.get_table_size() << " Number of Collisions: " << table2.get_num_collisions() << endl;
	// summary << "Type: Chaining Table Size: " << table3.get_table_size() << " Number of Collisions: " << table3.get_num_collisions() << endl;

	summary << table1.get_num_collisions() << endl;
	summary << table2.get_num_collisions()	<< endl; 
	summary << table3.get_num_collisions()	<< endl; 

	summary.flush();
	summary.close(); 

	return 0; 
}