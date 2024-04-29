#include "syscalls.h"
#include <iostream>
#include <fstream>
#include <pwd.h>


class Process {
    private:
    std::string ProgName;
    std::string userName;
    int pid;
    long rss;
    long pss;
    std::string cwd;

    public:
        Process(int pidVal) {
            pid = pidVal;
            rss = 0;
            pss = 0;
        }
    std::string getName() {
    if (!ProgName.empty()) {
        ProgName.pop_back();
    }

        return ProgName;
    }

    // Overloading << operator
    friend std::ostream & operator << (std::ostream & out, const Process & proc) {
        out << proc.userName << "  " << proc.pid << "  " << proc.rss << "  " << proc.pss << "  " << proc.cwd << std::endl;
        return out;
    }


    std::string getUsername() {
        return userName;
    }

    int getPid() {
        return pid;
    }
    int getRss() {
        return rss;
    }
    int getPss() {
        return pss;
    }
    std::string getCwd() {
        return cwd;
    }
    void setPid(long pidVal) {
        pid = pidVal;
    }
    void setRss(long rssVal) {
        rss = rssVal;
    }
    void setpss(long pssVal) {
        pss = pssVal;
    }
    void setcwd(std::string cwdVal) {
        cwd = cwdVal;
    }


    void addRssUsage(std::string type) {
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
            if (strstr(line, type.c_str())) {
                char * rssStr = strtok(line, " ");
                rssStr = strtok(NULL, " ");
                rss += atol(rssStr);
            }
        }
    }

    void addPssUsage(std::string type) {
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
            if (strstr(line, type.c_str())) {
                char * pssStr = strtok(line, " ");
                pssStr = strtok(NULL, " ");
                pss += atol(pssStr);
            }
        }
    }

    //print cwd with /proc/$pid/cwd
    void addCwd() {
        std::string pids = std::to_string(pid);
        std::ifstream file("/proc/" + pids + "/cmdline");
        std::string line;
        std::getline(file, line);
        cwd = line;
    }

    //print name of prog /proc/$pid/status only the first line is needed
    void addname() {
        std::string pids = std::to_string(pid);
        std::string filePath = "/proc/" + pids + "/status";
        FILE* file = Fopen(filePath.c_str(), "r");
        char* line = NULL;
        size_t len = 0;
        getline(&line, &len, file);
        //get a substring of the name after Name:
        std::string substring = std::string(line).substr(6);
        ProgName = substring;
    }
    //get uid from status and then use getpwuid to get username from the uid
    void addUsername() {
       std::string pids = std::to_string(pid);
        std::string filePath = "/proc/" + pids + "/status";
        FILE* file = Fopen(filePath.c_str(), "r");
        while(!feof(file)) {
            char* line = NULL;
            size_t len = 0;
            ssize_t read;
            read = getline(&line, &len, file);
            if(read == -1) {
                break;
            }
            if(strstr(line, "Uid:")) {
            //split the output of Uid:    42      42      42      42 into getting just the 42:
            char* uidStr = strtok(line, "\t");
            uidStr = strtok(NULL, "\t");
            std::cout << "uidStr: " << uidStr << std::endl;
            struct passwd* pwd = getpwuid(atoi(uidStr));
            userName = pwd->pw_name;
            }
        }
    }
};


    //be able to print out your process instance(s) information with a simple "call" of the insertion operator. (There should be no calls to printf or fprintf.) E.g., cout << procInstance;