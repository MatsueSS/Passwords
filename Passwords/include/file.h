#ifndef _FILE_H_
#define _FILE_H_

#include <iostream>

using std::string;

class File {
public:
    virtual void read(const string& filename) = 0;
    virtual void write(const string& filename) = 0;
};

#endif