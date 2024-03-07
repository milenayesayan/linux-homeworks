#include <iostream>
#include <unistd.h>
#include <cstring>
#include <errno.h>
#include <sys/wait.h>


using namespace std;


int mthPrimeNumber(int m) {
    if (m <= 0) {
        return 0;
    }

    int count = 0;
    int num = 2;

    while(true) {
      bool isPrime = true;

        for(int i = 2; i * i <= num; ++i) {
          if(num % i == 0) {
            isPrime = false;
              break;
          }
        }

      if(isPrime) {
         count++;
      }

      if(count == m) {
          return num;
      }

      num++;
    }
}


int main() {
    int pipe_ask[2];
    int pipe_answer[2];

    int pipe_ask_res = pipe(pipe_ask);

    if(pipe_ask_res < 0) {
        cerr << strerror(errno) << endl;
        exit(errno);
    }

    int pipe_ans_res = pipe(pipe_answer);

    if(pipe_ans_res < 0) {
        cerr << strerror(errno) << endl;
        exit(errno);
    }


    pid_t pid = fork(); //creat a child process

    if(pid == -1) { //error
        cerr << strerror(errno) << endl;
        exit(errno);
    }


    if(pid == 0) { // child process
        close(pipe_ask[1]);
        close(pipe_answer[0]);

        int m;

        while(true) {
            int read_res = read(pipe_ask[0], &m, sizeof(int)); //read from pipe_ask

            if(read_res < 0){ // error
               cerr << strerror(errno) << endl;
               exit(errno);
            }
            cout << "[Child] Calculating " << m << "-th prime number..." << endl;

            int mthPrime = mthPrimeNumber(m); //caclulate mthPrimeNumber

            cout << "[Child] Sending calculation result of prime(" << m << ")..." << endl;
            int write_res = write(pipe_answer[1], &mthPrime, sizeof(int)); //send mthPrimeNumber to pipe_answer

            if(write_res < 0) { // error
                cerr << strerror(errno) << endl;
                exit(errno);
            }
        }
    }


    if(pid > 0) { //parent process

        close(pipe_ask[0]);
        close(pipe_answer[1]);

        string input;

        while(true) {
            cout << "[Parent] Please enter the number: ";
            cin >> input;

            if(input == "exit") {
                return 0;
            }

            int m = stoi(input);

            cout << "[Parent] Sending " << m << " to the child process..." << endl;

            int write_res = write(pipe_ask[1], &m, sizeof(m)); //send m to pipe_ask

            if(write_res < 0) { //error
                std::cerr << strerror(errno) << endl;
                exit(errno);
            }

            cout << "[Parent] Waiting for the response from the child process..." << endl;

            int res;

            int read_res = read(pipe_answer[0], &res, sizeof(int)); //read from pipe_answer

            if(read_res < 0) {
                cerr << strerror(errno) << endl;
                exit(errno);
            }

            cout << "[Parent] Received calculation result of prime(" << m << ") = " << res << "..." << endl;
        }

      int wait_res = waitpid(pid, NULL, 0);

      if(wait_res == -1) {
        cerr << strerror(errno);
        exit(errno);
      }
    }

 return 0;
}
