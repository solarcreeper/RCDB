#include "sstable.h"
#include <time.h>
void main()
{
	srand(time(0));
	SSTable* table = new SSTable;
	
	//unsigned char* filename = new unsigned char[3];
	unsigned char* start = new unsigned char[2];
	//for (int i = 0; i < 100; i++)
	//{
	//	for (int m = 0; m < 2; m++)
	//	{
	//		filename[m] = rand() % 25 + 65;
	//		start[m] = rand() % 25 + 65;
	//	}
	//	filename[2] = '\0';
	//	start[2] = '\0';
	//	//table->addInx(start, 3, filename, 3);
	//}
	table->readIdx();
	//table->saveIdx();
	start[0] = 1;
	start[1] = '\0';
	table->getFilename(start, 2);
	return;
}