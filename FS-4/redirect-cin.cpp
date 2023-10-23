#include <iostream>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

void initialize(int argc, char** argv) {
    if(argc < 2){
        std::cerr << "Error:file path is not given"<< std:: endl;
        exit(1);
    }

    char* path = argv[1];

    int fd =  open(path, O_RDONLY | O_WRONLY);
    if(fd < 0){
        std::cerr<< errno << strerror(errno);
        exit(errno);
    }

   
   int duplicate = dup2(fd,0);
   if(duplicate < 0){
   std::cerr << strerror(errno);
   }
   int close_f = close(fd);
    if(close_f < 0){
     std::cerr << strerror(errno);
     exit(errno);
      }
}

int main(int argc, char** argv)
{
  initialize(argc, argv);

  std::string input;
  std::cin >> input;
  size_t size_of_input = input.size();
  std::string reversed[size_of_input];

  for(int i = 0; i <= size_of_input; ++i) {
      reversed[i] = input[size_of_input - i];
  }
  reversed[size_of_input + 1] = '\0';

  std::cout << reversed;

  return 0;
}
