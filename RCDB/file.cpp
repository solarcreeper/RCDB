#include "file.h"

int File::createDir(std::string dir)
{
	int ret = -1;
#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
	ret = _mkdir(dir.c_str());
#endif

#if defined (__unix__) || defined(__APPLE__)
	ret = mkdir(dir.c_str(), 0755);
#endif
	return ret;
}

int File::removeDir(std::string dir)
{
	int ret = -1;
#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
	ret = _rmdir(dir.c_str());
#endif

#if defined(__unix__) || defined(__APPLE__)
	ret = rmdir(dir.c_str());
#endif
	return ret;
}

int File::removeFile(std::string file_url)
{
	int ret = -1;
#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
	ret = _unlink(file_url.c_str());
#endif

#if defined(__unix__) || defined(__APPLE__)
	ret = unlink(file_url.c_str());
#endif
	return ret;
}