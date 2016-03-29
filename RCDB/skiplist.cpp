#include "SkipList.h"

SkipList::SkipList(int max_level) : header(NULL), size(0), max_level(max_level)
{
	this->seed = time(NULL);
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
		delete[] node->forward;
		delete node;
	}
}

bool SkipList::insertNode(unsigned char* key, int key_size, unsigned char* value, int value_size)
{
	SkipListNode** update = new SkipListNode*[this->max_level];
	SkipListNode* current = this->header;
	for (int i = this->max_level - 1; i >= 0; --i)
	{
		SkipListNode* next = NULL;
		while ((next = current->forward[i]) && (compare(key, key_size, next->slice.getKey(), next->slice.getKeySize()) == 1))
		{
			current = next;
		}
		update[i] = current;
	}

	bool is_find = (update[0]->forward[0] && compare(update[0]->forward[0]->slice.getKey(), update[0]->forward[0]->slice.getKeySize(), key, key_size) == 0);
	if (!is_find)
	{
		SkipListNode* node = new SkipListNode;
		node->slice = Slice(key, key_size, value, value_size);
		int node_level = this->getLevel(1, 4);
		if (node_level > this->max_level)
		{
			node_level = this->max_level;
		}
		node->forward = new SkipListNode*[node_level];
		for (int i = 0; i < node_level; i++)
		{
			node->forward[i] = update[i]->forward[i];
			update[i]->forward[i] = node;
		}
		this->size++;
	}
	else 
	{
		//输入错误
	}
	delete[] update;
	return !is_find;
}

bool SkipList::deleteNode(unsigned char* key, int key_size)
{
	SkipListNode** update = new SkipListNode*[this->max_level];
	for (int i = this->max_level - 1; i >= 0; i--)
	{
		SkipListNode* current = this->header;
		SkipListNode* next = NULL;
		while ((next = current->forward[i]) && (compare(key, key_size, next->slice.getKey(), next->slice.getKeySize()) == 1))
		{
			current = next;
		}
		update[i] = current;
	}

	bool is_find = (update[0]->forward[0] && compare(update[0]->forward[0]->slice.getKey(), update[0]->forward[0]->slice.getKeySize(), key, key_size) == 0);
	if (is_find)
	{
		SkipListNode* find_node = update[0]->forward[0];
		for (int i = 0; i < this->max_level; i++)
		{
			if (update[i]->forward[i] == find_node)
			{
				update[i]->forward[i] = find_node->forward[i];
			}
			else
			{
				break;
			}
		}
		
		delete[] find_node->forward;
		delete find_node;
		this->size--;
		return true;
	}
	else {
		//输出信息
		return false;
	}
}

unsigned char* SkipList::searchNode(unsigned char* key, int key_size)
{
	SkipListNode* current = this->header;
	for (int i = this->max_level - 1; i >= 0; i--)
	{
		SkipListNode* next = NULL;
		while ((next = current->forward[i]) && compare(key, key_size, next->slice.getKey(), next->slice.getKeySize()) == 1)
		{
			current = next;
		}
		if (next && compare(next->slice.getKey(), next->slice.getKeySize(), key, key_size) == 0)
		{
			return next->slice.getValue();
		}
	}
	return NULL;
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


}

int SkipList::getLevel(int min, int max)
{
	srand(seed);
	seed = rand();
	return (min + rand() % (max - min + 1));
}


int SkipList::compare(unsigned char* a, int lenth_a, unsigned char* b, int lenth_b)
{
	std::string s_a((char*)a);
	std::string s_b((char*)b);
	if (s_a == s_b) return 0;
	int size = lenth_a;
	if (size > lenth_b)
	{
		size = lenth_b;
	}
	bool flag = 0;
	for (int i = 0; i < size; i++) {
		if (a[i] == b[i])
		{
			flag++;
		}
		if (a[i] > b[i] && flag == i)
		{
			return 1;
		}
		
	}
	return -1;
}

bool SkipList::isEqual(unsigned char* a, unsigned char* b)
{
	std::string s_a((char*)a);
	std::string s_b((char*)b);
	if (s_a == s_b)
	{
		return true;
	}
	return false;
}
