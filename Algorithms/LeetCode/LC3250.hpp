//
//  LC0000.hpp
//  Algorithms
//
//  Created by Jun Chen on 8/10/24.
//

#ifndef LC0000_h
#define LC0000_h

#include <vector>

using namespace std;

namespace LC3250 {

class Solution {
public:
    int countOfPairs(vector<int>& nums) {
        int n(nums.size());
        vector<int> inc(n, 0);
        vector<int> dec(n, 0);
        dec[0] = nums[0];
        for (int i = 1; i < n; i ++ ) {
            int diff = nums[i] - nums[i-1];
            if (diff > 0) {
                inc[i] = inc[i-1] + diff;
            } else {
                inc[i] = inc[i-1];
            }
            dec[i] = nums[i] - inc[i];
        }
        int avail(dec[n-1]);
        vector<int> dp(avail+1, 1);
        for (int i = 0; i < n; i ++) {
            partial_sum(dp.cbegin(), dp.cend(), dp.begin());
        }
        return dp.back();
    }
static constexpr auto testEntry = &Solution::countOfPairs;
};

} // end namespace LC3250


#endif /* LC0000_h */
