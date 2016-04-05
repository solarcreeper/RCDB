#ifndef SSTABLE_FILTER_H
#define SSTABLE_FILTER_H
#include "sstable.h"
#include "sstable_block.h"
#include "skiplist.h"

class SSTableFilter
{
public:
	SSTableFilter();
	~SSTableFilter();

	void readTable();

	
private:
	SkipList* list;
	SSTable* table;
	SSTableBlock* block;
};
#endif // !SSTABLE_FILTER_H
