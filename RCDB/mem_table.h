#ifndef MEM_TABLE_H
#define MEM_TABLE_H
#include "skiplist.h"
#include <fstream>
#include <thread>


class MemTable
{
public:
	MemTable(int level = 100, int mem_table_max = 1000, std::string mem_table_path = "./data/mem_table.dat");
	~MemTable();
	int put(unsigned char* key, int key_size, unsigned char* value, int value_size);
	Slice get(unsigned char* key, int key_size);
	
public:
	void saveMemtable();
	bool isTableFull();
	void setTableMutex();
private:
	bool current_table;

	SkipList *mem_table1;
	SkipList *mem_table2;

private:
	std::string mem_table_path;
	int level = level;
	int mem_table_max;
};
#endif // !MEM_TABLE_H
