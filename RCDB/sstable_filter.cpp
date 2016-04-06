#include "sstable_filter.h"

SSTableFilter::SSTableFilter(std::string data_file = "mem_table.dat", std::string index_file = "data_index.dat", std::string path = "./data/")
{
	this->path = path;
	this->data_to_save = new SSTableBlock(data_file, path);
	this->data_to_save->readMemTable();

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

void SSTableFilter::filter()
{
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

}




