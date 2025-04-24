//
//  LC100365.hpp
//  Algorithms
//
//  Created by Jun Chen on 7/20/24.
//

#ifndef LC100365_h
#define LC100365_h

#include <vector>
#include <bitset>

using namespace std;

namespace LC100365 {

class Solution {
public:
    int minChanges(vector<int>& nums, int k) {
        #define abs_sub(a, b) (a) > (b) ? (a) - (b) : (b) - (a)
        int n(nums.size());
        vector<int> costDiff(k+1,0);
        vector<int> costAdj(k+1, 0);
        for (int i = 0; i < n/2; i ++) {
            int v1(nums[i]), v2(nums[n-1-i]);
            int d0 = abs_sub(v1, v2);

            int r1 = k - v1 > v1 ? k-v1 : v1;
            int r2 = k - v2 > v2 ? k-v2 : v2;
            int r = r1 > r2 ? r1 : r2;
            if (r + 1 <= k) {
                costDiff[r+1] = 1;
            }
            costAdj[d0] ++;
        }
        int sum = n/2;
        for (int i = 0; i <= k; i ++) {
            sum += costDiff[i];
            costDiff[i] = sum - costAdj[i];
        }

        return *min_element(costDiff.begin(), costDiff.end());
    }
    static constexpr auto testEntry = &Solution::minChanges;
};

} // end namespace LC100365


#endif /* LC100365_h */
