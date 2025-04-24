//
//  LC3197.hpp
//  Algorithms
//
//  Created by J.C. on 6/24/24.
//

#ifndef LC3197_h
#define LC3197_h

#include <vector>

using namespace std;

namespace LC3197 {

class Solution {
private:
    int minimumArea(vector<vector<int>>& grid, int u, int d, int l, int r) {
        int idxN(d), idxS(u);
        int idxW(r), idxE(l);
        for (int i = u; i < d; i ++)  {
            for (int j = l; j < r; j ++) {
                if (grid[i][j] == 1) {
                    if (idxN > i) {
                        idxN = i;
                    }
                    if (idxW > j) {
                        idxW = j;
                    }
                    if (idxS < i) {
                        idxS = i;
                    }
                    if (idxE < j) {
                        idxE = j;
                    }
                }
            }
        }
        return idxS < idxN || idxE < idxW ? 0 : (idxS - idxN + 1) * (idxE - idxW + 1);
    }
public:
    int minimumSum(vector<vector<int>>& grid) {
        int minSum(INT_MAX);
        int m(grid.size()), n(grid[0].size());
        for (int i = 1; i < m; i ++) {
            for (int j = 1; j < n; j ++) {
                {
                    //__|__
                    //
                    int sum(0);
                    sum += minimumArea(grid, 0, i, 0, j);
                    sum += minimumArea(grid, 0, i, j, n);
                    sum += minimumArea(grid, i, m, 0, n);
                    minSum = sum < minSum ? sum : minSum;
                }
                {
                    //  |__
                    //  |
                    int sum(0);
                    sum += minimumArea(grid, 0, i, j, n);
                    sum += minimumArea(grid, i, m, j, n);
                    sum += minimumArea(grid, 0, m, 0, j);
                    minSum = sum < minSum ? sum : minSum;
                }
                {
                    //__ __
                    //  |
                    int sum(0);
                    sum += minimumArea(grid, 0, i, 0, n);
                    sum += minimumArea(grid, i, m, 0, j);
                    sum += minimumArea(grid, i, m, j, n);
                    minSum = sum < minSum ? sum : minSum;
                }
                {
                    //__|
                    //  |
                    int sum(0);
                    sum += minimumArea(grid, 0, i, 0, j);
                    sum += minimumArea(grid, i, m, 0, j);
                    sum += minimumArea(grid, 0, m, j, n);
                    minSum = sum < minSum ? sum : minSum;
                }
            }
        }
        return minSum;
    }
    static constexpr auto testEntry = &Solution::minimumSum;
};

} // end namespace LC3197


#endif /* LC3197_h */
