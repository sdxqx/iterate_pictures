//
// Created by Master on 2021/10/15.
//

#ifndef T_PATH_PROCESS_H
#define T_PATH_PROCESS_H

#include <thread>
#include <functional>
#include "../../vars/file_vars.h"

class process {
    public:
        process* join(thread_call callback, const string& t_name, ...) {
            va_list args;
            this -> tr->callback[this -> tr->index] = thread(callback, t_name, args);
            return this;
        };

        int start() const {
            for(int i = 0; i < this -> tr->index; i++) {
                this -> tr->callback[i].join();
            }
            return 1;
        }
    protected:
        threads* tr;
};


#endif //T_PATH_PROCESS_H
