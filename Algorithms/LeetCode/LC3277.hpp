//
//  LC3277.hpp
//  Algorithms
//
//  Created by J.C. on 9/3/24.
//

#ifndef LC3277_h
#define LC3277_h

#include <vector>
#include <algorithm>

using namespace std;

namespace LC3277 {

class Solution_2D_segtree_misunderstood_the_problem {
private:
    void buildTree(vector<vector<int>> & t, int n, const vector<int> & bwdCumXOR) {
        for (int i = 0; i < n; i ++) {
            for (int j = 0; j < n; j ++) {
                if (i < j) {
                    t[n+i][n+j] = bwdCumXOR[i];
                    if (j + 1 < n) {
                        t[n+i][n+j] ^= bwdCumXOR[j+1];
                    }
                } else {
                    t[n+i][n+j] = bwdCumXOR[j];
                    if (i + 1 < n) {
                        t[n+i][n+j] ^= bwdCumXOR[i+1];
                    }
                }
            }
            for (int j = n-1; j > 0; j --) {
                t[n+i][j] = MAX(t[n+i][j<<1], t[n+i][j<<1 | 1]);
            }
        }
        for (int i = n-1; i > 0; i --) {
            for (int j = 0; j < n; j ++) {
                t[i][n+j] = MAX(t[i<<1][n+j], t[i<<1 | 1][n+j]);
            }
            for (int j = n-1; j > 0; j --) {
                t[i][j] = MAX(t[i][j<<1], t[i][j<<1 | 1]);
            }
        }
    }
    int queryTreeRow(vector<vector<int>> & t, int n, int rowIdx, int l, int r) {
        int res(INT_MIN);
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                res = MAX(res, t[rowIdx][l]);
                l ++;
            }
            if (r & 1) {
                -- r;
                res = MAX(res, t[rowIdx][r]);
            }
        }
        return res;
    }
    int queryTree(vector<vector<int>> & t, int n, int l, int r) {
        int res(INT_MIN);
        int u(l), d(r);
        for (u += n, d += n; u < d; u >>= 1, d >>= 1) {
            if (u & 1) {
                int rowMax = queryTreeRow(t, n, u++, l, r);
                res = MAX(res, rowMax);
            }
            if (d & 1) {
                int rowMax = queryTreeRow(t, n, --d, l, r);
                res = MAX(res, rowMax);
            }
        }
        return res;
    }
public:
    vector<int> maximumSubarrayXor(vector<int>& nums, vector<vector<int>>& queries) {
        int n(nums.size());
        vector<vector<int>> max2DTree(2*n, vector<int>(2*n, 0));
        vector<int> bwdCumXOR(n, 0);
        partial_sum(nums.crbegin(), nums.crend(), bwdCumXOR.rbegin(), bit_xor<int>());

        buildTree(max2DTree, n, bwdCumXOR);

        vector<int> ans;
        for (auto & q : queries) {
            ans.push_back(queryTree(max2DTree, n, q[0], q[1]+1));
        }

        return ans;
    }
    static constexpr auto testEntry = &Solution_2D_segtree_misunderstood_the_problem::maximumSubarrayXor;
};

class Solution {
private:
    void buildTree(vector<vector<int>> & t, int n, const vector<vector<int>> & arr) {
        
        for (int i = 0; i < n; i ++) {
            for (int j = 0; j < n; j ++) {
                if (i <= j) {
                    t[n+i][n+j] = arr[j-i][i];
                } else {
                    t[n+i][n+j] = arr[i-j][j];
                }
            }
            for (int j = n-1; j > 0; j --) {
                t[n+i][j] = MAX(t[n+i][j<<1], t[n+i][j<<1 | 1]);
            }
        }
        for (int i = n-1; i > 0; i --) {
            for (int j = 0; j < n; j ++) {
                t[i][n+j] = MAX(t[i<<1][n+j], t[i<<1 | 1][n+j]);
            }
            for (int j = n-1; j > 0; j --) {
                t[i][j] = MAX(t[i][j<<1], t[i][j<<1 | 1]);
            }
        }
    }
    int queryTreeRow(vector<vector<int>> & t, int n, int rowIdx, int l, int r) {
        int res(INT_MIN);
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                res = MAX(res, t[rowIdx][l]);
                l ++;
            }
            if (r & 1) {
                -- r;
                res = MAX(res, t[rowIdx][r]);
            }
        }
        return res;
    }
    int queryTree(vector<vector<int>> & t, int n, int l, int r) {
        int res(INT_MIN);
        int u(l), d(r);
        for (u += n, d += n; u < d; u >>= 1, d >>= 1) {
            if (u & 1) {
                int rowMax = queryTreeRow(t, n, u++, l, r);
                res = MAX(res, rowMax);
            }
            if (d & 1) {
                int rowMax = queryTreeRow(t, n, --d, l, r);
                res = MAX(res, rowMax);
            }
        }
        return res;
    }
public:
    vector<int> maximumSubarrayXor(vector<int>& nums, vector<vector<int>>& queries) {
        int n(nums.size());

        vector<vector<int>> triangle(n, vector<int>(n, 0));
        triangle[0] = vector<int>(nums);
        for (int i = 1; i < n; i ++) {
            for (int j = 0; j < n-i; j ++) {
                triangle[i][j] = triangle[i-1][j] ^ triangle[i-1][j+1];
            }
        }

        for (int i = 1; i < n; i ++) {
            for (int j = 0; j < n-i; j ++) {
                triangle[i][j] = MAX(triangle[i][j], triangle[i-1][j]);
                triangle[i][j] = MAX(triangle[i][j], triangle[i-1][j+1]);
            }
        }

        vector<int> ans;
        for (auto & q : queries) {
            ans.push_back(triangle[q[1]-q[0]][q[0]]);
        }

        return ans;

        // vector<vector<int>> max2DTree(2*n, vector<int>(2*n, 0));
        // buildTree(max2DTree, n, triangle);
        // triangle.clear();

        // vector<int> ans;
        // for (auto & q : queries) {
        //     ans.push_back(queryTree(max2DTree, n, q[0], q[1]+1));
        // }

        // return ans;
    }
static constexpr auto testEntry = &Solution::maximumSubarrayXor;
};

} // end namespace LC3277

#endif /* LC3277_h */
