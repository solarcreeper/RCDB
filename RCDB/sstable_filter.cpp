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

void SSTableFilter::filter(bool* write_table_done)
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
	this->data_to_save->readMemTable();

	SkipList::iterator ita;
	SkipList* block = this->data_to_save->getBlock();
	ita = block->Begin();
	std::string last_index = "";
	while (!ita.isEmpty())
	{
		Slice slice;
		slice = ita.next();
		std::string file_index = index_table->getFilename(slice.getKey(), slice.getKeySize());
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
			this->block->readBlock();
			last_index = file_index;
		}
		int add_result = this->block->addRecord(slice);
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




