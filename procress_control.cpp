#ifndef __cplusplus
#error "Please use C++ compiler"
#endif

#if __cplusplus < 201103UL
#error "Please use -std=c++11 or higher standards"
#endif

#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>

#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

const int N = 10;
const int INTERVAL = 2;

int proc_seq = 0;

void do_sth() {
    while (true) {
        std::cout << "No." << proc_seq << " process runs" << std::endl;
        std::cout << std::endl;
        sleep(INTERVAL);
    }
}

int main(int argc, char *argv[]) {
    int childs = N;
    pid_t pid[N];

    if (argc > 1)
        childs = std::min(N, std::stoi(argv[1]));

    for (int i = 0; i < childs; ++i) {
        if (pid_t child = fork()) { // parent
            pid[i] = child;
        } else { // child
            proc_seq = i;
            do_sth();
        }
    }
    char ch;
    while (std::cin >> ch, ch != 'q') {
        if (std::isdigit(ch) && pid[ch - '0']) {
            kill(pid[ch - '0'], SIGTERM);
            pid[ch - '0'] = 0;
        }
    }
    for (int i = 0; i < childs; ++i) {
        if (pid[i])
            kill(pid[i], SIGTERM);
    }
    return 0;
}
