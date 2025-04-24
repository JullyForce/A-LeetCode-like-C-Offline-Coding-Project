//
//  LC1521.hpp
//  Algorithms
//
//  Created by J.C. on 6/1/24.
//

#ifndef LC1521_h
#define LC1521_h

#include <algorithm>
#include <vector>

using namespace std;

namespace LC1521{
class Solution {
private:
    void buildTree(vector<int> & t, int n, vector<int> & arr) {
        for (int i = 0; i < n; i ++) {
            t[n+i] = arr[i];
        }
        for (int i = n-1; i > 0; i --) {
            t[i] = t[i<<1] & t[i<<1 | 1];
        }
    }
    int queryTree(vector<int> & t, int n, int l, int r) {
        int res(INT_MAX);
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                res &= t[l++];
            }
            if (r & 1) {
                res &= t[--r];
            }
        }
        return res;
    }
    void bisect(vector<int> & t, int n, int k, int start, int l, int r, int & minDiff) {
        while (r - l > 1) {
            int m = (l + r) / 2;
            int val = queryTree(t, n, start, m);
            if (val > k) {
                l = m;
            } else {
                r = m;
            }
        }
        int vL = queryTree(t, n, start, l);
        if (abs(vL-k) < minDiff) {
            minDiff = abs(vL-k);
        }
        int vR = queryTree(t, n, start, r);
        if (abs(vR-k) < minDiff) {
            minDiff = abs(vR-k);
        }
    }
public:
    int closestToTarget(vector<int>& arr, int target) {
        int n = arr.size();
        vector<int> tree(2*n, 0);
        buildTree(tree, n, arr);
        int dist(INT_MAX);
        for (int i = 0; i < n; i ++) {
            bisect(tree, n, target, i, i+1, n, dist);
        }
        return dist;
    }
    static constexpr auto testEntry = &Solution::closestToTarget;
};

} // end namespace LC1521

#endif /* LC1521_h */
