#include <unistd.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include "Process.h"


void findProcesses(std::string username, std::vector < Process > & processes);
void checkValidUser(std::string username);
void checkOwner(std::string username, std::string pid);
bool checkRoot(std::string pids);
bool checkActive(std::string pids);

int main(int argc, char * argv[]) {
    int pid = getpid();
    std::vector < Process > processes;
    std::string username = "test";



    if (argc > 1) {
        // Check if the first argument is '-p' or '--pid'
        if (strcmp(argv[1], "-p") == 0 || strcmp(argv[1], "--pid") == 0) {
            // If so, make sure there is a valid PID provided
            if (argc == 3) {
                if (std::all_of(argv[2], argv[2] + strlen(argv[2]), ::isdigit)) {
                    pid = std::stoi(argv[2]);
                    Process proc1(pid);
                    proc1.addRssUsage();
                    proc1.addPssUsage();
                    proc1.addname();
                    proc1.addCwd();
                    proc1.addUsername();
                    processes.push_back(proc1);
                } else {
                    std::cerr << "PID is not valid1" << std::endl;
                    exit(1);
                }
            } else if (argc == 5) {
                checkOwner(argv[4], argv[2]);

            }
        } else if (strcmp(argv[1], "-u") == 0 || strcmp(argv[1], "--user") == 0) {
            // If the first argument is '-u' or '--user', expect a username next
            if (argc > 2) {
                username = argv[2];
                // Check if the username is valid
                checkValidUser(username);
                // Find processes associated with the username
                findProcesses(username, processes);
            } else {
                std::cerr << "Username is not specified" << std::endl;
                exit(1);
            }
        } else {
            // If the first argument is neither '-p' nor '--pid', assume it's a PID directly
            if (std::all_of(argv[1], argv[1] + strlen(argv[1]), ::isdigit)) {
                pid = std::stoi(argv[1]);
            } else {
                std::cerr << "PID is not valid2" << std::endl;
                exit(1);
            }
        }

        // If a valid PID is provided, add the process to the vector
        if (pid > 0) {
            // Verify if the PID directory exists in /proc
            std::string filePath = "/proc/" + std::to_string(pid);
            DIR * dir = opendir(filePath.c_str());
            if (dir == NULL) {
                exit(0);
            } else {
                closedir(dir);
            }

            // Add the process with the specified PID to the vector

        } else {
            std::cerr << "PID is not possible" << std::endl;
            exit(1);

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
    DIR * dir = Opendir(filePath.c_str());
    struct dirent * entry;
    while ((entry = Readdir(dir)) != NULL) {
        if (entry -> d_type == DT_DIR) {
            std::string pids = entry -> d_name;
            if (std::all_of(pids.begin(), pids.end(), ::isdigit)) {
                //user strcmp to compare the username with root
                if (strcmp(username.c_str(), "root") != 0){
                    Process proc1(std::stoi(pids));
                    //make sure these files can be opened by opening a file to check if it is valid
                    std::cout << pids << "1\n";
                    std::string filePath = "/proc/" + pids + "/status";
                    FILE * file = fopen(filePath.c_str(), "r");
                    std::cout << pids << "2b\n";

                    if(file == NULL){
                        continue;
                    }
                    proc1.addname();
                    proc1.addCwd();
                    proc1.addUsername();
                    if (strcmp(proc1.getUsername().c_str(), username.c_str()) == 0){
                        //check if the 7th number in /stat is not zero to make sure it is a valid active process then push it to the vector
                        if (checkActive(pids) != false) {
                            proc1.addRssUsage();
                            proc1.addPssUsage();
                            processes.push_back(proc1);
                        }
                    }
                } else if (strcmp(username.c_str(), "root") == 0){
                       

                    if (checkRoot(pids)) {
                      
                        Process proc1(std::stoi(pids));
                        std::string filePath = "/proc/" + pids + "/status";
                        FILE * file = fopen(filePath.c_str(), "r");
                        if(file == NULL){
                            continue;
                        }
                        
                        proc1.addname();
                        proc1.addCwd();
                        proc1.addUsername();
                        proc1.setUsername("root");
                        //if (strcmp(proc1.getUsername().c_str(), username.c_str()) == 0){
                        //check if the 7th number in /stat is not zero to make sure it is a valid active process then push it to the vector
                        //if (checkActive(pids) == true) {
                        processes.push_back(proc1);
                        //}
                       // }
                    } else {
                        continue;
                    }
                }
            }
        }
    }
    Closedir(dir);
}


void checkValidUser(std::string username) {
    if (username == "root") {
        return;
    }
    std::string filePath = "/home";
    DIR * dir = Opendir(filePath.c_str());
    struct dirent * entry;
    while ((entry = Readdir(dir)) != NULL) {
        if (entry -> d_type == DT_DIR) {
            std::string user = entry -> d_name;
            if (user == username) {
                return;
            }
        }
    }
    std::cerr << "username is not valid" << std::endl;
    exit(1);
}

void checkOwner(std::string username, std::string pid) {
    std::string filePath = "/proc/" + pid + "/status";
    std::ifstream file(filePath);
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("Uid:") != std::string::npos) {
            uid_t uid = std::stoi(line.substr(5));
            struct passwd * pw = getpwuid(uid);
            if (pw != nullptr) {
                std::string owner = pw -> pw_name;
                if (owner == username) {
                    return;
                }
            }
        }
    }
    std::cerr << "User is not the owner of the process" << std::endl;
    exit(1);
}


bool checkRoot(std::string pids) {
    std::string filePath = "/proc/" + pids + "/status";
    FILE * file = Fopen(filePath.c_str(), "r");
   
    while (!feof(file)) {
        char * line = NULL;
        size_t len = 0;
        ssize_t read;
        read = getline( & line, & len, file);
        if (read == -1) {
            break;
        }
      
        if (strstr(line, "Uid:")) {
        //     if(stoi(pids) <= 735939 && stoi(pids) >= 735937) {
        // std::cout <<pids <<"he6" << line <<"\n";
        // }
            char * uidStr = strtok(line, "\t");
            uidStr = strtok(NULL, "\t");
            char * uidStr2 = strtok(NULL, "\t");
            //std::cout <<"1uid1:"<<uidStr <<"1uid2:"<<uidStr2 << "\n";


            if (atoi(uidStr) != 0 && atoi(uidStr2) == 0) {
                //std::cout <<"pid:"<<pids<<"uid1:"<<uidStr <<"uid2:"<<uidStr2 << "\n";
                return true;
            }
        }
    }
    return false;

}

//check if the 7th number in /stat is not zero to make sure it is a valid active process then push it to the vector
bool checkActive(std::string pids) {
    std::string filePath = "/proc/" + pids + "/stat";
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return false;
    }
    std::string token;
    for (int i = 0; i < 7; ++i) {
        if (!(file >> token)) {
            return false;
        }
    }

    return token != "0";
}