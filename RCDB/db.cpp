#include "db.h"

DB::DB(Options option)
{
	this->cache = new Cache(option.path + option.index_name, option.path);
	this->mem_table = new MemTable(option.mem_table_level, option.mem_table_size, option.path + option.mem_table_name);
	this->filter = new SSTableFilter(option.mem_table_name, option.index_name, option.path);
}

DB::~DB()
{
	if (this->cache)
	{
		delete this->cache;
		this->cache = NULL;
	}
	if (this->mem_table)
	{
		delete this->mem_table;
		this->mem_table = NULL;
	}
	if (this->filter)
	{
		delete this->filter;
		this->filter = NULL;
	}
}

unsigned char* DB::get(unsigned char* key, int key_size)
{
	slice = this->mem_table->get(key, key_size);
	if (slice.getKeySize() == 0)
	{
		slice = this->cache->get(key, key_size);
	}
	return slice.getValue();
}

bool DB::put(unsigned char* key, int key_size, unsigned char* value, int value_size)
{
	int result = this->mem_table->put(key, key_size, value, value_size);
	if (result == INSERT_VALUE_SUCCESS)
	{
		if (this->mem_table->isTableFull())
		{
			this->mem_table->setTableMutex();
			this->saveMemTable();
		}
	}
}

void DB::saveMemTable()
{
	std::thread t1(&MemTable::saveMemtable, this->mem_table);
	t1.join();
}