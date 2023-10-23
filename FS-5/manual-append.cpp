#include <stdlib.h>
#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char** argv)
{
     if(argc < 2){
        std::cerr << "Error:file path is not given"<< std::endl;
        exit(1);
    }

    char* path = argv[1];

    int fd =  open(path, O_RDONLY | O_WRONLY | O_TRUNC | O_CREAT,S_IRWXU|S_IRUSR|S_IRGRP|S_IROTH );
    if(fd < 0){
        std::cerr<< errno << strerror(errno);
        exit(errno);
    }

    int new_fd = dup(fd);

    std::string line1 = "first line\n";
    std::string line2 = "second line";

    size_t write_bytes1 = write(fd,line1.c_str(), line1.size());
    if(write_bytes1 < 0) {
      std::cerr<< errno << strerror(errno);
        exit(errno);
    }

    size_t write_bytes2 = write(new_fd,line2.c_str(), line2.size());
    if(write_bytes2 < 0) {
      std::cerr<< errno << strerror(errno);
        exit(errno);
    }

    close(fd);
    close(new_fd);
    return 0;
    }

