#include "syscalls.h"


class Process {
    private:
    std::string username;
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
            std::cout << line << std::endl;
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
            std::cout << line << std::endl;
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
        std::string filePath = "/proc/" + pids + "/cwd";
        char * buf = new char[1024];
        ssize_t len = readlink(filePath.c_str(), buf, 1024);
        buf[len] = '\0';
        cwd = buf;
    }

    //be able to print out your process instance(s) information with a simple "call" of the insertion operator. (There should be no calls to printf or fprintf.) E.g., cout << procInstance;
};