#include "library.h"

#include <iostream>


disk *_disk = nullptr;

void hello() {
    cout << "Hello, World!" << endl;
}

disk* getDiskObject(string os, callback _call) {
    if (_disk != nullptr) return _disk;
    _disk = new  disk(move(os), move(_call));
    return _disk;
}

/**
 * 扫描全盘目录
 * @param os
 * @param _call
 * @return
 */
int startGetImage(string os, callback _call) {
    _disk = getDiskObject(move(os), move(_call));
    return _disk -> start();
}

/**
 * 查询指定文件夹图片
 * @param os
 * @param path
 * @param _call
 * @return
 */
int findByPathImage(string os, const string& path, callback _call = nullptr) {
    _disk = getDiskObject(move(os), move(_call));
    return _disk -> start();
}
