#include "db.h"

void test();

int main()
{
	test();

	Options p;
	p.setOptions(100, 5000, "./data1/", "./snapshot1/");
	DB *db = new DB(p);



	const int size = 4;
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

	db->batchPut( key[2], 5, value[2], 5);
	Slice s = db->batchGet(key[2], 5);
	db->writeBatch();
	s = db->get(key[2], 5);
	return 0;
}

void test()
{
	Options p;
	p.setOptions(100, 5000, "./data1/", "./snapshot1/");
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
	
	int test = 2;
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

	
		DB::db_iterator ita;
		ita.init(db->dbBegin(), p.compare, key[1], 5, p.getDataSavePath());

		while (!ita.isTail())
		{
			Slice s1 = ita.current();
			Slice s = ita.next();
		}

		while (!ita.isHead())
		{
			Slice s = ita.pre();
		}

		DB::batch_iterator ita1;
		ita1.init(db->batchBegin());
		while (!ita1.isTail())
		{
			Slice s = ita1.next();
		}

		DB::mem_iterator ita2;
		ita2.init(db->memBegin());
		while (!ita2.isTail())
		{
			Slice slice = ita2.next();
		}

	double s_1 = clock();
	for (int i = 0; i < 2; i++)
	{
		Cache* cache = db->createSnapshot();
		Slice s = cache->get(p.compare, key[1], 5);
	}
	double s_2 = clock();
	delete db;
	db = NULL;
	double s_3 = clock();

	int r1 = s_2 - s_1;
	int r2 = s_3 - s_2;

	for (int i = 0; i < size; i++)
	{
		delete[] key[i];
		delete[] value[i];
	}
}