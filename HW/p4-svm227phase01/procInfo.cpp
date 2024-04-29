#include <unistd.h>
#include <string>
#include <iostream>
#include <vector>
#include "Process.h"



int main(int argc, char* argv[]) {
    int pid = getpid();
    std::vector<Process> processes;
    std::string username = "test";

    if (argc > 1) {
        std::string option = argv[1];
        if(option == "-p" || option == "pid") {
            if(argc > 2) {
                pid = std::stoi(argv[2]);
            }
            Process proc1(pid);
            proc1.addRssUsage("Rss:");
            proc1.addPssUsage("Pss:");
            proc1.addname();
            proc1.addCwd();
            proc1.addUsername();
            std::cout << proc1.getUsername() << "  " << proc1.getPid() <<  "  " << proc1.getCwd() << "  " << proc1.getName() <<  "  " << proc1.getPss() << "  " << proc1.getRss() << std::endl;
            processes.push_back(proc1);
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
    for(int i = 0; i < processes.size(); i++) {
        std::cout << processes[i];
    }
}