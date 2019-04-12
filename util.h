#ifndef __UTIL_H__
#define __UTIL_H__

#include <QString>

//100 Days of Code
namespace HDC {

    class Utility {
    public:
        static QString GetAbsolutePath(const std::string& path);
        static QString GetAbsolutePath(const char * path);
        static QString GetAbsolutePath(const QString& path);
        
    };
}



#endif //__UTIL_H__