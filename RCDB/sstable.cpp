#include "sstable.h"


SSTable::SSTable(std::string file_url)
{
	this->file_url = file_url;
	this->index = new SSTableList;
	this->index->next = NULL;
	this->index_size = 0;
	
	//create file if not exist
	std::ofstream file(this->file_url, std::ios::binary | std::ios::app);
	file.close();

	readIdx();
	if (this->index_size == 0)
	{
		initIdx();
	}
}

SSTable::~SSTable()
{
	SSTableList *node = this->index->next;
	while (node)
	{
		SSTableList* re = node;
		node = node->next;
		if (re != NULL)
		{
			delete[] re->start;
			re->start = NULL;
			delete re;
			re = NULL;
		}
	}
	delete this->index;
}

bool SSTable::readIdx()
{
	std::ifstream file(this->file_url, std::ios::binary);
	if (!file)
	{
		return false;
	}

	file.read((char*)&this->index_size, sizeof(int));

	int start_index_length = 0;

	SSTableList* list = this->index;
	for (int i = 1; i <= this->index_size; i++)
	{
		file.read((char*)&start_index_length, sizeof(int));

		SSTableList* node = new SSTableList;
		node->next = NULL;

		node->start_length = start_index_length;
		node->start = new unsigned char[start_index_length];

		list->next = node;
		list = list->next;
	}

	list = this->index->next;
	for (int i = 0; i < this->index_size; i++)
	{
		char* start = new  char[list->start_length];

		file.read(start, list->start_length);
		file.read((char*)&list->filename, sizeof(int));
		memcpy(list->start, start, list->start_length);
		list = list->next;

		delete[] start;
	}

	

	file.close();
	return true;
}

bool SSTable::saveIdx()
{
	std::ofstream file(this->file_url, std::ios::binary);
	if (!file)
	{
		return false;
	}

 	file.write((char*)&this->index_size, sizeof(int));
	SSTableList* list = this->index;
	
	int start_index_length = 0;

	while (list != NULL)
	{
		start_index_length = list->start_length;

		file.write((char*)&start_index_length, sizeof(int));
		list = list->next;
	}
	list = this->index;
	while (list != NULL)
	{
		file.write((char*)list->start, list->start_length);
		file.write((char*)list->filename, sizeof(int));
		list = list->next;
	}
	file.close();
	return true;
}

bool SSTable::addInx(unsigned char* start, int start_length, unsigned char* filename, int file_length)
{
	SSTableList* node = new SSTableList;
	node->next = NULL;
	node->start = new unsigned char[start_length];
	node->start_length = start_length;
	memcpy(node->start, start, start_length);

	SSTableList* list = this->index;
	while (list->next = NULL)
	{
		if (compare(start, start_length, list->next->start, list->next->start_length) == 1)
		{
			list = list->next;
		}
		else
		{
			break;
		}
	}
	SSTableList* temp = list->next;
	list->next = node;
	node->next = temp;
	return true;
}

std::string SSTable::getFilename(unsigned char* start, int length)
{
	SSTableList* list = this->index;
	while (list->next)
	{
		if (isEqual(list->next->start, list->next->start_length, start, length))
		{
			break;
		}
		list = list->next;
	}
	if (list->next)
	{
		int file_ahead = list->next->filename;
		std::string file = std::to_string(file_ahead).append(".dat");
		return file;
	}
	return "";
}

int SSTable::getFilePrefix(unsigned char* start, int start_length)
{
	SSTableList* list = this->index;
	while (list->next)
	{
		if (isEqual(list->next->start, list->next->start_length, start, start_length))
		{
			break;
		}
		list = list->next;
	}
	int result = -1;
	if (list->next)
	{
		result = list->next->filename;
	}
	return result;
}

void SSTable::initIdx()
{
	std::ofstream file(this->file_url, std::ios::binary);
	if (!file)
	{
		return;
	}
	this->index_size = 255;
	file.write((char *)&this->index_size, sizeof(int));

	unsigned char* start = new unsigned char[2];
	const int length = sizeof(int);
	const int value = 2;

	for (int i = 0; i < this->index_size; i++)
	{
		file.write((char *)&value, length);
	}
	for (int i = 0; i < this->index_size; i++)
	{
		start[0] = i;
		start[1] = '\0';
		file.write((char *)start, 2);
		file.write((char *)&i, length);
	}
	file.close();
}


int SSTable::compare(unsigned char* a, int lenth_a, unsigned char* b, int lenth_b)
{
	int size = lenth_a;
	if (size > lenth_b)
	{
		size = lenth_b;
	}
	for (int i = 0; i < size; i++)
	{
		if (a[i] < b[i])
		{
			return -1;
		}
		if (a[i] > b[i])
		{
			return 1;
		}
	}
	if (lenth_a == lenth_b)
	{
		return 0;
	}
	if (lenth_a > lenth_b)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

bool SSTable::isEqual(unsigned char* start, int start_length, unsigned char* b, int length_b)
{
	int size = length_b;
	if (start_length < size)
	{
		size = start_length;
	}
	//避免比较文件结束符的0
	size = size - 1;
	for (int i = 0; i < size; i++)
	{
		int left = start[i];
		int right = b[i];
		if (left != right)
		{
			return false;
		}
	}
	return true;
}


SSTableList* SSTable::indexBegin()
{
	if (this->index != NULL)
	{
		return this->index;
	}
	return NULL;
}