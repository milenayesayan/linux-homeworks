#ifndef SHARED_ARRAY_H
#define SHARED_ARRAY_H

#include <iostream>
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>

using namespace std;

class shared_array {

private:
 string name;
 int size;
 char* file_cont;
 int fd;

public:
 shared_array(string name, int size);
 ~shared_array();
 char& operator[](int i);

};

#endif
