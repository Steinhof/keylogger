#ifndef KEY_CONSTANTS_H
#define KEY_CONSTANTS_H

#include <map>
#include <string>

using namespace std;

class KeyPair {

public:
    KeyPair(const string &vk = "", const string &name = "") : VKName(vk), Name(name) {};

    string VKName;
    string Name;
};


#endif
