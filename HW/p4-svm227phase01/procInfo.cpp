#include <unistd.h>

#include <string>

#include <iostream>

#include <vector>

#include "Process.h"


    void findProcesses(std::string username, std::vector < Process > & processes);

int main(int argc, char * argv[]) {
    int pid = getpid();
    std::vector < Process > processes;
    std::string username = "test";

    if (argc > 1) {
        std::string option = argv[1];
        if (option == "-p" || option == "-pid") {
            if (argc > 2) {
                pid = std::stoi(argv[2]);
            }
            //if pid negative number cerr error
            if (pid < 0) {
                std::cerr << "pid is negative" << std::endl;
            }
            Process proc1(pid);
            proc1.addRssUsage();
            proc1.addPssUsage();
            proc1.addname();
            proc1.addCwd();
            proc1.addUsername();

            processes.push_back(proc1);
        } else if (option == "-u" || option == "-user") {
            if (argc > 2) {
                username = argv[2];
                //find processes associated with the username
                Process proc1(0);
                findProcesses(username, processes);

                processes.push_back(proc1);
            } else {
                std::cerr << "username is not been given" << std::endl;
            }
        } else {
            std::cerr << "option not specified" << std::endl;
        }
    }
    int sizeofps = processes.size();
    for (int i = 0; i < sizeofps; i++) {
        std::cout << processes[i];
    }
    return 0;
};

     //find the pids associated with the username and add them to the vector
    void findProcesses(std::string username, std::vector < Process > & processes) {
        std::string filePath = "/proc";
        DIR * dir = opendir(filePath.c_str());
        struct dirent * entry;
        while ((entry = readdir(dir)) != NULL) {
            if (entry -> d_type == DT_DIR) {
                std::string pids = entry -> d_name;
                if (std::all_of(pids.begin(), pids.end(), ::isdigit)) {
                    Process proc1(std::stoi(pids));
                    proc1.addname();
                    proc1.addCwd();
                    proc1.addUsername();
                    if (proc1.getUsername() == username) {
                        processes.push_back(proc1);
                    }
                }
            }
        }
        Closedir(dir);
    }
