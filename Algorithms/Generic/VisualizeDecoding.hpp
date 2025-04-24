//
//  VisualizeDecoding.hpp
//  Algorithms
//
//  Created by J.C. on 4/22/25.
//

#ifndef VisualizeDecoding_h
#define VisualizeDecoding_h

#include <cassert>
#include <string>

#include "../Exercise/LEB128/IntegerEncoding.hpp"

namespace GP_VisualizeDecoding {

class Solution {
    unsigned char fromHex(char const c) {
        if (c <= '9') {
            return c - '0';
        } else {
            return c - 'A' + 10;
        }
    }
    void destringHex(unsigned char * const buff, const std::string& hexString) {
        std::string hexNumeral(hexString.substr(2, -1));
        int n(hexNumeral.length());
        assert(n % 2 == 0);
        for (int i = 0; i < n; i += 2) {
            char hi(hexNumeral[i]), lo(hexNumeral[i+1]);
            buff[i/2] = fromHex(hi) << 4 | fromHex(lo);
        }
    }
public:
    int testDecode(std::string& hexString) {
        unsigned char buff[8] = {0};
        destringHex(buff, hexString);
        return IntegerEncoding::IntEncoder::decodeInt(&buff[0]);
    }
    static constexpr auto testEntry = &Solution::testDecode;
};

} // end namespace GP_VisualizeDecoding


#endif /* VisualizeDecoding_h */
