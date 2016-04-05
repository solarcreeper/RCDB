#include "skiplist.h"

int main()
{
	srand(time(0));
	const int size = 5;
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

	SkipList* list = new SkipList(4);
	double start = clock();
	for (int i = 0; i < size; i++)
	{
		list->insertNode(key[i], 5, value[i], 5);
	}
	double end1 = clock();
	int total1 = end1 - start;

	for (int i = 0; i < size; i++)
	{
		list->searchNode(key[i], 5);
	}
	double end2 = clock();
	int total2 = end2 - end1;

	list->printList();
	SkipList::iterator ita;
	ita = list->Begin();
	Slice a;
	while (!ita.isEmpty())
	{
		a = ita.next();
	}

	return 1;
}

