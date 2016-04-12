#include "SkipList.h"

SkipList::SkipList(int max_level)
{
	this->seed = time(NULL);
	this->size = 0;
	srand(seed);
	this->max_level = max_level;
	this->header = new SkipListNode;
	this->header->forward = new SkipListNode*[this->max_level];
	for (int level = 0; level < this->max_level; level++)
	{
		this->header->forward[level] = NULL;
	}
}

SkipList::~SkipList()
{
	while (this->header)
	{
		SkipListNode* node = this->header;
		this->header = this->header->forward[0];
		if (node->forward != NULL)
		{
			delete[] node->forward;
			node->forward = NULL;
		}
		if (node != NULL)
		{
			delete node;
			node = NULL;
		}
	}
	delete this->header;
	this->header = NULL;
}

int SkipList::insertNode(int(*compare)(unsigned char* key, int key_size, unsigned char* value, int value_size), unsigned char* key, int key_size, unsigned char* value, int value_size, bool is_deleted)
{
	SkipListNode** update = new SkipListNode*[this->max_level];
	SkipListNode* current = this->header;
	for (int i = this->max_level - 1; i >= 0; --i)
	{
		SkipListNode* next = NULL;
		while ((next = current->forward[i]) && (this->compare(compare, key, key_size, next->slice.getKey(), next->slice.getKeySize()) == 1))
		{
			current = next;
		}
		update[i] = current;
	}

	bool is_find = (update[0]->forward[0] && this->compare(compare, update[0]->forward[0]->slice.getKey(), update[0]->forward[0]->slice.getKeySize(), key, key_size) == 0);
	int result = FAILED;
	if (!is_find)
	{
		SkipListNode* node = new SkipListNode;
		node->slice = Slice(key, key_size, value, value_size, is_deleted);
		int node_level = this->getLevel(1, this->max_level);

		node->forward = new SkipListNode*[node_level];
		for (int i = 0; i < node_level; i++)
		{
			node->forward[i] = update[i]->forward[i];
			update[i]->forward[i] = node;
		}
		result = INSERT_VALUE_SUCCESS;
		this->size++;
	}
	else
	{
		update[0]->forward[0]->slice.setValue(value, value_size);
		result = MODIFY_VALUE_SUCCESS;
	}
	delete[] update;
	return result;
}

int SkipList::insertNode(int(*compare)(unsigned char* key, int key_size, unsigned char* value, int value_size), unsigned char* key, int key_size, unsigned char* value, int value_size)
{
	SkipListNode** update = new SkipListNode*[this->max_level];
	SkipListNode* current = this->header;
	for (int i = this->max_level - 1; i >= 0; --i)
	{
		SkipListNode* next = NULL;
		while ((next = current->forward[i]) && (this->compare(compare, key, key_size, next->slice.getKey(), next->slice.getKeySize()) == 1))
		{
			current = next;
		}
		update[i] = current;
	}

	bool is_find = (update[0]->forward[0] && this->compare(compare, update[0]->forward[0]->slice.getKey(), update[0]->forward[0]->slice.getKeySize(), key, key_size) == 0);
	int result = FAILED;
	if (!is_find)
	{
		SkipListNode* node = new SkipListNode;
		node->slice = Slice(key, key_size, value, value_size);
		int node_level = this->getLevel(1, this->max_level);
		 
		node->forward = new SkipListNode*[node_level];
		for (int i = 0; i < node_level; i++)
		{
			node->forward[i] = update[i]->forward[i];
			update[i]->forward[i] = node;
		}
		result = INSERT_VALUE_SUCCESS;
		this->size++;
	}
	else 
	{
		update[0]->forward[0]->slice.setValue(value, value_size);
		result = MODIFY_VALUE_SUCCESS;
	}
	delete[] update;
	return result;
}

