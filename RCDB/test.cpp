#include "skiplist.h"
#include "helper.h"
int main()
{
	SkipList* list = new SkipList(4);

	for (int i = 0; i < 10; i++)
	{
		unsigned char key[4];
		unsigned char value[4];
		for (int i = 0; i < 3; i++)
		{
			key[i] = rand() % 25 + 65;
			value[i] = rand() % 25 + 65;
		}
		key[3] = '\0';
		value[3] = '\0';
		bool a = list->insertNode(key, 4, value, 4);
	}
	list->printList();
	delete list;
	return 1;
}

