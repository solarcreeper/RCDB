#ifndef OPTIONS_H
#define OPTIONS_H
#include <string>
#include "file.h"

class Options
{
public:
	Options();
		
	~Options();
	void setOptions(int memtable_level = 100,
		int mem_table_size = 1000,
		std::string path = "./data/",
		std::string snapshot_path = "./snapshot/",
		int(*compare)(unsigned char* key, int key_size, unsigned char* value, int value_size) = NULL);

	int getMemTableLevel();
	int getMemTableSize();
	std::string getDataSavePath();
	std::string getSnapshotPath();
	std::string getIndexName();
	std::string getMemTableName();

	int(*compare)(unsigned char* key, int key_size, unsigned char* value, int value_size);

private:
	int mem_table_level;
	int mem_table_size;
	std::string path;
	std::string mem_table_name;
	std::string index_name;
	std::string snapshot_path;
};
#endif // !OPTIONS_H
