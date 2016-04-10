#ifdef _WIN32  
#include <direct.h>  
#elif _LINUX  
#include <stdarg.h>  
#include <sys/stat.h>  
#endif  

//#ifdef _WIN32  
//#define ACCESS _access  
//#define MKDIR(a) _mkdir((a))  
//#elif _LINUX  
//#define ACCESS access  
//#define MKDIR(a) mkdir((a),0755)  
//#endif  

#include <string>
//
//int create(std::string s)
//{
//	int ret = _mkdir(s.c_str());
//	return ret;
//}