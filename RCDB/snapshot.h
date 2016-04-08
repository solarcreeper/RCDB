#ifndef SNAPSHOT_H
#define SNAPSHOT_H
#include <string>
#include "db.h"
#include "options.h"

class Snapshot {
public:
	Snapshot(Options option);
	~Snapshot();

	void create();
	void destroy(std::string version);
	void get(unsigned char* key, int key_sise);
private:
	void read(std::string date);

private:
	DB* db;

	std::string data_path;
	std::string snapshot_path;
};
#endif // !SNAPSHOT_H
