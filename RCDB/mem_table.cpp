#include "mem_table.h"

MemTable::MemTable()
{
	this->mem_table1 = new SkipList(100);
	this->mem_table2 = new SkipList(100);
	this->size = 0;
	this->current_table = true;
}

MemTable::~MemTable()
{
	if (this->mem_table1 != NULL)
	{
		delete this->mem_table1;
		this->mem_table1 = NULL;
	}
	if (this->mem_table2 != NULL)
	{
		delete this->mem_table2;
		this->mem_table2 = NULL;
	}
}

int MemTable::put(unsigned char* key, int key_size, unsigned char* value, int value_size)
{
	SkipList* table = this->mem_table1;
	if (!this->current_table)
	{
		table = this->mem_table2;
	}
	int result = -1;
	if (value_size == 0)
	{
		result = table->deleteNode(key, key_size);
	}
	else
	{
		result = table->insertNode(key, key_size, value, value_size);
	}
	if (result == INSERT_VALUE_SUCCESS)
	{
		this->size++;
		if (this->size == MAX)
		{
			//当一个表存满了之后
			this->current_table = !this->current_table;
			this->size = 0;
			/*delete table;
			table = NULL;
			table = new SkipList(100);*/
		}
	}
	if (result == DELETE_VALUE_SUCCESS)
	{
		this->size--;
	}
	return result;
}

unsigned char* MemTable::get(unsigned char* key, int key_size)
{
	if (this->current_table)
	{
		unsigned char* result = this->mem_table1->searchNode(key, key_size);
		if (result == NULL)
		{
			return this->mem_table2->searchNode(key, key_size);
		}
		else
		{
			return result;
		}
	}
	else {
		unsigned char* result = this->mem_table2->searchNode(key, key_size);
		if (result == NULL)
		{
			return this->mem_table1->searchNode(key, key_size);
		}
		else {
			return result;
		}
	}
}