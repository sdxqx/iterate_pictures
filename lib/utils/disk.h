//
// Created by Master on 2021/10/15.
//

#ifndef T_PATH_DISK_H
#define T_PATH_DISK_H

#include <string>
#include <utility>
#include <filesystem>
#include <io.h>
#include <dirent.h>
#include <iostream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__) || defined(WIN64)
#else
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#define MAX_PATH_LEN (256)
#endif



#include "../utils/process/process.h"
#include "../utils/Image/ImageFile.h"

class disk {
    public:
        string os = "windows";
        callback _call;
        disk_var dsv;

        disk(string os, callback _call) {
            this -> os = move(os);
            this -> _call = move(_call);
        }

        int start() {
            this -> getDisk();
            return 1;
        };

        int findByPathImage(string path) {
            thread(disk::getAllFiles, path, "", this).join();
            return 1;
        }
    protected:
        file_vars load_image_file(string file) {
            ImageFile imageFile;
            if (imageFile.readFile(file, file)) {
                this -> _call(imageFile.fs);
            }
            return imageFile.fs;
        };

        int getDisk() {
            if (this -> os == "windows") {
                return getWindowsDisk();
            } else {
                thread(disk::getAllFiles, "/", "", this).join();
            }
            return 1;
        };

        /**
         * 获取所有盘符
         * @return disk_vars
         */
        int getWindowsDisk() {
            int i = 0;
            string rootPath = "";
            for (char disk = 'A'; disk <= 'Z'; disk++, i++) {
                rootPath.append(1, disk);
                rootPath.append(":\\");
                bool bExists = opendir(rootPath.c_str());
                if (bExists) {
                    this -> dsv.diskName = rootPath;
                     thread(disk::getAllFiles, rootPath, "", this).join();
                }
                rootPath = "";
            }
            return 1;
        }

        //获取所有的文件名
        static void getAllFiles(string path, string files, disk *_disk)
        {
            #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__) || defined(WIN64)
                long  hFile = 0;
                //文件信息
                struct _finddata_t fileinfo;
                string p;

                string dim = _disk -> os == "windows" ? "\\" : "/";

                if ((hFile = _findfirst(p.assign(path).append("*").c_str(), &fileinfo)) != -1) {
                    do {
                        if ((fileinfo.attrib &  _A_SUBDIR)) {
                            // 查询子目录
                            if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
                                //files.push_back(p.assign(path).append("\\").append(fileinfo.name));  // 存入目录
                                thread(disk::getAllFiles, p.assign(path).append(dim).append(fileinfo.name).append(dim), files, _disk).join();
                            }
                        } else {
                            _disk -> load_image_file(p.assign(path).append(dim).append(fileinfo.name));
                        }
                    } while (_findnext(hFile, &fileinfo) == 0);
                    _findclose(hFile);
                }
            #else
                DIR *d = NULL;
                struct dirent *dp = NULL;
                struct stat st;
                char p[MAX_PATH_LEN] = {0};

                if(stat(path.c_str(), &st) < 0 || !S_ISDIR(st.st_mode)) {
                    return;
                }

                if(!(d = opendir(path.c_str()))) {
                    return;
                }

                while((dp = readdir(d)) != NULL) {
                    if((!strncmp(dp->d_name, ".", 1)) || (!strncmp(dp->d_name, "..", 2)))
                        continue;

                    stat(p, &st);
                    if(!S_ISDIR(st.st_mode)) {
                        _disk -> load_image_file(dp->d_name);
                    } else {
                        thread(disk::getAllFiles, dp->d_name, files, _disk).join();
                    }
                }
                closedir(d);
            #endif
        }
};


#endif //T_PATH_DISK_H
