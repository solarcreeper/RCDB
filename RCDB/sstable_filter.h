#ifndef SSTABLE_FILTER_H
#define SSTABLE_FILTER_H
#include "sstable.h"
#include "sstable_block.h"
#include "skiplist.h"

class SSTableFilter
{
public:
	SSTableFilter(std::string data_file = "mem_table.dat", std::string index_file = "data_index.dat", std::string path = "./data");
	~SSTableFilter();

	void filter();
private:
	SSTableBlock* data_to_save;
	SSTable* index_table;
	SSTableBlock* block;

private:
	std::string path;
};
#endif // !SSTABLE_FILTER_H
