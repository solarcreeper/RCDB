#include "snapshot.h"

Snapshot::Snapshot(Options option)
{
	this->data_path = option.path;
	this->snapshot_path = option.snapshot_path;
}

Snapshot::~Snapshot()
{
	if (this->db)
	{
		delete this->db;
		this->db = NULL;
	}
}

void Snapshot::create()
{

}

void destroy(std::string version)
{

}

