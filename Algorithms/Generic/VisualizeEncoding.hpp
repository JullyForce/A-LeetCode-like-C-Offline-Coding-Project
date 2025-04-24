//
//  VisualizeEncoding.hpp
//  Algorithms
//
//  Created by J.C. on 4/22/25.
//

#ifndef VisualizeEncoding_h
#define VisualizeEncoding_h

#include <cassert>
#include <string>

#include "../Exercise/LEB128/IntegerEncoding.hpp"

namespace GP_VisualizeEncoding {

class Solution {
    char toHex(unsigned char const c) {
        assert(c < 16);
        if (c < 10) {
            return '0' + c;
        } else {
            return 'A' + c - 10;
        }
    }
    std::string stringifyHex(unsigned char const * const buff) {
        std::string ans("0x");
        for (int i = 0; i < 8; i ++) {
            unsigned char c = buff[i];
            ans += toHex(c >> 4);
            ans += toHex(c & 0x0F);
            bool lastByte = !(c & 0x80);
            if (lastByte) {
                break;
            }
        }
        return ans;
    }
public:
    std::string testEncode(int x) {
        unsigned char buff[8] = {0};
        IntegerEncoding::IntEncoder::encodeInt(buff, x);
        return stringifyHex(buff);
    }
    static constexpr auto testEntry = &Solution::testEncode;
};

} // end namespace GP_VisualizeEncoding


#endif /* VisualizeEncoding_h */
