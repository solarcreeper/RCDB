#include "db.h"

DB::DB(Options option)
{
	this->cache = new Cache(option.getDataSavePath() + option.getIndexName(), option.getDataSavePath());
	this->mem_table = new MemTable(option.getMemTableLevel(), option.getMemTableSize(), option.getDataSavePath() + option.getMemTableName());
	this->filter = new SSTableFilter(option.getMemTableName(), option.getIndexName(), option.getDataSavePath());
	this->write_table_done = false;
	this->option = option;
	this->snapshot = new Snapshot(option);
	this->mem_table_batch = NULL;
	this->batch_result = NULL;
}

DB::~DB()
{
	this->saveData();

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
	if (this->snapshot)
	{
		delete this->snapshot;
		this->snapshot = NULL;
	}
}

Slice DB::get(unsigned char* key, int key_size)
{
	Slice slice;
	slice = this->mem_table->get(this->option.compare, key, key_size);
	if (slice.getKeySize() == 0 && (!slice.isDeleted()))
	{
		slice = this->cache->get(this->option.compare, key, key_size);
	}
	if (slice.isDeleted())
	{
		return Slice();
	}
	return Slice(slice.getKey(), slice.getKeySize(), slice.getValue(), slice.getValueSize());
}

bool DB::put(unsigned char* key, int key_size, unsigned char* value, int value_size)
{
	int result = this->mem_table->put(this->option.compare, key, key_size, value, value_size);
	if (result == INSERT_VALUE_SUCCESS || result == DELETE_VALUE_SUCCESS)
	{
		if (this->mem_table->isTableFull())
		{
			this->mem_table->setTableMutex();
			this->saveData();
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
		std::string mem_url = option.getDataSavePath() + option.getMemTableName();
		this->mem_table_batch = new MemTable(100, INT_MAX, mem_url);
		this->batch_result = new SliceList;
		this->is_batch_success = true;
	}
	if (!this->is_batch_success)
	{
		return false;
	}
	int result = this->mem_table_batch->put(this->option.compare, key, key_size, value, value_size);
	if (result == FAILED)
	{
		this->is_batch_success = false;
		return false;
	}
	return true;
}

Slice DB::batchGet(unsigned char* key, int key_size)
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
		this->is_batch_success = true;
	}
	Slice slice;
	slice = this->mem_table_batch->get(this->option.compare, key, key_size);
	if (slice.getKeySize() == 0 && (!slice.isDeleted()))
	{
		slice = this->mem_table->get(this->option.compare, key, key_size);
	}

	if (slice.getKeySize() == 0 && (!slice.isDeleted()))
	{
		slice = this->cache->get(this->option.compare, key, key_size);
	}

	if (slice.getKeySize() > 0 && (!slice.isDeleted()))
	{
		this->batch_result->add(slice);
		return Slice(slice.getKey(), slice.getKeySize(), slice.getValue(), slice.getValueSize());
	}
	return Slice();
}

bool DB::writeBatch()
{
	if (is_batch_success)
	{
		std::thread t1(&MemTable::saveMemtable, this->mem_table_batch, &this->write_table_done);
		t1.join();
		std::thread t2(&SSTableFilter::filter, this->filter, this->option.compare, &this->write_table_done);
		t2.join();
	}
	else
	{
		delete mem_table_batch;
	}
	return this->is_batch_success;
}

void DB::printList()
{
	this->mem_table->getTable()->printList();
}
void DB::printListToFile()
{
	this->mem_table->getTable()->printListToFile("./data/test.txt");
}


void DB::saveData()
{
	std::thread t1(&MemTable::saveMemtable, this->mem_table, &this->write_table_done);
	t1.join();
	std::thread t2(&SSTableFilter::filter, this->filter, this->option.compare, &this->write_table_done);
	t2.join();
}

SkipListNode* DB::memBegin()
{
	return this->mem_table->getTable()->Begin();
}

SliceListNode* DB::batchBegin()
{
	if (this->batch_result)
	{
		return this->batch_result->Begin();
	}
	return NULL;
}

SSTable* DB::dbBegin()
{
	//save data before iterator start
	this->saveData();
	if (this->cache)
	{
		return this->cache->getTable();
	}
	return NULL;
}

Options DB::getOption()
{
	return this->option;
}

SSTable* DB::getSSTable()
{
	return this->cache->getTable();
}

Cache* DB::createSnapshot()
{
	this->saveData();
	return this->snapshot->create(this->cache->getTable());
}