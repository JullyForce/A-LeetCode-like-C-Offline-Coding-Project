//
//  LC100306.hpp
//  Algorithms
//
//  Created by J.C. on 5/25/24.
//

#ifndef LC100306_h
#define LC100306_h

#include <vector>

using namespace std;

namespace LC100306 {

class Solution {
private:
    int findMaxSum(vector<int>& nums, vector<long long>& dp, int start) {
        if (start < 2) {
            dp[0] = nums[0] > 0 ? nums[0] : 0;
            if (dp.size() >= 2) {
                dp[1] = nums[1] > 0 ? nums[1] : 0;
                if (dp[1] < dp[0]) {
                    dp[1] = dp[0];
                }
            }
        }
        for (int i = start > 1 ? start : 2; i < nums.size(); i ++) {
            dp[i] = dp[i-2];
            if (nums[i] > 0) {
                dp[i] += nums[i];
            }
            if (dp[i-1] > dp[i]) {
                dp[i] = dp[i-1];
            }
        }
        return dp.back() % 1000000007;
    }
public:
    int maximumSumSubsequence(vector<int>& nums, vector<vector<int>>& queries) {
        int sum(0);
        vector<long long> dp(nums.size(), 0);
        findMaxSum(nums, dp, 0);
        for (auto & q : queries) {
            nums[q[0]] = q[1];
            int ret = findMaxSum(nums, dp, q[0]);
            sum = (sum + ret) % 1000000007;
        }
        return sum;
    }
    static constexpr auto testEntry = &Solution::maximumSumSubsequence;
};


} // end namespace LC100306

#endif /* LC100306_h */
