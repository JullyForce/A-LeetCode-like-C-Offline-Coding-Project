//
//  LC3363.hpp
//  Algorithms
//
//  Created by J.C. on 11/23/24.
//

#ifndef LC3363_h
#define LC3363_h

#include <algorithm>
#include <vector>

using namespace std;

namespace LC3363 {

class Solution {
private:
    int findOptmBPrev(const vector<vector<vector<vector<int>>>>& dp, int n, int cGy, int cGx, int cRx, int cBy) {
        int ans(dp[cGy][cGx][cRx][cBy]); // B look left
        if (cBy < n-1) { // B look down left
            ans = MAX(ans, dp[cGy][cGx][cRx][cBy+1]);
        }
        if (cBy > 0) { // B look up left
            ans = MAX(ans, dp[cGy][cGx][cRx][cBy-1]);
        }
        return ans;
    }
    int findOptmRPrev(const vector<vector<vector<vector<int>>>>& dp, int n, int cGy, int cGx, int cRx, int cBy) {
        int ans(findOptmBPrev(dp, n, cGy, cGx, cRx, cBy)); // R look up
        if (cRx < n-1) { // R look up right
            ans = MAX(ans, findOptmBPrev(dp, n, cGy, cGx, cRx+1, cBy));
        }
        if (cRx > 0) { // R look up left
            ans = MAX(ans, findOptmBPrev(dp, n, cGy, cGx, cRx-1, cBy));
        }
        return ans;
    }
    int findOptmGPrev(const vector<vector<vector<vector<int>>>>& dp, int n, int t, int cGy, int cGx, int cRx, int cBy) {
        int ans(0);
        if (cGx > 0) { // G look left
            ans = MAX(ans, findOptmRPrev(dp, n, cGy, cGx-1, cRx, cBy));
        }
        if (cGy > 0) { // G look up
            ans = MAX(ans, findOptmRPrev(dp, n, cGy-1, cGx, cRx, cBy));
        }
        if (cGx > 0 && cGy > 0 && cGx + cGy > t) { // G look left-up
            ans = MAX(ans, findOptmRPrev(dp, n, cGy-1, cGx-1, cRx, cBy));
        }
        return ans;
    }
public:
    int maxCollectedFruits(vector<vector<int>>& fruits) {
        int n(fruits.size());
        vector<vector<vector<vector<int>>>> dp(n, vector<vector<vector<int>>>(n, vector<vector<int>>(n, vector<int>(n, 0)))); // [cG.y][cG.x][cR.x][cB.y]
        dp[0][0][0][0] = fruits[0][0] + fruits[0][n-1] + fruits[n-1][0];
        for (int t = 1; t < n; t ++) {
            auto tmp = vector<vector<vector<vector<int>>>>(n, vector<vector<vector<int>>>(n, vector<vector<int>>(n, vector<int>(n, 0))));
            for (int cGy = 0; cGy <= t; cGy ++) {
                for (int cGx = 0; cGx <= t; cGx ++) {
                    if (cGx + cGy < t) {
                        continue;
                    }
                    for (int cRx = n-1; cRx >= n-1-t; cRx --) {
                        for (int cBy = n-1; cBy >= n-1-t; cBy --) {
                            int delta(0);
                            delta += fruits[cGy][cGx];
                            if (cGy != t || cGx != cRx) {
                                delta += fruits[t][cRx];
                            }
                            if ((cGx != t || cGy != cBy) &&
                                (cRx != t || cBy != t)) {
                                delta += fruits[cBy][t];
                            }
                            tmp[cGy][cGx][cRx][cBy] = findOptmGPrev(dp, n, t, cGy, cGx, cRx, cBy) + delta;
                        }
                    }
                }
            }
            swap(dp, tmp);
        }
        int ans(0);
        for (int cGy = 0; cGy < n; cGy ++) {
            for (int cGx = 0; cGx < n; cGx ++) {
                for (int cRx = 0; cRx < n; cRx ++) {
                    for (int cBy = 0; cBy < n; cBy ++) {
                        ans = MAX(ans, dp[cGy][cGx][cRx][cBy]);
                    }
                }
            }
        }

        return ans;
    }
    static constexpr auto testEntry = &Solution::maxCollectedFruits;
};

} // end namespace LC3363

#endif /* LC3363_h */
