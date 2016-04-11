#include "file.h"

void main()
{
	
	int reult = File().createDir("./test");
	reult = File().removeFile("./test/test.txt");

}