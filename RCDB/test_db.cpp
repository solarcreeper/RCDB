#include "db.h"

//用一个表来存批量操作，成功则push到磁盘，失败则丢弃
void main()
{
	Options p;
	p.mem_table_level = 100;
	p.mem_table_size = 5000;
	DB *db = new DB(p);

	const int size = 10;
	unsigned char key[size][5];
	unsigned char value[size][5];
	for (int i = 0; i < size; i++)
	{

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
		db->put(key[i], 5, value[i], 5);
		std::cout << i << std::endl;
	}
	double end1 = clock();
	int total1 = end1 - start;

	for (int i = 0; i < size; i++)
	{
		db->get(key[i], 5);
	}
	double end2 = clock();
	delete db;
	int total2 = end2 - end1;


}