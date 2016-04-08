#include "db.h"

DB::DB(Options option)
{
	this->cache = new Cache(option.path + option.index_name, option.path);
	this->mem_table = new MemTable(option.mem_table_level, option.mem_table_size, option.path + option.mem_table_name);
	this->filter = new SSTableFilter(option.mem_table_name, option.index_name, option.path);
	this->write_table_done = false;
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

Slice DB::get(unsigned char* key, int key_size)
{
	Slice slice;
	slice = this->mem_table->get(key, key_size);
	if (slice.getKeySize() == 0)
	{
		slice = this->cache->get(key, key_size);
	}
	return Slice(slice.getKey(), slice.getKeySize(), slice.getValue(), slice.getValueSize());
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
			this->filterData();
		}
	}
	return true;
}

bool DB::batchPut(unsigned char* key, int key_size, unsigned char* value, int value_size)
{
	if (this->mem_table_batch == NULL)
	{
		if (this->batch_result != NULL)
		{
			delete this->batch_result;
			this->batch_result = NULL;
		}
		this->mem_table_batch = new MemTable(100, INT_MAX);

		this->batch_result = new SliceList;
		this->batch_result->slice = Slice();
		this->batch_result->next = NULL;

		this->is_batch_success = true;
	}
	if (!this->is_batch_success)
	{
		return false;
	}
	int result = this->mem_table_batch->put(key, key_size, value, value_size);
	if (result == FAILED)
	{
		this->is_batch_success = false;
		return false;
	}
	return true;
}

bool DB::batchGet(unsigned char* key, int key_size)
{
	Slice slice;
	slice = this->mem_table->get(key, key_size);
	if (slice.getKeySize() == 0)
	{
		slice = this->cache->get(key, key_size);
	}
	if (slice.getKeySize() > 0)
	{
		SliceList* it = this->batch_result;
		while (it->next)
		{
			it = it->next;
		}

	}
}

void DB::writeBatch()
{

}


void DB::saveMemTable() 

{
	std::thread t1(&MemTable::saveMemtable, this->mem_table, &this->write_table_done);
	t1.join();
}

void DB::filterData()
{
	std::thread t2(&SSTableFilter::filter, this->filter, &this->write_table_done);
	t2.join();
}