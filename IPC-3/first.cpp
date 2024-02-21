#include <iostream>
#include <cstring>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <cerrno>
#include "shared_array.h"

using namespace std;

int main() {

  shared_array arr("file_path", 10);

  sem_t* sem = sem_open("semaphore_name", O_CREAT | O_RDWR, 0644, 1);

  if (sem == SEM_FAILED) {
    cerr << "Failed to create semaphore" << endl;
    exit(errno);
  }

  while(true) {
    sem_wait(sem);

    for(int i = 0; i < 10; i++) {
      arr[i] = 'a';
    }

    sem_post(sem);
  }
  return 0;
}
