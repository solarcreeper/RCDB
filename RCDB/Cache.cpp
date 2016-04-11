#include "cache.h"

Cache::Cache(std::string sstable_url, std::string sstable_block_path)
{
	this->sstable_url = sstable_url;
	this->sstable_block_path = sstable_block_path;
	this->curr_block = 0;
	for (int i = 0; i < CACHE_SIZE; i++)
	{
		this->cache_block[i] = NULL;
	}
	this->cache_index = new SSTable(this->sstable_url);
	this->cache_index->readIdx();
}

Cache::~Cache()
{
	if (this->cache_index != NULL)
	{
		delete this->cache_index;
		this->cache_index = NULL;
	}

	for (int i = 0; i < CACHE_SIZE; i++)
	{
		if (this->cache_block[i] != NULL)
		{
			delete cache_block[i];
			cache_block[i] = NULL;
		}
	}
}

Slice Cache::get(int(*compare)(unsigned char* key, int key_size, unsigned char* value, int value_size), unsigned char* key, int key_size)
{
	std::string filename = this->cache_index->getFilename(key, key_size);

	Slice result;
	result = this->getFormCache(compare, key, key_size, filename);
	if (result.getKey() == 0)
	{
		result = this->getFromFile(compare, key, key_size, filename);
	}
	return Slice(result.getKey(), result.getKeySize(), result.getValue(), result.getValueSize());
}

int Cache::isInCache(std::string filename)
{
	for (int i = 0; i < CACHE_SIZE; i++)
	{
		if (this->cache_block[i] != NULL)
		{
			if (filename == this->cache_block[i]->getFilename())
			{
				return i;
			}
		}
	}
	return -1;
}

Slice Cache::getFormCache(int(*compare)(unsigned char* key, int key_size, unsigned char* value, int value_size), unsigned char* key, int key_size, std::string filename)
{
	int block_index = this->isInCache(filename);
	if (block_index == -1)
	{
		return Slice();
	}
	SkipList* block_data = cache_block[block_index]->getBlock();
	Slice result;
	result = block_data->searchNode(compare, key, key_size);
	return Slice(result.getKey(), result.getKeySize(), result.getValue(), result.getValueSize());
}

Slice Cache::getFromFile(int(*compare)(unsigned char* key, int key_size, unsigned char* value, int value_size), unsigned char* key, int key_size, std::string filename)
{
	this->reloadBlock(compare, curr_block, filename);
	SkipList* block_data = cache_block[curr_block]->getBlock();
	Slice result;
	result = block_data->searchNode(compare, key, key_size);

	this->curr_block++;
	if (this->curr_block == CACHE_SIZE)
	{
		this->curr_block = 0;
	}

	return Slice(result.getKey(), result.getKeySize(), result.getValue(), result.getValueSize());
}

void Cache::reloadIndex()
{
	if (this->cache_index != NULL)
	{
		delete this->cache_index;
		this->cache_index = NULL;
	}
	this->cache_index = new SSTable(this->sstable_url);
	this->cache_index->readIdx();
	return;
}

void Cache::reloadBlock(int(*compare)(unsigned char* key, int key_size, unsigned char* value, int value_size), int curr_block, std::string filename)
{
	if (cache_block[curr_block] != NULL)
	{
		delete cache_block[curr_block];
		cache_block[curr_block] = NULL;
	}

	cache_block[curr_block] = new SSTableBlock(filename, this->sstable_block_path);
	cache_block[curr_block]->readBlock(compare);
	return;
}

SSTable* Cache::getTable()
{
	if (this->cache_index)
	{
		return this->cache_index;
	}
	return NULL;
}