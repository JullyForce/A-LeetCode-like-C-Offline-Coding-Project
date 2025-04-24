//
//  LC100317.hpp
//  Algorithms
//
//  Created by J.C. on 6/15/24.
//

#ifndef LC100317_h
#define LC100317_h

#include <vector>
#include <algorithm>

using namespace std;

namespace LC100317{


class Solution {
private:
    void buildTree(vector<int> & t, int n, vector<int> & arr) {
        for (int i = 1; i < n-1; i ++) {
            t[n+i] = (arr[i] > arr[i-1] && arr[i] > arr[i+1]) ? 1 : 0;
        }
        for (int i = n-1; i > 0; i --) {
            t[i] = t[i<<1] + t[i<<1 | 1];
        }
    }
    int queryTree(vector<int> & t, int n, int l, int r) {
        int res(0);
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                res += t[l++];
            }
            if (r & 1) {
                res += t[--r];
            }
        }
        return res;
    }
    void updateTree(vector<int> & t, int n, vector<int> & arr, int i, int val) {
        arr[i] = val;
        if (i > 0 && i < n-1) {
            t[n+i] = (arr[i] > arr[i-1] && arr[i] > arr[i+1]) ? 1 : 0;
            for (int j = i + n; j > 1; j >>= 1) {
                t[j>>1] = t[j] + t[j^1];
            }
            if (i-1 > 0) {
                t[n+i-1] = (arr[i-1] > arr[i-2] && arr[i-1] > arr[i]) ? 1 : 0;
                for (int j = i-1 + n; j > 1; j >>= 1) {
                    t[j>>1] = t[j] + t[j^1];
                }
            }
            if (i+1 < n-1) {
                t[n+i+1] = (arr[i+1] > arr[i] && arr[i+1] > arr[i+2]) ? 1 : 0;
                for (int j = i+1 + n; j > 1; j >>= 1) {
                    t[j>>1] = t[j] + t[j^1];
                }
            }
        } else if (i == 0) {
            if (i+1 < n-1) {
                t[n+i+1] = (arr[i+1] > arr[i] && arr[i+1] > arr[i+2]) ? 1 : 0;
                for (int j = i+1 + n; j > 1; j >>= 1) {
                    t[j>>1] = t[j] + t[j^1];
                }
            }
        } else {
            if (i-1 > 0) {
                t[n+i-1] = (arr[i-1] > arr[i-2] && arr[i-1] > arr[i]) ? 1 : 0;
                for (int j = i-1 + n; j > 1; j >>= 1) {
                    t[j>>1] = t[j] + t[j^1];
                }
            }
        }
    }
public:
    vector<int> countOfPeaks(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<int> sTree(2*n, 0);
        buildTree(sTree, n, nums);
        vector<int> ans;
        for (auto & q : queries) {
            if (q[0] == 1) {
                ans.push_back(queryTree(sTree, n, q[1]+1, q[2]));
            } else {
                updateTree(sTree, n, nums, q[1], q[2]);
            }
        }
        return ans;
        
    }
    static constexpr auto testEntry = &Solution::countOfPeaks;
};

} // end namespace LC100317


#endif /* LC100317_h */
