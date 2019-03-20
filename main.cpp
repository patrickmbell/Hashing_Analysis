#include <iostream>
#include <string>
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

int main() {

//	experiment_1::hashtable<string, int> table(127);
//	table.add("plop", 20);

	experiment_1::hashtable<int> table(127);
	table.add("Patrick ", 20);
	table.add("the rock", 512);
	table.add("Jeremy spoke in class today", 1995);
	table.add("Spam", 565);
	table.add("Bo! Bo! Bo!", 1990);

	table.print_table();
	cout << "" << endl; 

	return 0; 
}