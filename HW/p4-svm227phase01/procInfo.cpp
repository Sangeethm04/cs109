#include <unistd.h>
#include <string>
#include <iostream>
#include "Process.h"



int main(int argc, char* argv[]) {
    int pid = getpid();
    std::string username = "test";

    if (argc > 1) {
        std::string option = argv[1];
        if(option == "-p" || option == "pid") {
            if(argc > 2) {
                pid = std::stoi(argv[2]);
            } else {
                std::cerr << "pid is not been given" << std::endl;
            }
            std::cout << "argc:" << argc;
            std::cout << "pid:" << pid;
            Process proc1(pid);
            proc1.addRssUsage("Rss:");
            proc1.addPssUsage("Pss:");
            proc1.addCwd();
            std::cout << "RSS: " << proc1.getRss() << "PSS: " << proc1.getPss() <<  "CWD: " << proc1.getCwd() << std::endl;
        } else if(option == "-u" || option == "user") {
            if(argc > 2) {
                username = argv[2];
            } else {
                std::cerr << "username is not been given" << std::endl;
            }
        } else {
            std::cerr << "option not specified" << std::endl;
        }
    }
}