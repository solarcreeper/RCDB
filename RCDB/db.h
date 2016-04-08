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
	
	bool batchPut(unsigned char* key, int key_size, unsigned char* value, int value_size);
	bool batchGet(unsigned char* key, int key_size);
	void writeBatch();
	
private:
	void saveMemTable();
	void filterData();

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

};

#endif // !DB_H

