#include "sstable_block.h"
#define PATH "./data/"

SSTableBlock::SSTableBlock(std::string filename)
{
	this->filename = PATH + filename;
	this->list_node = new SSTableBlockNode;
	this->list_node->next = NULL;
	this->block = new SkipList(50);
	this->size = 0;

	//create file if not exist
	std::ofstream file(this->filename, std::ios::binary | std::ios::app);
	file.close();
}

SSTableBlock::~SSTableBlock()
{
	while (this->list_node->next)
	{
		delete this->list_node->next;
		this->list_node->next = NULL;
		this->list_node = this->list_node->next;
	}
	delete this->list_node;
	this->list_node = NULL;
}

void SSTableBlock::readBlock()
{
	std::ifstream file(this->filename, std::ios::binary);
	if (!file)
	{
		return;
	}

	file.read((char*)&this->size, sizeof(int));

	SSTableBlockNode* list = this->list_node;
	int key_value_length = sizeof(int);
	for (int i = 0; i < this->size; i++)
	{
		SSTableBlockNode* node = new SSTableBlockNode;
		file.read((char*)&node->key_size, key_value_length);
		file.read((char*)&node->value_size, key_value_length);
		list->next = node;
		list = list->next;
	}

	list = this->list_node->next;
	for (int i = 0; i < this->size; i++)
	{
		char* key = new char[list->key_size];
		char* value = new char[list->value_size];
		
		file.read(key, list->key_size);
		file.read(value, list->value_size);

		this->block->insertNode((unsigned char*)key, list->key_size, (unsigned char*)value, list->value_size);
		
		delete[] key;
		delete[] value;
		list = list->next;
	}
	return;
}

void SSTableBlock::saveBlock()
{
	std::ofstream file(this->filename, std::ios::binary);
	if (!file)
	{
		return;
	}
	int length = sizeof(int);
	file.write((char*)&this->size, length);

	SkipList::iterator ita;
	ita = block->Begin();
	while (!ita.isEmpty())
	{
		Slice slice = ita.next();
		if (!slice.isDeleted())
		{
			file.write((char*)slice.getKeySize(), length);
			file.write((char*)slice.getValueSize(), length);
		}
	}
	ita = block->Begin();
	while (!ita.isEmpty())
	{
		Slice slice = ita.next();
		if (!slice.isDeleted())
		{
			file.write((char*)slice.getKey(), slice.getKeySize());
			file.write((char*)slice.getValue(), slice.getValueSize());
		}
	}
	file.close();
	return;
}

int SSTableBlock::addRecord(Slice slice)
{
	int result = -1;
	if (!slice.isDeleted())
	{
		result = this->block->deleteNode(slice.getKey(), slice.getKeySize());
	}
	else
	{
		result = this->block->insertNode(slice.getKey(), slice.getKeySize(), slice.getValue(), slice.getValueSize());
	}
	if (result == INSERT_VALUE_SUCCESS)
	{
		this->size++;
	}
	if (result == DELETE_VALUE_SUCCESS)
	{
		this->size--;
	}
	return result;
}
