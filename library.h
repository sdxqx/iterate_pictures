#ifndef T_PATH_LIBRARY_H
#define T_PATH_LIBRARY_H

#include "./lib/utils/disk.h"

void hello();

// 获取磁盘对象
disk* getDiskObject(std::string os, callback _call);
int startGetImage(string os, callback _call);
int findByPathImage(string os, const string& path, callback _call);

#endif //T_PATH_LIBRARY_H
