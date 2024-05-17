#include "syscalls.h"
#include <iostream>
#include <pwd.h>
#include <fstream>

#ifndef PROCESS_H
#define PROCESS_H


class Process {
    private:
        std::string ProgName;
        std::string userName;
        int pid;
        long rss;
        long pss;
        std::string cwd;

    public:
        Process(int pidVal);
    std::string getName();

    // Overloading << operator
    friend std::ostream & operator << (std::ostream & out, const Process & proc) {
        if (proc.rss != 0 && proc.pss != 0) {
          out << proc.userName << " " << proc.pid << " '" << proc.cwd << "' '" << proc.ProgName << "' " << proc.pss << " "  << proc.rss << std::endl;
        } else {
          out << proc.userName << " " << proc.pid << " '" << proc.cwd << "' '" << proc.ProgName << "' " << std::endl;
        }
        return out;
    }


    std::string getUsername();

    int getPid();
    int getRss();
    int getPss();
    std::string getCwd();
    void setPid(long pidVal);
    void setRss(long rssVal);
    void setpss(long pssVal);
    void setcwd(std::string cwdVal);
    void setUsername(std::string username) {
        userName = username;
    }


    void addRssUsage();

    void addPssUsage();

    //print cwd with /proc/$pid/cwd ifstream: https://stackoverflow.com/questions/6399822/reading-a-text-file-fopen-vs-ifstream
    void addCwd();

    //print name of prog /proc/$pid/status only the first line is needed
    void addname();
    //get uid from status and then use getpwuid to get username from the uid
    std::string addUsername();


};

#endif

