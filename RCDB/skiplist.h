#ifndef SKIPLIST_H
#define SKIPLIST_H
#include "skiplist_node.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>

class Skiplist 
{
public:
	SkiplistNode* list_header;
	int list_level;
	
	Skiplist();
	~Skiplist();
	unsigned char* searchNode(unsigned char* key, int key_size);
	bool insertNode(unsigned char* key, int key_size, unsigned char* value, int value_size);
	bool deleteNode(unsigned char* key, int key_size);
	void printList();

private:
	int seed;
	int compare(unsigned char* a, int lenth_a, unsigned char* b, int lenth_b);
	int getRand(int min, int max);
	int getInsertLevel();
	bool isEqual(unsigned char* a, unsigned char* b);

};
#endif // !SKIPLIST_H
