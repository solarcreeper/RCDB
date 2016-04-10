#include "port.hpp"


void main()
{
	int result = port::createDir("./test1");
	result = port::removeDir("./test1");
}