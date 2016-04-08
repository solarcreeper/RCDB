#include "mem_table.h"

MemTable::MemTable(int level, int mem_table_max, std::string mem_table_path)
{
	this->mem_table_path = mem_table_path;
	this->level = level;
	this->mem_table_max = mem_table_max;
	this->mem_table1 = new SkipList(level);
	this->mem_table2 = new SkipList(level);
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
	int result = FAILED;
	if (value_size == 0)
	{
		result = table->deleteNode(key, key_size);
	}
	else
	{
		result = table->insertNode(key, key_size, value, value_size);
	}
	return result;
}

Slice MemTable::get(unsigned char* key, int key_size)
{
	Slice slice;
	if (this->current_table)
	{
		slice = this->mem_table1->searchNode(key, key_size);
		if (slice.getKeySize() == 0)
		{
			Slice s = this->mem_table2->searchNode(key, key_size);
			return Slice(s.getKey(),s.getKeySize(),s.getValue(),s.getValueSize());
		}
		else
		{
			return Slice(slice.getKey(), slice.getKeySize(), slice.getValue(), slice.getValueSize());
		}
	}
	else {
		slice = this->mem_table2->searchNode(key, key_size);
		if (slice.getKeySize() == 0)
		{
			Slice s = this->mem_table1->searchNode(key, key_size);
			return Slice(s.getKey(), s.getKeySize(), s.getValue(), s.getValueSize());
		}
		else {
			return Slice(slice.getKey(), slice.getKeySize(), slice.getValue(), slice.getValueSize());
		}
	}
}

void MemTable::saveMemtable(bool* write_table_done)
{
	if (!this->current_table)
	{
		if (this->mem_table2)
		{
			delete this->mem_table2;
			this->mem_table2 = NULL;
		}
		mem_table2 = new SkipList(this->level);
	}
	else
	{
		if (this->mem_table1)
		{
			delete this->mem_table1;
			this->mem_table1 = NULL;
		}
		mem_table1 = new SkipList(this->level);
	}

	std::ofstream file(this->mem_table_path, std::ios::binary);
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
	
	*write_table_done = true;
	return;
}

bool MemTable::isTableFull()
{
	if (current_table)
	{
		return (mem_table1->getSize() == this->mem_table_max);
	}
	return (mem_table2->getSize() == this->mem_table_max);
}

void MemTable::setTableMutex()
{
	this->current_table = !this->current_table;
}