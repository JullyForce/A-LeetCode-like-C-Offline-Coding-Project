//
//  LC100352.hpp
//  Algorithms
//
//  Created by Jun Chen on 7/13/24.
//

#ifndef LC100352_h
#define LC100352_h

#include <string>

using namespace std;

namespace LC100352 {

class Solution {
public:
    string getSmallestString(string s) {
        int p(0);
        while ( p < s.length()) {
            int q(p+1);
            if (q < s.length() && s[q] % 2 == s[p] % 2 && s[q] < s[p]) {
                char t = s[p];
                s[p] = s[q];
                s[q] = t;
                return s;
            }
            p = q;
        }
        return s;
    }
    static constexpr auto testEntry = &Solution::getSmallestString;
};

} // end namespace LC100352


#endif /* LC100352_h */
