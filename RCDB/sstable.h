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
	SSTable();
	~SSTable();

	bool readIdx();
	bool saveIdx();
	bool addInx(unsigned char* start, int start_length, unsigned char* filename, int file_length);
	std::string getFilename(unsigned char* start, int start_length);
private:
	SSTableList* index;
	int index_size;

private:
	void initIdx();
	int compare(unsigned char* a, int lenth_a, unsigned char* b, int lenth_b);
	bool isEqual(unsigned char* start, int start_length, unsigned char* b, int length_b);
};
#endif // !SSTABLE_H
