#ifndef HELPER_H_INCLUDED
#define HELPER_H_INCLUDED

#include <string>
#include <ctime>
#include <sstream>
#include <fstream>

using namespace std;

namespace Helper {

    // converts variables to string
    template<class T>
    string ToString(const T &);

    struct DateTime {
        DateTime() {
            time_t ms;
            time(&ms);

            struct tm *info = localtime(&ms);

            D = info->tm_mday; //day
            m = info->tm_mon + 1; //month +1 since counting starts at 0
            y = 1900 + info->tm_year; // year
            M = info->tm_min; //minutes
            H = info->tm_hour; //hours
            S = info->tm_sec; //seconds
        }

        DateTime(int D, int m, int y, int H, int M, int S) : D(D), m(m), y(y), H(H), M(M), S(S) {}

        DateTime(int D, int m, int y) : D(D), m(m), y(y), H(0), M(0), S(0) {}

        DateTime Now() const {
            return DateTime();
        }

        int D, m, y, H, M, S;

        string GetDateString() const {
            //returns Date in the DD.mm.YYYY format
            return std::string(D < 10 ? "0" : "") + ToString(D) + std::string(M < 10 ? ".0" : ".") + ToString(m) + "." +
                   ToString(y);

        }

        string GetTimeString(const string &sep = ":") const {
            //returns time in the following format HH:MM:SS
            return string(H < 10 ? "0" : "") + ToString(H) + sep +
                   string(M < 10 ? "0" : "") + ToString(M) + sep +
                   string(S < 10 ? sep : "") + ToString(S);

        }

        string GetDateTimeString(const string &sep = ":") const {
            return GetDateString() + " " + GetTimeString(sep);
        }


    };

    template<class T>
    string ToString(const T &e) {
        ostringstream s;
        s << e;
        return s.str();
    }

    //writes to the log
    void WriteAppLog(const string &s) {
        ofstream file("AppLog.txt", std::ios::app);
        file << "[" << Helper::DateTime().GetDateTimeString() << "]" <<
             "\n" << s << std::endl << "\n";

        file.close();
    }

}


#endif // HELPER_H_INCLUDED