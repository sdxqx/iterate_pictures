cmake_minimum_required(VERSION 3.19)
project(t_path)

set(CMAKE_CXX_STANDARD 14)

add_library(t_path SHARED library.cpp library.h lib/utils/disk.cpp lib/utils/disk.h lib/vars/file_vars.h lib/utils/process/process.cpp lib/utils/process/process.h lib/utils/LoadImageInfo.h lib/utils/Image/ImageFile.cpp lib/utils/Image/ImageFile.h)