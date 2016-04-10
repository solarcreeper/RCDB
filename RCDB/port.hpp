#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined (_WIN64)
	#include <direct.h>  
#endif
#if defined(__unix__) || defined(__APPLE__)
    #include <sys/stat.h>
    #include <unistd.h>
#endif
#include <string>

namespace port{
int createDir(std::string dir) {
    int ret = -1;
#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
    // TODO
    ret = _mkdir(dir.c_str());
#endif

#if defined (__unix__) || defined(__APPLE__)
    ret = mkdir(dir.c_str(), 0755);
#endif
    return ret;
}

int removeDir(std::string dir) {
    int ret = -1;
#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
    // TODO
     ret = _rmdir(dir.c_str());
#endif

#if defined(__unix__) || defined(__APPLE__)
    ret = rmdir(dir.c_str());
#endif
    return ret;
}
} // namespace port