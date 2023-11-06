#include <iostream>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

using namespace std;

#define BUFFER_SIZE 15


int main(int argc, char** argv) {

    if(argc < 3) {
        cerr << "Error:file path is not given" << endl;
        exit(1);
    }

    char* source_file = argv[1];
    char* destination_file = argv[2];

    int fd_source =  open(source_file, O_RDONLY);
    if(fd_source < 0) {
        exit(errno);
    }

    int fd_dest =  open(destination_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if(fd_dest < 0) {
        exit(errno);
    }

    char* buffer = new char[BUFFER_SIZE + 1];
    int copied_bytes = 0;
    int hole_bytes = 0;


    while(true) {
        int read_bytes = read(fd_source, buffer, BUFFER_SIZE);

        if(read_bytes < 0){
             cerr<< strerror(errno);
             exit(errno);
        }

        if(read_bytes == 0){
            buffer[read_bytes] = '\0';
            break;
            }

        int write_bytes = write(fd_dest, buffer, read_bytes);

        if(write_bytes < 0) {
             cerr<< strerror(errno);
             exit(errno);
        }

        copied_bytes += write_bytes;
        
        off_t begin_of_hole = lseek(fd_dest, 0, SEEK_HOLE);
        off_t end_of_hole = lseek(fd_dest, 0, SEEK_DATA);
        
        while(begin_of_hole >= 0) {
           hole_bytes = end_of_hole - begin_of_hole;
           begin_of_hole = lseek(fd_dest, 0, SEEK_HOLE);
           end_of_hole = lseek(fd_dest, 0, SEEK_DATA);

        }
        
        

   }

    int close_source = close(fd_source);
      if(close_source < 0) {
        cerr << errno << strerror(errno);
        exit(errno);
    }
    int close_dest = close(fd_dest);
      if(close_dest < 0) {
        cerr << errno << strerror(errno);
        exit(errno);
    }
    cout<< "Succesfully copyed " << copied_bytes << " bytes (data: " << copied_bytes - hole_bytes << ", hole: " << hole_bytes << ")";

    return 0;
}
