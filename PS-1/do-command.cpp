#include <iostream>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <chrono>
#include <errno.h>
#include <string.h>

using namespace std;

void do_command(char** argv) {

  auto start_time = chrono::high_resolution_clock::now();

// fork() and errors
  pid_t pid = fork();
  if(pid == -1) {
      cout << "Error: no child process is created " << strerror(errno) <<endl;
      exit(errno);
  }
  
// execv() with errors
    int exec_res = execv(argv[0], argv);
    if(exec_res == -1) {
      cout << "Error: error has occurred " << strerror(errno) << endl;
      exit(errno);
    }

// waitpid() with errors
    int stat;
    pid_t wait_func = waitpid(pid, &stat, 0);
    if(wait_func == -1) {
        cout << "Error: failure during wait " << strerror(errno) << endl;
    }
  
  auto end_time = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::seconds>(end_time - start_time);

  cout << "Status: " << WEXITSTATUS(stat) << endl;
  cout << "Duration: " << duration.count() << "seconds" << endl;
  
 }

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cerr << "path is not given " << strerror(errno) << std::endl;
        exit(1);
    }
    
    do_command(argv);

    return 0;
}
