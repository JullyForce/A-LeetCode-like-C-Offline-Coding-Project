//
//  LC3276.hpp
//  Algorithms
//
//  Created by J.C. on 9/1/24.
//

#ifndef LC3276_h
#define LC3276_h

#include <vector>
#include <algorithm>

using namespace std;

namespace LC3276 {

class Solution {
private:
    int bt(vector<vector<int>>& g, vector<bool> & selV, int m, int n, int r, int val) {
        if (r == m) {
            return val;
        }
        int ans(0);
        for (int i = 0; i < n; i ++) {
            int v(g[r][i]);
            if (selV[v]) {
                continue;
            }
            selV[v] = true;
            int trial = bt(g, selV, m, n, r+1, val+v);
            selV[v] = false;
            if (trial > ans) {
                ans = trial;
            }
        }
        // int trial = bt(g, selV, m, n, r+1, val);
        // if (trial > ans) {
        //     ans = trial;
        // }
        return ans;
    }
public:
    int maxScore(vector<vector<int>>& grid) {
        int m(grid.size()), n(grid[0].size());
        vector<bool> selV(101, false);
        return bt(grid, selV, m, n, 0, 0);
    }
static constexpr auto testEntry = &Solution::maxScore;
};

} // end namespace LC3276

#endif /* LC3276_h */
