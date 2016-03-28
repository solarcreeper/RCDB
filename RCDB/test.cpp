#include "skiplist.h"
#include "helper.h"
int main()
{
	char* filename = "out.txt";
	const int value = 9;
	unsigned char key1[3] = {'y', 'e', '\0'};
	unsigned char value1[value] = {'2', '0', '1', '2', '1', '9', '3', '1','\0'};
	unsigned char key2[4] = { 'l', 'z', 'y' };
	unsigned char value2[value] = { '2', '0', '1', '2', '1', '9', '5', '8', '\0' };
	
	Skiplist list;
	list.insertNode(key1, 3, value1, value);
	list.printList();
	//Helper().printListToFile(list, filename);
	unsigned char* result = list.searchNode(key1, 3);
	bool result1 = list.insertNode(key2, 4, value2, value);
	//Helper().printListToFile(list, filename);
	list.printList();
	bool result2 = list.insertNode(key2, 4, value2, value);
	//Helper().printListToFile(list, filename);
	list.printList();
	return 1;
}

