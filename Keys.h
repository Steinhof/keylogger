#ifndef LIB_APP_KEYS_H
#define LIB_APP_KEYS_H

#include <map>
#include "KeyPair.h"

class Keys {
public:
    Keys();

    static map<int, KeyPair> KEYS;
};


#endif
