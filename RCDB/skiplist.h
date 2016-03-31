#ifndef SKIPLIST_H
#define SKIPLIST_H
#include "slice.h"
#include <iostream>
#include <time.h>
#include <fstream>

struct SkipListNode
{
	Slice slice;
	SkipListNode** forward;
};

enum OpResult
{
	DELETE_VALUE_SUCCESS,
	DELETE_VALUE_FAILED,
	INSERT_VALUE_SUCCESS,
	MODIFY_VALUE_SUCCESS,
};

class SkipList
{
public:
	explicit SkipList(int max_level = 12);
	~SkipList();

	unsigned char* searchNode(unsigned char* key, int key_size);
	int insertNode(unsigned char* key, int key_size, unsigned char* value, int value_size);
	int deleteNode(unsigned char* key, int key_size);

public:
	void printList();
	void printListToFile(const char* filename);

private:
	int seed;
	//int size;
	int max_level;
	SkipListNode* header;

private:
	int compare(unsigned char* a, int lenth_a, unsigned char* b, int lenth_b);
	int getLevel(int min, int max);

};
#endif // !SKIPLIST_H
