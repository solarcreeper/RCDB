#ifndef  HELPER_H
#define HELPER_H
#include "skiplist.h"
#include <fstream>

class Helper {
public:
	static void printListToFile(const Skiplist& list, const char* filenme);
private:

};
#endif // ! HELPER_H
