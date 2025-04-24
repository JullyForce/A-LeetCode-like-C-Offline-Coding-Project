//
//  LC3161.hpp
//  Algorithms
//
//  Created by J.C. on 6/10/24.
//

#ifndef LC3161_h
#define LC3161_h

#include <vector>

using namespace std;

namespace LC3161 {

class Solution {
private:
    void buildTree(vector<int>& t, int n) {
        t[n] = n;
        for (int i = n-1; i > 0; i --) {
            t[i] = max(t[i<<1], t[(i<<1) | 1]);
        }
    }
    void updateTree(vector<int>& t, int n, int i) {
        if (t[i + n] != -1) {
            return;
        }
        int idx = i + n;
        // find the left neighbor obstacle
        bool foundLeftBranch(false);
        while (!foundLeftBranch) {
            if (!(idx & 1)) {
                foundLeftBranch |= t[--idx] != -1;
            } else if (t[idx-1] != -1) {
                idx --;
                foundLeftBranch = true;
            } else {
                idx >>= 1;
            }
        }
        while (idx < n) {
            // Go down the tree
            idx <<= 1;
            // Go right if there is recorded obstacle
            if (t[idx | 1] != -1) {
                idx |= 1;
            }
        }
        // update neighbor and its ancester chain
        int newDist = t[idx] + idx - n - i;
        t[idx] = i + n - idx;
        for (int j = idx; j > 1; j >>= 1) {
            t[j>>1] = max(t[j], t[j^1]);
        }
        // update the node itself and ancesters
        idx = i+n;
        t[idx] = newDist;
        for (int j = idx; j > 1; j >>= 1) {
            t[j>>1] = max(t[j], t[j^1]);
        }
    }
    bool queryTree(vector<int>& t, int n, int r, int size) {
        int l(0);
        if (r <= 0) {
            return false;
        }
        bool res(false);
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                res |= (t[l++] >= size);
            }
            if (r & 1) {
                res |= (t[--r] >= size);
            }
        }
        return res;
    }
public:
    vector<bool> getResults(vector<vector<int>>& queries) {
        int n = 50001;
        vector<int> sTree(2*n, -1);
        buildTree(sTree, n);
        vector<bool> ans;
        for (auto & q : queries) {
            if (q[0] == 1) {
                updateTree(sTree, n, q[1]);
            } else {
                ans.push_back(queryTree(sTree, n, q[1]-q[2]+1, q[2]));
            }
        }
        return ans;
    }
    static constexpr auto testEntry = &Solution::getResults;
};

} // end namespace LC3161

#endif /* LC3161_h */
