#ifndef SSTABLE_BLOCK_H
#define SSTABLE_BLOCK_H
#include "skiplist.h"
#include <fstream>

struct SSTableBlockNode
{
	int key_size;
	int value_size;

	SSTableBlockNode* next;
};

class SSTableBlock
{
public:
	SSTableBlock(std::string filename);
	~SSTableBlock();

	void readBlock();
	void saveBlock();
	int addRecord(Slice slice);

private:
	SSTableBlockNode* list_node;
	SkipList* block;
	int size;
	std::string filename;
	

 };
#endif // !SSTABLE_BLOCK_H
