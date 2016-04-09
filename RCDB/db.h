#ifndef DB_H
#define DB_H
#include "cache.h"
#include "mem_table.h"
#include "sstable_filter.h"
#include "options.h"
#include "slicelist.h"

class DB
{
public:
	DB(Options option = Options());
	~DB();

	Slice get(unsigned char* key, int key_size);
	bool put(unsigned char* key, int key_size, unsigned char* value, int value_size);
	
public:
	bool batchPut(unsigned char* key, int key_size, unsigned char* value, int value_size);
	Slice batchGet(unsigned char* key, int key_size);
	bool writeBatch();
	
public:
	SkipListNode* begin();
	SliceListNode* batchBegin();
private:
	void saveData();

private:
	Cache* cache;
	MemTable* mem_table;
	MemTable* mem_table_batch;
	SSTableFilter* filter;

private:
	SliceList* batch_result;

private:
	bool write_table_done;
	bool is_batch_success;

public:
	typedef SkipList::iterator iterator;
	typedef SliceList::iterator batch_iterator;
};

#endif // !DB_H

