#include "syscalls.h"
#include "Process.h"
#include <iostream>
#include <pwd.h>
#include <fstream>


Process::Process(int pidVal) {
    // if (pid <= 0 ) {
    //     std::cerr << "pid is negative" << std::endl;
    //     exit(1);
    // }
    pid = pidVal;
    rss = 0;
    pss = 0;
}
std::string Process::getName() {
    if (!ProgName.empty()) {
        ProgName.pop_back();
    }

    return ProgName;
}



std::string Process::getUsername() {
    return userName;
}

int Process::getPid() {
    return pid;
}
int Process::getRss() {
    return rss;
}
int Process::getPss() {
    return pss;
}
std::string Process::getCwd() {
    return cwd;
}
void Process::setPid(long pidVal) {
    pid = pidVal;
}
void Process::setRss(long rssVal) {
    rss = rssVal;
}
void Process::setpss(long pssVal) {
    pss = pssVal;
}
void Process::setcwd(std::string cwdVal) {
    cwd = cwdVal;
}


void Process::addRssUsage() {
    std::string pids = std::to_string(pid);
    std::string filePath = "/proc/" + pids + "/smaps";
    FILE * file = Fopen(filePath.c_str(), "r");
    while (!feof(file)) {
        char * line = NULL;
        size_t len = 0;
        ssize_t read;
        read = getline( & line, & len, file);
        if (read == -1) {
            break;
        }
        if (strstr(line, "Rss:")) {
            char * rssStr = strtok(line, " ");
            rssStr = strtok(NULL, " ");
            rss += atol(rssStr);
        }
        free(line);
    }
    Fclose(file);
}

void Process::addPssUsage() {
    std::string pids = std::to_string(pid);
    std::string filePath = "/proc/" + pids + "/smaps";
    FILE * file = Fopen(filePath.c_str(), "r");

    while (!feof(file)) {
        char * line = NULL;
        size_t len = 0;
        ssize_t read;
        read = getline( & line, & len, file);
        if (read == -1) {
            break;
        }
        if (strstr(line, "Pss:")) {
            char * pssStr = strtok(line, " ");
            pssStr = strtok(NULL, " ");
            pss += atol(pssStr);
        }
        free(line);
    }
    Fclose(file);
}

//print cwd with /proc/$pid/cwd ifstream: https://stackoverflow.com/questions/6399822/reading-a-text-file-fopen-vs-ifstream
void Process::addCwd() {
    std::string pids = std::to_string(pid);
    std::ifstream file("/proc/" + pids + "/cmdline");
    std::string line;
        if (file.is_open()) {
        std::getline(file, line);
        size_t firstNullByte = line.find('\0');
        while(firstNullByte != std::string::npos && firstNullByte != line.size()-1) {
            line[firstNullByte] = ' ';
            firstNullByte = line.find('\0');
        }
    }

    int num = line.find(" ");


    //if the line doesn't start with / then use the exe file in /proc/pids/exe
    if (line[0] != '/') {
        std::string filePath = "/proc/" + pids + "/exe";
        char buffer[1024];
        ssize_t len = readlink(filePath.c_str(), buffer, sizeof(buffer));
        if (len != -1) {
            buffer[len] = '\0';
            std::string bufferString = std::string(buffer);

            std::string bufferCWD = bufferString + line.substr(num);
            cwd = bufferCWD;
        }
    } else {
        cwd = line;
    }

}

//print name of prog /proc/$pid/status only the first line is needed
void Process::addname() {
    std::string pids = std::to_string(pid);
    std::string filePath = "/proc/" + pids + "/status";
    FILE * file = Fopen(filePath.c_str(), "r");

    char * line = NULL;
    size_t len = 0;
    getline( & line, & len, file);
    //get a substring of the name after Name:
    std::string substring = std::string(line).substr(6);
    if (!substring.empty()) {
        substring.pop_back();
    }
    Fclose(file);
    free(line);
    ProgName = substring;
}

//get uid from status and then use getpwuid to get username from the uid
std::string Process::addUsername() {
    std::string pids = std::to_string(pid);
    std::string filePath = "/proc/" + pids + "/status";
    FILE * file = Fopen(filePath.c_str(), "r");

    std::string usernameTemp = "";
    while (!feof(file)) {
        char * line = NULL;
        size_t len = 0;
        ssize_t read;
        read = getline( & line, & len, file);
        if (read == -1) {
            break;
        }
        if (strstr(line, "Uid:")) {
            //split the output of Uid:    42      42      42      42 into getting just the 42:
            char * uidStr = strtok(line, "\t");
            uidStr = strtok(NULL, "\t");
            struct passwd * pwd = getpwuid(atoi(uidStr));
            usernameTemp = pwd -> pw_name;
            userName = pwd -> pw_name;
        }
        free(line);
    }
    Fclose(file);
    return usernameTemp;
}

