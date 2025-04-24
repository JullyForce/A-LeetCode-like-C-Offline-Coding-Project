//
//  LC3209.hpp
//  Algorithms
//
//  Created by Jun Chen on 7/8/24.
//

#ifndef LC3209_h
#define LC3209_h
#include <vector>

using namespace std;

namespace LC3209 {

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
    int lower(vector<int> & t, int n, int k, int start) {
        int l(start+1), r(n);
        while (r - l > 1) {
            int m = (l + r) / 2;
            int v = queryTree(t, n, start, m);
            if ((v & k) == k && v > k) {
                l = m;
            } else {
                r = m;
            }
        }
        return queryTree(t, n, start, l) == k ? l : r;
    }
    int upper(vector<int> & t, int n, int k, int start) {
        int l(start+1), r(n);
        while (r - l > 1) {
            int m = (l + r) / 2;
            int v = queryTree(t, n, start, m);
            if ((v & k) == k && v >= k) {
                l = m;
            } else {
                r = m;
            }
        }
        return queryTree(t, n, start, r) == k ? r+1 : r;
    }
public:
    long long countSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> tree(2*n, 0);
        buildTree(tree, n, nums);
        long long count(0);
        for (int i = 0; i < n; i ++) {
            int l = lower(tree, n, k, i);
            int r = upper(tree, n, k, i);
            count += (long long)(r - l);
        }
        return count;
    }
    static constexpr auto testEntry = &Solution::countSubarrays;
};

} // end namespace LC3209

#endif /* LC3209_h */
