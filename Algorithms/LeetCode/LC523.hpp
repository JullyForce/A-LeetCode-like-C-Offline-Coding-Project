//
//  LC523.hpp
//  Algorithms
//
//  Created by J.C. on 9/30/24.
//

#ifndef LC523_h
#define LC523_h

#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

namespace LC523 {

class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int n(nums.size());
        vector<int> accumMod(n+1, 0);
        partial_sum(nums.begin(), nums.end(), next(accumMod.begin()), [k] (const int a, const int b) {return (a + b) % k;});
        accumMod[1] = nums[0] % k;

        unordered_map<int,int> firstSeen;
        for (int i = 0; i < accumMod.size(); i ++) {
            int x = accumMod[i];
            if (firstSeen.count(x) != 0) {
                if (firstSeen[x] < i - 1) {
                    return true;
                }
            } else {
                firstSeen.emplace(x, i);
            }
        }

        return false;
    }
static constexpr auto testEntry = &Solution::checkSubarraySum;
};

} // end namespace LC523


#endif /* LC523_h */
