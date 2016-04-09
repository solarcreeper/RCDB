#include "db.h"

//用一个表来存批量操作，成功则push到磁盘，失败则丢弃
void main()
{
	Options p;
	p.mem_table_level = 100;
	p.mem_table_size = 5000;
	DB *db = new DB(p);

	const int size = 10;
	unsigned char* key[size];
	unsigned char* value[size];
	for (int i = 0; i < size; i++)
	{
		key[i] = new unsigned char[5];
		value[i] = new unsigned char[5];

		for (int m = 0; m < 4; m++)
		{
			key[i][m] = rand() % 25 + 65;
			value[i][m] = rand() % 25 + 65;
		}
		key[i][4] = '\0';
		value[i][4] = '\0';
	}

	double start = clock();
	for (int i = 0; i < size; i++)
	{
		//db->batchPut(key[i], 5, value[i], 5);
		db->put(key[i], 5, value[i], 5);
		std::string s((char*)key[i]);
		std::cout << s << std::endl;
	}
	double end1 = clock();
	int total1 = end1 - start;

	Slice s;
	for (int i = 0; i < size; i++)
	{
		//s = db->batchGet(key[i], 5);
		s = db->get(key[i], 5);
	}
	//db->writeBatch();

	DB::batch_iterator ita1;
	ita1 = db->batchBegin();
	while (!ita1.isEmpty())
	{
		Slice s = ita1.next();
	}

	DB::iterator ita;
	ita = db->begin();
	while (!ita.isEmpty())
	{
		Slice slice = ita.next();
	}
	double end2 = clock();
	delete db;
	int total2 = end2 - end1;
}