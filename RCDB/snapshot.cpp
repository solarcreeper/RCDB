#include "snapshot.h"

Snapshot::Snapshot(Options option)
{
	this->option = option;
	this->list = new SnapshotList;
	this->list->cache = NULL;
	this->list->next = NULL;
	this->version = 0;
	File().createDir(option.snapshot_path);
}

Snapshot::~Snapshot()
{
	while (list->next)
	{
		SnapshotList* s = list->next;
		list = list->next;
		//delete file

		SSTable* index_file = s->cache->getTable();
		std::string del_path = s->cache->getBlockPath();
		SSTable::index_iterator ita;
		ita = index_file->indexBegin();
		while (!ita.isTail())
		{
			std::string file = del_path + ita.next();
			File().removeFile(file);
		}

		File().removeFile(del_path + option.index_name);
		File().removeFile(del_path + option.mem_table_name);
		File().removeDir(del_path);
		delete s->cache;
		s->cache = NULL;
	}
	delete list;

	File().removeDir(option.snapshot_path);
}

Cache* Snapshot::create(SSTable* index_file)
{
	File().createDir(option.snapshot_path + std::to_string(version));
	SSTable::index_iterator ita;
	ita = index_file->indexBegin();
	while (!ita.isTail())
	{
		std::string file = ita.next();
		std::string input_file = option.path + file;
		std::string output_file = option.snapshot_path + std::to_string(version) + "/" + file;
		std::ifstream input(input_file, std::ios::binary);

		if (input)
		{
			std::ofstream output(output_file, std::ios::binary);
			output << input.rdbuf();
			output.close();
		}
		input.close();
	}

	std::string input_file = option.path + option.index_name;
	std::string output_file = option.snapshot_path + std::to_string(version) + "/" + option.index_name;
	std::ifstream input(input_file, std::ios::binary);
	std::ofstream output(output_file, std::ios::binary);

	output << input.rdbuf();
	input.close();
	output.close();

	Options p;
	p.path = option.snapshot_path + std::to_string(this->version) + "/";

	Cache* cache = new Cache(p.path + p.index_name, p.path);
	SnapshotList* node = new SnapshotList;
	node->cache = cache;
	node->next = NULL;

	SnapshotList* it = this->list;
	while (it->next)
	{
		it = it->next;
	}
	it->next = node;
	
	this->version++;
	return cache;
}
