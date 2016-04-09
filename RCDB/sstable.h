#ifndef SSTABLE_H
#define SSTABLE_H
#include <iostream>
#include <fstream>
#include <string>
struct SSTableList
{
	unsigned char* start;
	int filename;
	int start_length;

	SSTableList* next;
};


class SSTable
{
public:
	SSTable(std::string file_url = "./data/data_index.dat");
	~SSTable();

	bool readIdx();
	bool saveIdx();
	bool addInx(unsigned char* start, int start_length, unsigned char* filename, int file_length);
	std::string getFilename(unsigned char* start, int start_length);
private:
	SSTableList* index;
	int index_size;
	std::string file_url;

private:
	void initIdx();
	int compare(unsigned char* a, int lenth_a, unsigned char* b, int lenth_b);
	bool isEqual(unsigned char* start, int start_length, unsigned char* b, int length_b);

private:
	class Index_Iterator
	{
		SSTableList* curr;
		SSTableList* head;

	public: 
		void operator =(SSTableList* ptr)
		{
			curr = ptr;
			head = ptr;
		}

		std::string pre()
		{
			std::string result = "";
			if (curr == head || head->next == curr)
			{
				curr = head;
				return result;
			}
			SSTableList* it = head->next;
			while (it->next != curr)
			{
				it = it->next;
			}
			result = std::to_string(it->filename).append(".dat");
			curr = it;
			return result;
		}

		std::string next()
		{
			std::string result = "";
			if (curr->next)
			{
				result = std::to_string(curr->filename).append(".dat");
				curr = curr->next;
			}
			return result;
		}

		bool isEmpty()
		{
			if (curr == NULL)
			{
				return true;
			}

			if (curr->next)
			{
				return false;
			}
			return true;
		}
	};
public:
	typedef Index_Iterator index_iterator;

};
#endif // !SSTABLE_H
