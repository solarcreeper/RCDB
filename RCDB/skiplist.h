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
	FAILED = 99,
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
	public:
		void operator =(SkipListNode* ptr)
		{
			curr = ptr;
			head = ptr;
		}

		Slice pre()
		{
			if (curr == head || head->forward[0] == curr)
			{
				curr = head;
				return Slice();
			}
			
			Slice p;
			SkipListNode* it = head->forward[0];
			while (it->forward[0] != curr)
			{
				it = it->forward[0];
			}
			p = it->slice;
			curr = it;
			return Slice(p.getKey(), p.getKeySize(), p.getValue(), p.getValueSize());
		}

		Slice next()
		{
			Slice p;
			if (curr->forward[0])
			{
				p = curr->forward[0]->slice;
				curr = curr->forward[0];
			}
			return Slice(p.getKey(), p.getKeySize(), p.getValue(), p.getValueSize());
		}

		Slice current()
		{
			Slice p;
			if (curr->slice.getKey() > 0)
			{
				p = curr->slice;
			}
			return Slice(p.getKey(), p.getKeySize(), p.getValue(), p.getValueSize());
		}

		bool isEmpty()
		{
			if (curr == NULL)
			{
				return true;
			}

			if(curr->forward[0])
			{ 
				return false;
			}
			return true;
		}

		bool isHead()
		{
			if (curr == head || head->forward[0] == curr )
			{
				return true;
			}
			return false;
		}
	};

public:
	typedef List_Iterator iterator;
};
#endif // !SKIPLIST_H
