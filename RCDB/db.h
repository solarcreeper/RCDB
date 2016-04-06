#ifndef DB_H
#define DB_H
#include "cache.h"
#include "mem_table.h"
#include "sstable_filter.h"
#include "options.h"

class DB
{
public:
	DB(Options option = Options());
	~DB();

	Slice get(unsigned char* key, int key_size);
	bool put(unsigned char* key, int key_size, unsigned char* value, int value_size);

private:
	void saveMemTable();
	void filterData();
private:
	Cache* cache;
	MemTable* mem_table;
	SSTableFilter* filter;
private:
	Slice slice;
	bool write_table_done;

};

#endif // !DB_H

