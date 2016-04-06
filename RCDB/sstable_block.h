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
	SSTableBlock(std::string filename, std::string path = "./data/");
	~SSTableBlock();

	void readBlock();
	void saveBlock();
	int addRecord(Slice& slice);
	std::string getFilename();

public:
	void readMemTable();
	SkipList* getBlock();

private:
	SSTableBlockNode* list_node;
	SkipList* block;
	int size;
private:
	std::string filename;
	std::string file_url;
 };
#endif // !SSTABLE_BLOCK_H
