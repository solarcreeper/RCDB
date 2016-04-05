#include "mem_table.h"

MemTable::MemTable()
{
	this->mem_table1 = new SkipList(100);
	this->mem_table2 = new SkipList(100);
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
		if (table->getSize() == MAX)
		{
			this->current_table = !this->current_table;
			//new thread to save 
			saveMemtable();
		}
	}
	return result;
}

unsigned char* MemTable::get(unsigned char* key, int key_size)
{
	if (this->current_table)
	{
		unsigned char* result = this->mem_table1->searchNode(key, key_size).getValue();
		if (result == NULL)
		{
			return this->mem_table2->searchNode(key, key_size).getValue();
		}
		else
		{
			return result;
		}
	}
	else {
		unsigned char* result = this->mem_table2->searchNode(key, key_size).getValue();
		if (result == NULL)
		{
			return this->mem_table1->searchNode(key, key_size).getValue();
		}
		else {
			return result;
		}
	}
}

void MemTable::saveMemtable()
{
	std::ofstream file("./data/mem_table.dat", std::ios::binary);
	if (!file)
	{
		return;
	}
	SkipList* table = this->mem_table1;
	if (this->current_table)
	{
		table = this->mem_table2;
	}

	int length = sizeof(int);
	int size = table->getSize();
	file.write((char*)&size, length);

	SkipList::iterator ita;
	ita = table->Begin();
	while (!ita.isEmpty())
	{
		Slice slice;
		slice = ita.next();
		int key_size = slice.getKeySize();
		int value_size = slice.getValueSize();
		file.write((char*)&key_size, length);
		file.write((char*)&value_size, length);
	}
	ita = table->Begin();
	while (!ita.isEmpty())
	{
		Slice slice;
		slice = ita.next();
		bool is_deleted = slice.isDeleted();
		unsigned char* key = new unsigned char[slice.getKeySize()];
		unsigned char* value = new unsigned char[slice.getValueSize()];
		memcpy(key, slice.getKey(), slice.getKeySize());
		memcpy(value, slice.getValue(), slice.getValueSize());

		file.write((char*)key, slice.getKeySize());
		file.write((char*)value, slice.getValueSize());
		file.write((char*)&is_deleted, sizeof(bool));

		delete[] key;
		delete[] value;
	}
	file.close();

	if (!this->current_table)
	{
		delete this->mem_table1;
		mem_table1 = new SkipList(100);
	}
	else
	{
		delete this->mem_table2;
		mem_table2 = new SkipList(100);
	}
	return;
}