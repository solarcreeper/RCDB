#ifndef SNAPSHOT_H
#define SNAPSHOT_H
#include <string>
#include "cache.h"
#include "file.h"
#include "options.h"

struct SnapshotList
{
	Cache* cache;
	SnapshotList* next;
};

class Snapshot {
public:
	Snapshot(Options option);
	~Snapshot();

	Cache* create(SSTable* index_file);

private:
	SnapshotList* list;
	Options option;
	int version;
};
#endif // !SNAPSHOT_H
