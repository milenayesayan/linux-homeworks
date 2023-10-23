#include <iostream>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>



int main (int argc, char** argv) {
    if(argc < 2){
        std::cerr << "Error:file path is not given"<< std:: endl;
        exit(1);
    }

    const char* path = argv[1];

    int fd =  open(path,O_RDWR);
    if(fd < 0){
    	close(fd);
        std::cerr<< errno << strerror(errno);
        exit(errno);
    }

    off_t file_length = lseek(fd, 0, SEEK_END);
    
    if(file_length < 0) {
        std::cerr << "Error " << errno << ": " << strerror(errno) << std::endl;
        exit(errno);
        }
        
    if(file_length == 0) {
    close(fd);
    int  unl = unlink(path);
    if(unl != 0){
    std::cerr<< strerror(errno)<< std::endl;
	}
    }

    
    char buffer[file_length];

    for(int i = 0; i <= file_length; ++i) {
        buffer[i] = '\0';
    }

    lseek(fd, 0, SEEK_SET);
    ssize_t write_bytes = write(fd, buffer, file_length);

    if(write_bytes < 0){
     std::cerr<< strerror(errno);
     close(fd);
     exit(errno);
    }
     
    close(fd);
    delete[] buffer;
    int  unl = unlink(path);
    if(unl < 0){
    std::cerr<< strerror(errno)<< std::endl;
}
    return 0;
}
