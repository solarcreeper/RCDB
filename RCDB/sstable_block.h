#ifndef SSTABLE_BLOCK_H
#define SSTABLE_BLOCK_H
#include "skiplist.h"
#include "slice.h"
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

	void readBlock(int(*compare)(unsigned char* key, int key_size, unsigned char* value, int value_size));
	void saveBlock();
	int addRecord(int(*compare)(unsigned char* key, int key_size, unsigned char* value, int value_size), Slice& slice);
	std::string getFilename();

public:
	void readMemTable(int(*compare)(unsigned char* key, int key_size, unsigned char* value, int value_size));
	SkipList* getBlock();

	int(*compare)(unsigned char* key, int key_size, unsigned char* value, int value_size);

private:
	SSTableBlockNode* list_node;
	SkipList* block;
	int size;
private:
	std::string filename;
	std::string file_url;
 };
#endif // !SSTABLE_BLOCK_H
