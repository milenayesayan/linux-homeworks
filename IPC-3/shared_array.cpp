#include "shared_array.h"
#include <unistd.h>

using namespace std;

shared_array::shared_array(string name, int size) : name(name), size(size) {
  string name_size = std::to_string(size);
  this->name = '/' + this->name + '_' + name_size;

  fd = shm_open(this->name.c_str(), O_CREAT | O_RDWR, 0666);
  if (fd == -1) {
    cerr << strerror(errno) << endl;
    exit(errno);
  }

  int ftrnc_res = ftruncate(fd, size);
  if (ftrnc_res == -1){
    cerr << strerror(errno) << endl;
    exit(errno);
  }

  file_cont = (char*) mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  if (file_cont == MAP_FAILED) {
    cerr << strerror(errno) << endl;
    exit(errno);
  }
}

char& shared_array::operator[](int i) {
  return file_cont[i];
}

shared_array::~shared_array() {
  if (munmap(file_cont, size) == -1) {
    cerr << strerror(errno) << endl;
  }

  munmap(file_cont, size);

  if (close(fd) == -1) {
    cerr << strerror(errno) << endl;
    exit(errno);
  }

  if(shm_unlink(this->name.c_str()) == -1) {
    cerr << strerror(errno) << endl;
    exit(errno);
  }
}
