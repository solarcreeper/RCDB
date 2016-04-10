#ifndef CACHE_H
#define CACHE_H
#include "sstable_block.h"
#include "sstable.h"
#define CACHE_SIZE 256
class Cache
{
public:
	Cache(std::string sstable_url = "./data/data_index.dat", std::string sstable_block_path = "./data/");
	~Cache();

	Slice get(unsigned char* key, int key_size);

public:
	SSTable* getTable();

private:
	SSTableBlock* cache_block[CACHE_SIZE];
	SSTable* cache_index;
	int curr_block;

private:
	Slice getFormCache(unsigned char* key, int key_size, std::string filename);
	Slice getFromFile(unsigned char* key, int key_size, std::string filename);

	void reloadIndex();
	void reloadBlock(int curr_block, std::string filename);
	int isInCache(std::string filename);

private:
	std::string sstable_url;
	std::string sstable_block_path;

};

#endif // !CACHE_H
