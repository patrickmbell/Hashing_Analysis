#include <iostream>
#include <random>
#include <map>
#include <time.h>
#include "experiment_1.h"
#include "experiment_2.h"

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

int main() {

	experiment_1::hashtable<string> table(113);
	//table.add(20, "Patrick");
	//table.add(42, "Cheech");
	//table.add(187, "Blink");
	//table.add(45, "KRS ");
	//table.add(90, "Bo! Bo! Bo!");

	table.test_hashfunction();

	cout << "\nNumber of Collisions: " << table.get_num_collisions() << endl;

	experiment_2::hashtable<string> table2(113);
	table2.test_hashfunction();

	cout << "\nNumber of Collisions: " << table2.get_num_collisions() << endl;

	return 0; 
}