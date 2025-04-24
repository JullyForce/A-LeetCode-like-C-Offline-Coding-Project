//
//  LC1404.hpp
//  Algorithms
//
//  Created by Jun Chen on 9/26/24.
//

#ifndef LC1404_h
#define LC1404_h

#include <string>

using namespace std;

namespace LC1404 {

class Solution {
public:
    int numSteps(string s) {
        int n(s.length());
        int r(n-1);
        int ans(0);
        bool carry(false);
        while (r > 0) {
            if (!carry && s[r] != '0') {
                carry = true;
                ans += 2;
                r --;
                continue;
            }
            if (carry && s[r] == '0') {
                ans += 2;
                r --;
                continue;
            }
            ans ++;
            r --;
        }
        if (carry) {
            ans ++;
        }
        return ans;
    }
static constexpr auto testEntry = &Solution::numSteps;
};

} // end namespace LC1404

#endif /* LC1404_h */
