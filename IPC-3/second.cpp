#include <iostream>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <cerrno>
#include "shared_array.h"

using namespace std;

int main() {

  shared_array arr("file_path", 10);

  sem_t* sem = sem_open("semaphore_name",O_RDWR);

  if (sem == SEM_FAILED) {
    cerr << "Failed to create semaphore" << endl;
    exit(errno);
  }

  while(true) {

    sem_wait(sem);

    for(int i = 0; i < 10; i++) {
      cout << arr[i];
    }

    sem_post(sem);

  }

  if(sem_close(sem) == -1) {
    cerr << strerror(errno) << endl;
    exit(errno);
  }

  sem_close(sem);

  if(sem_unlink("semaphore_name") == -1) {
    cerr << strerror(errno) << endl;
    exit(errno);
  }

  sem_unlink("semaphore_name");

 return 0;
}
