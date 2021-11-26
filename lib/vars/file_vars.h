//
// Created by Master on 2021/10/15.
//

#ifndef T_PATH_FILE_VARS_H
#define T_PATH_FILE_VARS_H

#include <functional>
#include <thread>

using namespace std;

#if defined(__cplusplus) && __cplusplus >= 201703L && defined(__has_include)
    #if __has_include(<filesystem>)
        #define GHC_USE_STD_FS
        #include <filesystem>
        namespace fs = std::filesystem;
    #endif
#endif
#ifdef GHC_USE_STD_FS
    #include <ghc/filesystem.hpp>
    namespace fs = ghc::filesystem;
#endif


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__) || defined(WIN64)
const string __system = "windows";
#else
const string __system = "linux";
#endif

// 扇区
struct disk_var {
    string diskName;
};

// 扇区列表
struct disk_vars {
    int size = 0;
    struct disk_var *diskVar;
};


// 文件
struct file_vars {
    std::string fileName;
    std::string filePath;
    std::string fileType = "txt";

    // 图片尺寸 大小
    float fileSize = 0.00;
    float fileWidth = 0.00;
    float fileHeight = 0.00;
};

// 进程池
struct threads {
    int index;
    thread *callback;
};

typedef std::function<void(file_vars)> callback;
typedef void thread_call(string name, ...);

#endif //T_PATH_FILE_VARS_H
