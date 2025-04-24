//
//  LC100316.hpp
//  Algorithms
//
//  Created by Jun Chen on 6/15/24.
//

#ifndef LC100316_h
#define LC100316_h

#include <vector>
#include <algorithm>

using namespace std;

namespace LC100316{


class Solution {
public:
    long long maximumTotalDamage(vector<int>& power) {
        sort(power.begin(), power.end());
        vector<int> dpIdx(4, -4);
        vector<long long> dp(4, 0);
        int i(0);
        auto it = power.begin();
        while (it != power.end()) {
            auto itR = upper_bound(it, power.end(), *it);
            int numOccur = distance(it, itR);
            int i0 = i % 4;
            int i1 = (i+3) % 4;
            int i2 = (i+2) % 4;
            int i3 = (i+1) % 4;
            if (dpIdx[i1] < *it - 2) {
                dp[i0] = dp[i1] + *it * numOccur;
            } else if (dpIdx[i2] < *it - 2) {
                dp[i0] = dp[i2] + *it * numOccur;
            } else {
                dp[i0] = dp[i3] + *it * numOccur;
            }

            if (dp[i1] > dp[i0]) {
                dp[i0] = dp[i1];
            }
            if (dp[i2] > dp[i0]) {
                dp[i0] = dp[i2];
            }
            if (dp[i3] > dp[i0]) {
                dp[i0] = dp[i3];
            }

            dpIdx[i0] = *it;
            it = itR;
            i ++;
        }
        sort(dp.begin(), dp.end());
        return dp.back();
    }
    static constexpr auto testEntry = &Solution::maximumTotalDamage;
};

} // end namespace LC100316


#endif /* LC100316_h */
