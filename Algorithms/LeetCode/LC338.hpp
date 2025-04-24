//
//  LC338.hpp
//  Algorithms
//
//  Created by Jun Chen on 4/18/25.
//

#ifndef LC338_h
#define LC338_h

#include <vector>

using namespace std;

namespace LC338 {

class Solution {
    int popcount(int x) {
        x = (x & 0x55555555) + ((x >> 1) & 0x55555555); // 2/2-digit sum
        x = (x & 0x33333333) + ((x >> 2) & 0x33333333); // 3/4-digit sum
        x = (x & 0x07070707) + ((x >> 4) & 0x07070707); // 4/8-digit sum
        x = (x & 0x000F000F) + ((x >> 8) & 0x000F000F); // 5/16-digit sum
        x = (x & 0x0000001F) + ((x >> 16) & 0x0000001F); // 6/32-digit sum
        return x;
    }
public:
    vector<int> countBits(int n) {
        vector<int> ans(n+1);
        
        for (int i = 0; i <= n; i ++) {
            ans[i] = popcount(i);
        }
        
        return ans;
    }
    static constexpr auto testEntry = &Solution::countBits;
};

} // end namespace LC338


#endif /* LC338_h */
