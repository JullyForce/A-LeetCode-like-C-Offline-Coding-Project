//
//  LC100308.hpp
//  Algorithms
//
//  Created by J.C. on 5/18/24.
//

#ifndef LC100308_h
#define LC100308_h

#include <vector>
#include <algorithm>

using namespace std;

namespace LC100308 {
class Solution {
public:
    vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries) {
        int l(0);
        int m = nums[0] % 2;
        // vector<pair<int,int>> ranges;
        vector<int> L;
        vector<int> R;
        for (int i = 1; i < nums.size(); i ++) {
            if (nums[i] % 2 == m) {
                // ranges.emplace(make_pair(l, i));
                L.push_back(l);
                R.push_back(i);
                l = i;
            }
            m = nums[i] % 2;
        }
        // ranges.emplace(make_pair(l, nums.size()));
        L.push_back(l);
        R.push_back(nums.size());
        vector<bool> ret;
        for (auto & q : queries) {
            int & l = q[0];
            int & r = q[1];
            auto it = upper_bound(R.begin(), R.end(), r);
            int i = distance(R.begin(), it);
            if (L[i] <= l) {
                ret.push_back(true);
            } else {
                ret.push_back(false);
            }
        }
        return ret;
    }
    static constexpr auto testEntry = &Solution::isArraySpecial;
};
} // end namespace LC100308

#endif /* LC100308_h */
