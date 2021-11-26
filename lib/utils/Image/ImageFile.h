//
// Created by Master on 2021/10/17.
//

#ifndef T_PATH_IMAGEFILE_H
#define T_PATH_IMAGEFILE_H

#include <fstream>
#include <cstring>
#include "../../vars/file_vars.h"

#define JPEG_FILE_TYPE          1
#define BMP_FILE_TYPE           2
#define PNG_FILE_TYPE           3
#define GIF_FILE_TYPE           4


class ImageFile {
    public:
        file_vars fs;
        void getImageType (unsigned char *buff, int size) {
            int type = checkFileType(buff);
            int i;
            switch (type) {
                case JPEG_FILE_TYPE:
                    for(i = 0; i < size ; i++)
                    {
                        if(buff[i] == 0xff && buff[i+1] == 0xc0)
                        {
                            this -> fs.fileWidth = (buff[i+7]<<8) | buff[i+8];
                            this -> fs.fileHeight = (buff[i+5]<<8) | buff[i+6];
                            break;
                        }
                    }
                    this -> fs.fileType = "jpg";
                    break;

                case BMP_FILE_TYPE:
                    for(i = 0; i < size ; i++)
                    {
                        if(buff[i] == 0x28 && buff[i+1] == 0x00)
                        {
                            this -> fs.fileWidth = (buff[i+7]<<24) | buff[i+6]<<16 | buff[i+5]<<8 | buff[i+4];
                            this -> fs.fileHeight = (buff[i+11]<<24) | buff[i+10]<<16 | buff[i+9]<<8 | buff[i+8];
                            break;
                        }
                    }
                    this -> fs.fileType = "bmp";
                    break;

                case PNG_FILE_TYPE:
                    for(i = 0; i < size ; i++)
                    {
                        if(buff[i] == 0x49 && buff[i+1] == 0x48)
                        {
                            this -> fs.fileWidth = (buff[i+8]<<24) | buff[i+9]<<16 | buff[i+10]<<8 | buff[i+11];
                            this -> fs.fileHeight = (buff[i+4]<<24) | buff[i+5]<<16 | buff[i+6]<<8 | buff[i+7];
                            break;
                        }
                    }
                    this -> fs.fileType = "png";
                    break;

                case GIF_FILE_TYPE:
                    for(i = 0; i < size ; i++)
                    {
                        if(buff[i] == 0x00 && buff[i+1] == 0x2c)
                        {
                            this -> fs.fileWidth = (buff[i+7]<<8) | buff[i+6];
                            this -> fs.fileHeight = (buff[i+9]<<8) | buff[i+8];
                            break;
                        }
                    }
                    this -> fs.fileType = "gif";
                    break;
                default:
                    break;
            }
        };
        int readFile (string path, string fileName) {
            int size;
            unsigned char *buff = NULL;
            FILE *fp;
            if((fp = fopen(path.c_str(),"rb+")) == NULL) {
                return 0;
            }
            fseek(fp,0, SEEK_END);
            size = ftell(fp);
            buff = (unsigned char*) malloc (size);
            if(buff) {
                memset(reinterpret_cast<wchar_t *>(buff), 0, size);
            }
            fseek(fp,0, SEEK_SET);
            if(fread(buff,1,size,fp) != size) {
                return 0;
            }
            this->getImageType(buff, size);

            fclose(fp);
            free(buff);

            this -> fs.fileName = fileName;
            this -> fs.filePath = path;
            this -> fs.fileSize = (float)size;
            return this -> fs.fileType == "txt" ? 0 : 1;
        }

    protected:
        int checkFileType(unsigned char *buf) {
            if(buf[0] == 0xFF && buf[1] == 0xd8 && buf[2] == 0xFF) {
                return JPEG_FILE_TYPE;
            }
            if(buf[0] == 0x42 && buf[1] == 0x4d) {
                return BMP_FILE_TYPE;
            }
            if(buf[0] == 0x47 && buf[1] == 0x49 && buf[2] == 0x46 && buf[3] == 0x38) {
                return GIF_FILE_TYPE;
            }
            if(buf[0] == 0x89 && buf[1] == 0x50 && buf[2] == 0x4e && buf[3] == 0x47) {
                return PNG_FILE_TYPE;
            }
            else
                return 0;
        }
};


#endif //T_PATH_IMAGEFILE_H
