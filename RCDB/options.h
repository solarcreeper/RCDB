#ifndef OPTIONS_H
#define OPTIONS_H
#include <string>

class Options
{
public:
	Options(int memtable_level = 100,
		int mem_table_size = 1000,
		std::string path = "./data/",
		std::string mem_table_name = "mem_table.dat",
		std::string index_name = "data_index.dat");

	~Options();

public:
	int mem_table_level;
	int mem_table_size;
	std::string path;
	std::string mem_table_name;
	std::string index_name;
};
#endif // !OPTIONS_H
