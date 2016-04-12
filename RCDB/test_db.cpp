#include "db.h"


//用一个表来存批量操作，成功则push到磁盘，失败则丢弃
void main()
{
	Options p;
	p.mem_table_level = 100;
	p.mem_table_size = 5000;
	DB *db = new DB(p);

	const int size = 2;
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
	
	int test = 3;
	switch (test)
	{
	case 0:
		//test put and get
		for (int i = 0; i < size; i++)
		{
			bool result = db->put(key[i], 5, value[i], 5);
		}
		for (int i = 0; i < size; i++)
		{
			Slice s = db->get(key[i], 5);
		}
		break;
	case 1:
		//test put and delete
		for (int i = 0; i < size; i++)
		{
			bool result = db->put(key[i], 5, value[i], 5);
		}
		for (int i = 0; i < size; i++)
		{
			bool result = db->put(key[i], 5, NULL, 0);
		}
		for (int i = 0; i < size; i++)
		{
			Slice s = db->get(key[i], 5);
		}
		break;
	case 2:
		//test batchput and get
		for (int i = 0; i < size; i++)
		{
			bool result = db->batchPut(key[i], 5, value[i], 5);
		}
		for (int i = 0; i < size; i++)
		{
			Slice s = db->batchGet(key[i], 5);
		}
		break;
	case 3:
		//test batchput and delete
		for (int i = 0; i < size; i++)
		{
			bool result = db->batchPut(key[i], 5, value[i], 5);
		}
		for (int i = 0; i < size; i++)
		{
			bool result = db->batchPut(key[i], 5, NULL, 0);
		}
		for (int i = 0; i < size; i++)
		{
			Slice s = db->batchGet(key[i], 5);
		}
		db->writeBatch();

		for (int i = 0; i < size; i++)
		{
			Slice s = db->get(key[i], 5);
		}
		break;
	default:
		break;
	}

	



	

	
	
	//DB::db_iterator ita(p.compare, key[1], 5, p.path);
	//ita = db->dbBegin();

	//while (!ita.isTail())
	//{
	//	Slice s1 = ita.current();
	//	Slice s = ita.next();
	//}

	//while (!ita.isHead())
	//{
	//	Slice s = ita.pre();
	//}

	//DB::batch_iterator ita1;
	//ita1 = db->batchBegin();
	//while (!ita1.isTail())
	//{
	//	Slice s = ita1.next();
	//}

	//DB::mem_iterator ita2;
	//ita2 = db->memBegin();
	//while (!ita2.isTail())
	//{
	//	Slice slice = ita2.next();
	//}

	double s_1 = clock();
	for (int i = 0; i < 2; i++)
	{
		Cache* cache = db->createSnapshot();
	}
	double s_2 = clock();
	delete db;
	double s_3 = clock();

	int r1 = s_2 - s_1;
	int r2 = s_3 - s_2;
}