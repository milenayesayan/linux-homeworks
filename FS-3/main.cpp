#include <stdlib.h>
#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

using namespace std;
#define BUF_SIZE 10
int main(int argc, char** argv){
    if(argc < 2){
        cerr << "Error:file path is not given"<< endl;
        exit(1);
    }

    char* name = argv[1];

    int fd =  open(name, O_RDONLY);
    if(fd < 0){
        cerr<< errno << strerror(errno);
        exit(errno);
    }

    char* buffer = new char[BUF_SIZE + 1];
    while(true){
        int read_bytes = read(fd, buffer, BUF_SIZE);
        if(read_bytes < 0){
             cerr<< strerror(errno);
             exit(errno);
        }

        if(read_bytes == 0){
                break;
         }

       buffer[read_bytes] = '\0';
       cout<< buffer;
    }

    int close_num = close(fd);
    if(close_num < 0) {
        cerr<< errno << strerror(errno);
        exit(errno);
    }
     delete[] buffer;
    return 0;
}