int SkipList::deleteNode(int(*compare)(unsigned char* key, int key_size, unsigned char* value, int value_size), unsigned char* key, int key_size)
{
	SkipListNode** update = new SkipListNode*[this->max_level];
	for (int i = this->max_level - 1; i >= 0; i--)
	{
		SkipListNode* current = this->header;
		SkipListNode* next = NULL;
		while ((next = current->forward[i]) && (this->compare(compare, key, key_size, next->slice.getKey(), next->slice.getKeySize()) == 1))
		{
			current = next;
		}
		update[i] = current;
	}

	bool is_find = (update[0]->forward[0] && this->compare(compare, update[0]->forward[0]->slice.getKey(), update[0]->forward[0]->slice.getKeySize(), key, key_size) == 0);
	int result = FAILED;
	if (is_find)
	{
		if (update[0]->forward[0]->slice.isDeleted())
		{
			result= DELETE_VALUE_FAILED;
		}
		else
		{
			update[0]->forward[0]->slice.delValue();
			result = DELETE_VALUE_SUCCESS;
		}
	}
	else {
		//Êä³öÐÅÏ¢
		result = DELETE_VALUE_FAILED;
	}
	delete[] update;
	return result;
}

Slice SkipList::searchNode(int(*compare)(unsigned char* key, int key_size, unsigned char* value, int value_size), unsigned char* key, int key_size)
{
	SkipListNode* current = this->header;
	for (int i = this->max_level - 1; i >= 0; i--)

	{
		SkipListNode* next = NULL;
		while ((next = current->forward[i]) && this->compare(compare, key, key_size, next->slice.getKey(), next->slice.getKeySize()) == 1)
		{
			current = next;
		}
		if (next && this->compare(compare, next->slice.getKey(), next->slice.getKeySize(), key, key_size) == 0)
		{
			return Slice(next->slice.getKey(), next->slice.getKeySize(), next->slice.getValue(), next->slice.getValueSize(), next->slice.isDeleted());
		}
	}
	return Slice();
}



void SkipList::printList()
{
	SkipListNode* current = this->header;
	for (int i = this->max_level - 1; i >= 0; i--)
	{
		SkipListNode* next = current->forward[i];
		std::cout << "************level-" << i << "******************" << std::endl;
		while (next != NULL)
		{
			std::cout << next->slice.getKey() << "->" << next->slice.getValue() << "  ";
			next = next->forward[i];
		}
		std::cout << std::endl;
	}
}

void SkipList::printListToFile(const char* filename)
{
	std::ofstream out(filename, std::ios::app);
	SkipListNode* current = this->header;
	out << "****************************************************************\n";
	for (int i = this->max_level - 1; i >= 0; i--)
	{
		SkipListNode* next = current->forward[i];
		out << "************level-" << i << "******************\n";
		out << "*  ";
		while (next != NULL)
		{
			out << next->slice.getKey() << "->" << next->slice.getValue() << "  ";
			next = next->forward[i];
		}
		out << "\n";
	}
	out << "****************************************************************\n\n\n";
	out.close();
}

int SkipList::getSize()
{
	return this->size;
}

SkipListNode* SkipList::Begin()
{
	return this->header;
}

int SkipList::getLevel(int min, int max)
{
	//srand(seed);
	seed = rand();
	return (min + rand() % (max - min + 1));
}


int SkipList::compare(int(*compare)(unsigned char* key, int key_size, unsigned char* value, int value_size), unsigned char* a, int lenth_a, unsigned char* b, int lenth_b)
{
	if (compare != NULL)
	{
		return compare(a, lenth_a, b, lenth_b);
	}

	int size = lenth_a;
	if (size > lenth_b)
	{
		size = lenth_b;
	}
	for (int i = 0; i < size; i++)
	{
		if (a[i] < b[i])
		{
			return -1;
		}
		if (a[i] > b[i])
		{
			return 1;
		}
	}
	if (lenth_a == lenth_b)
	{
		return 0;
	}
	if (lenth_a > lenth_b) 
	{
		return 1;
	}
	else
	{
		return -1;
	}
}