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

	Slice searchNode(unsigned char* key, int key_size);
	int insertNode(unsigned char* key, int key_size, unsigned char* value, int value_size);
	int deleteNode(unsigned char* key, int key_size);

	int getSize();
public:
	void printList();
	void printListToFile(const char* filename);

	SkipListNode* Begin();
private:
	int seed;
	int size;
	int max_level;
	SkipListNode* header;

private:
	int compare(unsigned char* a, int lenth_a, unsigned char* b, int lenth_b);
	int getLevel(int min, int max);


private:
	class List_Iterator
	{
		SkipListNode* curr;
		SkipListNode* head;
		Slice p;
	public:
		void operator =(SkipListNode* ptr)
		{
			curr = ptr;
			head = ptr;
			p = Slice();
		}

		Slice& pre()
		{
			p = Slice();
			if (curr == head || head->forward[0] == curr)
			{
				curr = head;
				return p;
			}
			SkipListNode* it = head->forward[0];
			while (it->forward[0] != curr)
			{
				it = it->forward[0];
			}
			p = it->slice;
			curr = it;
			return p;
		}

		Slice& next()
		{
			p = Slice();
			if (curr->forward[0])
			{
				p = curr->forward[0]->slice;
				curr = curr->forward[0];
			}
			return p;
		}

		bool isEmpty()
		{
			if(curr->forward[0])
			{ 
				return false;
			}
			return true;
		}
	};

public:
	typedef List_Iterator iterator;
};
#endif // !SKIPLIST_H
