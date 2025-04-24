//
//  LC3229.hpp
//  Algorithms
//
//  Created by Jun Chen on 7/21/24.
//

#ifndef LC3229_h
#define LC3229_h

#include <vector>
#include <algorithm>

using namespace std;

namespace LC3229{

class Solution {
private:
    struct rec {
        int rmin;
        int rmax;
        rec (int a, int b) : rmin(a), rmax(b) {}
    };
    void buildTree(vector<rec> & t, int n, vector<int> & arr) {
        for (int i = 0; i < n; i ++) {
            t[n+i].rmin = arr[i];
            t[n+i].rmax = arr[i];
        }
        for (int i = n-1; i > 0; i --) {
            t[i].rmin = min(t[i<<1].rmin, t[i<<1 | 1].rmin);
            t[i].rmax = max(t[i<<1].rmax, t[i<<1 | 1].rmax);
        }
    }
    pair<int, int> queryTree(vector<rec> & t, int n, int l, int r) {
        int rmin(INT_MAX), rmax(INT_MIN);
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                rmin = min(rmin, t[l].rmin);
                rmax = max(rmax, t[l].rmax);
                l ++;
            }
            if (r & 1) {
                -- r;
                rmin = min(rmin, t[r].rmin);
                rmax = max(rmax, t[r].rmax);

            }
        }
        return make_pair(rmin, rmax);
    }
    void updateTree(vector<rec> & t, int n, int i, int delta) {
        t[n+i].rmin += delta;
        t[n+i].rmax += delta;
        for (int j = i + n; j > 1; j >>= 1) {
            t[j>>1].rmin = min(t[j].rmin, t[j^1].rmin);
            t[j>>1].rmax = max(t[j].rmax, t[j^1].rmax);
        }
    }
public:
    long long minimumOperations(vector<int>& nums, vector<int>& target) {
        int n(nums.size());
        for (int i = 0; i < n; i ++) {
            nums[i] -= target[i];
        }
        vector<rec> sTree(2*n, rec(INT_MAX, INT_MIN));
        fill(sTree.begin(), sTree.end(), rec(0, 0));
        buildTree(sTree, n, nums);

        int rmin, rmax;
        long long res(0);
        int L(0);
        while (L < n) {
            int l(L);
            if (sTree[n+l].rmin == 0) {
                int l2(n);
                while (l2 - l > 1) {
                    int m = (l + l2) / 2;
                    tie(rmin, rmax) = queryTree(sTree, n, l , m);
                    if (rmin != 0 || rmax != 0) {
                        l2 = m;
                    } else {
                        l = m;
                    }
                }
                tie(rmin, rmax) = queryTree(sTree, n, l , l2);
                if (rmin != 0 || rmax != 0) {
                    l2 = l;
                }
                L = l2;
            } else if (sTree[n+l].rmin > 0) {
                int l2(n);
                while (l2 - l > 1) {
                    int m = (l + l2) / 2;
                    tie(rmin, rmax) = queryTree(sTree, n, l, m);
                    if (rmin <= 0) {
                        l2 = m;
                    } else {
                        l = m;
                    }
                }
                tie(rmin, rmax) = queryTree(sTree, n, L, l2);
                if (rmin <= 0) {
                    l2 = l;
                    tie(rmin, rmax) = queryTree(sTree, n, L, l2);
                }
                res += (long long) rmin;
                for (int i = L; i < l2; i ++) {
                    updateTree(sTree, n, i, -rmin);
                }
            } else {
                int l2(n);
                while (l2 - l > 1) {
                    int m = (l + l2) / 2;
                    tie(rmin, rmax) = queryTree(sTree, n, l, m);
                    if (rmax >= 0) {
                        l2 = m;
                    } else {
                        l = m;
                    }
                }
                tie(rmin, rmax) = queryTree(sTree, n, L, l2);
                if (rmax >= 0) {
                    l2 = l;
                    tie(rmin, rmax) = queryTree(sTree, n, L, l2);
                }
                res -= (long long)rmax;
                for (int i = L; i < l2; i ++) {
                    updateTree(sTree, n, i, -rmax);
                }
            }
        }
        return res;
    }
    static constexpr auto testEntry = &Solution::minimumOperations;
};

} // end namespace LC3229


#endif /* LC3229_h */
