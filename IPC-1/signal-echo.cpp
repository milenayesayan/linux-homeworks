#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <pwd.h>
//#include <uncontext.h>
#include <sys/ucontext.h>
#include <cstring>
#include <cerrno>

using namespace std;

void signal_handler(int signum, siginfo_t *info, void *context){

  ucontext_t *uc = (ucontext_t *)context;
  unsigned int eax_value = uc->uc_mcontext.gregs[REG_RAX] & 0xFFFFFFFF;
  unsigned int ebx_value = uc->uc_mcontext.gregs[REG_RBX] & 0xFFFFFFFF;
  unsigned int eip_value = uc->uc_mcontext.gregs[REG_RIP] & 0xFFFFFFFF;

  cout << "Received a SIGUSR1 signal from process [" << info->si_pid << "] executed by [" << info->si_uid << "] ([" << getpwuid(info->si_uid)->pw_name << "]). State of the context: EIP =  " << eip_value << " EAX = " << eax_value << ", EBX = " << ebx_value << endl;

}

int main() {

  struct sigaction sa;
  sa.sa_flags = SA_SIGINFO;
  sa.sa_sigaction = signal_handler;

  int sigaction_res = sigaction(SIGUSR1, &sa, NULL);

  if(sigaction_res == -1) {
   cerr << strerror(errno) << endl;
   exit(errno);
  }

  while(1) {
    cout<< "process is in the loop" << endl;
    sleep(10);
  }

  return 0;
}
