#include "skiplist.h"

Skiplist::Skiplist() 
{
	seed = time(NULL);
	list_header = new SkiplistNode;
	list_level = 0;
	list_header->slice = Slice();

	for (int i = 0; i < MAX_LEVEL; i++) 
	{
		list_header->forward[i] = NULL;
	}
}

Skiplist::~Skiplist()
{
	delete list_header;
}

int Skiplist::getInsertLevel()
{
	int up_count = 1;
	for (int i = 0; i < MAX_LEVEL; i++)
	{
		int num = getRand(0, 10);
		if (num < 5)
		{
			up_count++;
		}
	}
	return --up_count;
}

unsigned char* Skiplist::searchNode(unsigned char* key, int key_size)
{
	SkiplistNode* current = new SkiplistNode;
	current = list_header;
	for (int i = list_level - 1; i >= 0; i--)
	{
		while (current->forward[i] != NULL)
		{
			if (compare(key, key_size, current->forward[i]->slice.getKey(), current->forward[i]->slice.getKeySize()) == 0)
			{
				return current->forward[i]->slice.getValue();
			}
			current = current->forward[i];
		}
	}
	return NULL;
}


bool Skiplist::insertNode(unsigned char* key, int key_size, unsigned char* value, int value_size)
{
	

	SkiplistNode* update[MAX_LEVEL];
	SkiplistNode* current = new SkiplistNode;
	current = list_header;
	//从最底层查找需要插入的位置，并将位置写入update
	for (int i = 0; i < MAX_LEVEL; i++)
	{
		while (current->forward[i] != NULL && compare(key, key_size, current->forward[i]->slice.getKey(), current->forward[i]->slice.getKeySize()) == 1)
		{
			current = current->forward[i];
		}
		update[i] = current;
	}

	//不能插入相同的值
	if (current->forward[0] != NULL && isEqual(current->forward[0]->slice.getKey(), key))
	{
		std::string out_key((char*)key);
		std::cout << std::endl;
		std::cout << "insert key:" << out_key << " already existed" << std::endl;
		return false;
	}
	//生成一个随机高度
	int level = getInsertLevel();
	SkiplistNode* node = new SkiplistNode;
	node->slice = Slice(key, key_size, value, value_size);

	//更新跳表的高度
	if (level > this->list_level)
	{
		for (int i = this->list_level; i <= level; i++)
		{
			update[i] = this->list_header;
		}
		this->list_level = level;
	}

	//逐层更新节点的指针
	for (int i = 0; i <= level; i++)
	{
		node->forward[i] = update[i]->forward[i];
		update[i]->forward[i] = node;
	}
	return true;
}

bool Skiplist::deleteNode(unsigned char* key, int key_size)
{
	SkiplistNode* update[MAX_LEVEL];
	SkiplistNode* current = new SkiplistNode;
	current = this->list_header;

	for (int i = 0; i < this->list_level; i++)
	{
		while (current->forward[i] != NULL && compare(key, key_size, current->forward[i]->slice.getKey(), current->forward[i]->slice.getKeySize()) == 1)
		{
			current = current->forward[i];
		}
		update[i] = current;
	}

	//开始删除
	if (current->forward[0] != NULL && isEqual(current->forward[0]->slice.getKey(), key))
	{
		for (int i = 0; i < this->list_level; i++)
		{
			if (isEqual(update[i]->forward[i]->slice.getKey(), current->slice.getKey()))
			{
				update[i]->forward[i] = current->forward[i];
			}
		}
		delete current;

		for (int i = 0; i < this->list_level; i++)
		{
			if (this->list_header->forward[i] == NULL)
			{
				this->list_level--;
			}
		}
		return true;
	}
	else
	{
		std::string out_key((char*)key);
		std::cout << "delete key:" << out_key << "does not exited" << std::endl;
		return false;
	}
}

void Skiplist::printList()
{
	SkiplistNode* current = list_header;
	for (int i = list_level; i >= 0; i--)
	{
		current = list_header;
		std::cout << "************level-" << i << "******************" << std::endl;
		while (current->forward[i] != NULL)
		{
			unsigned char* key = current->forward[i]->slice.getKey();
			unsigned char* value = current->forward[i]->slice.getValue();
			std::string key_s((char*)key);
			std::string value_s((char*)value);
			std::cout << key_s << ":" << value_s << "   ";
			current = current->forward[i];
		}
		std::cout << std::endl;
	}
}

int Skiplist::getRand(int min, int max)
{
	srand(seed);
	seed = rand();
	return (min + rand() % (max - min + 1));
}


int Skiplist::compare(unsigned char* a, int lenth_a, unsigned char* b, int lenth_b)
{
	std::string s_a((char*)a);
	std::string s_b((char*)b);
	if (s_a == s_b) return 0;
	int size = lenth_a;
	if (size > lenth_b)
	{
		size = lenth_b;
	}
	
	for (int i = 0; i < size; i++) {
		if (a[i] > b[i])
		{
			return 1;
		}
	}
	return -1;
}

bool Skiplist::isEqual(unsigned char* a, unsigned char* b)
{
	std::string s_a((char*)a);
	std::string s_b((char*)b);
	if (s_a == s_b)
	{
		return true;
	}
	return false;
}