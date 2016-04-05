#include "mem_table.h"
int main()
{
	srand(1);
	const int size = 100;
	unsigned char key[size][5];
	unsigned char value[size][5];
	MemTable* table = new MemTable();
	for (int j = 0; j < 1; j++)
	{
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
			int reult = table->put(key[i], 5, value[i], 5);
		}
		double end1 = clock();
		int total1 = end1 - start;

		for (int i = 0; i < size; i++)
		{
			unsigned char* value_result = table->get(key[i], 5);
		}
		double end2 = clock();
		int total2 = end2 - end1;
	}

	return 1;
}

