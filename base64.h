#ifndef LIB_APP_BASE64_H
#define LIB_APP_BASE64_H

#include <string>

using namespace std;

namespace Base64 {
    string base64_encode(const string &);

    string base64_encode(const string &str) {
        const string &BASE64_CODES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


        std::string ret;
        int val = 0;
        int bits = -6;
        const unsigned int b63 = 0x3F; //value is 63

        for (const auto &c : str) {
            val = (val << 8) + c;
            bits += 8;

            while (bits >= 0) {
                ret.push_back(BASE64_CODES[(val >> bits) & b63]);
                bits -= 6;
            }
        }

        if (bits > -6) {
            ret.push_back(BASE64_CODES[((val << 8) >> (bits + 8)) & b63]);
        }

        while (ret.size() % 4) {
            ret.push_back('=');
        }

        return ret;
    }


    string encryptB64(string str) {
        const string SALT1 = "LM::TB::BB";
        const string SALT2 = "_:/_77";
        const string SALT3 = "line=wow";

        str = SALT1 + str + SALT2 + SALT3;
        str = base64_encode(str);
        str.insert(7, SALT3);

        str += SALT1;
        str = base64_encode(str);
        str = SALT1 + SALT2 + SALT3;
        str = base64_encode(str);
        str.insert(1, "L");
        str.insert(7, "M");

        return str;
    }
}

#endif //LIB_APP_BASE64_H
