#ifndef MEM_TABLE_H
#define MEM_TABLE_H
#include "skiplist.h"
#include <fstream>

#define MAX 2

class MemTable
{
public:
	MemTable();
	~MemTable();
	int put(unsigned char* key, int key_size, unsigned char* value, int value_size);
	unsigned char* get(unsigned char* key, int key_size);
	
public:
	void saveMemtable();

private:
	bool current_table;

	SkipList *mem_table1;
	SkipList *mem_table2;
};
#endif // !MEM_TABLE_H
