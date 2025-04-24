//
//  LC100312.hpp
//  Algorithms
//
//  Created by Jun Chen on 5/11/24.
//

#ifndef LC100312_h
#define LC100312_h

#include <vector>
#include <cmath>

using namespace std;

namespace LC100312
{

class Solution {
private:
    int permHelper(vector<int> & nums, vector<int> & perm, vector<int> & permOptm,vector<bool> & valUsed, int n, int idx, int c) {
        if (idx == n) {
            return c + abs(perm[n-1] - nums[perm[0]]);
        }
        int minCost = INT_MAX;
        for (int i = 0; i < n; i ++) {
            if (!valUsed[i]) {
                perm[idx] = i;
                valUsed[i] = true;
                int currCost = c;
                if (idx != 0) {
                    currCost += abs(perm[idx-1] - nums[perm[idx]]);
                }
                int totalCost = permHelper(nums, perm, permOptm, valUsed, n, idx + 1, currCost);
                valUsed[i] = false;
                if (totalCost < minCost) {
                    minCost = totalCost;
                    copy(perm.cbegin() + idx, perm.cend(), permOptm.begin() + idx);
                }
            }
        }
        return minCost;
    }
public:
    vector<int> findPermutation(vector<int>& nums) {
        int n = nums.size();
        vector<int> perm(n, 0);
        vector<int> permOptm(n, 0);
        vector<bool> valUsed(n, false);
        permHelper(nums, perm, permOptm, valUsed, n, 0, 0);
        return permOptm;
    }
    static constexpr auto testEntry = &Solution::findPermutation;
};

} // end namespace LC100312

#endif /* LC100312_h */
