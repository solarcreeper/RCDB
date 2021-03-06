#include "sstable_filter.h"

SSTableFilter::SSTableFilter(std::string data_file, std::string index_file, std::string path)
{
	this->path = path;
	this->data_file = data_file;
	this->data_to_save = NULL;
	this->block = NULL;
	this->index_table = new SSTable(path + index_file);
}

SSTableFilter::~SSTableFilter()
{
	if (this->data_to_save)
	{
		delete this->data_to_save;
		this->data_to_save = NULL;
	}

	if (this->index_table)
	{
		delete this->index_table;
		this->index_table = NULL;
	}

	if (this->block)
	{
		delete this->block;
		this->block = NULL;
	}
}

void SSTableFilter::filter(int(*compare)(unsigned char* key, int key_size, unsigned char* value, int value_size), bool* write_table_done)
{
	while (!*write_table_done)
	{
		//just wait
	}
	if (this->data_to_save = NULL)
	{
		delete this->data_to_save;
		this->data_to_save = NULL;
	}
	this->data_to_save = new SSTableBlock(data_file, path);
	this->data_to_save->readMemTable(compare);

	SkipList::iterator ita;
	SkipList* block = this->data_to_save->getBlock();
	ita.init(block->Begin());
	std::string last_index = "";
	int file_prefix = -1;
	while (!ita.isTail())
	{
		Slice slice;
		slice = ita.next();
		file_prefix = index_table->getFilePrefix(slice.getKey(), slice.getKeySize());
		std::string file_index = std::to_string(file_prefix).append(".dat");
		if (last_index == "" || file_index != last_index)
		{
			//need to change the data block
			if (this->block)
			{
				this->block->saveBlock();
				delete this->block;
				this->block = NULL;
			}
			this->block = new SSTableBlock(file_index, this->path);
			this->block->readBlock(compare);
			last_index = file_index;
		}
		int add_result = this->block->addRecord(compare, slice);
	}

	//save the last part of data and release handle
	if (this->block)
	{
		this->block->saveBlock();
		delete this->block;
		this->block = NULL;
	}
	*write_table_done = false;
}




