#ifndef  FILE_H
#define FILE_H
#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined (_WIN64)
#include <direct.h>  
#endif
#if defined(__unix__) || defined(__APPLE__)
#include <sys/stat.h>
#include <unistd.h>
#endif
#include <string>

class File
{
public:
	static int createDir(std::string dir);
	static int removeDir(std::string dir);
	static int removeFile(std::string file_url);
};

#endif // ! FILE_H
