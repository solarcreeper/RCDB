#include "db.h"

void main()
{
	Options p;
	p.mem_table_level = 1;
	p.mem_table_size = 1;
	DB *db = new DB(p);

	unsigned char* key = new unsigned char[5];
	unsigned char* value = new unsigned char[5];
	key[0] = value[0] = 'A';
	key[1] = value[1] = 'A';
	key[2] = value[2] = 'A';
	key[3] = value[3] = 'A';
	key[4] = value[4] = '\0';

	db->put(key, 5, value, 5);

	key[0] = value[0] = 'B';
	key[1] = value[1] = 'B';
	key[2] = value[2] = 'B';
	key[3] = value[3] = 'B';
	key[4] = value[4] = '\0';
	db->put(key, 5, value, 5);

	Slice slice = db->get(key, 5);
}