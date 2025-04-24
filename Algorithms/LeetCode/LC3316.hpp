//
//  LC3316.hpp
//  Algorithms
//
//  Created by J.C. on 10/30/24.
//

#ifndef LC3316_h
#define LC3316_h

#include <algorithm>
#include <vector>

using namespace std;

namespace LC3316 {

class Solution {
public:
    int maxRemovals(string source, string pattern, vector<int>& targetIndices) {
        int n(source.size());
        int m(pattern.size());
        vector<int> dp(targetIndices.size()+1, 0);
        int idx(0);
        for (int i = 0; i < n; i ++) {
            auto tmp = dp;
            for (int j = 0; j <= idx; j ++) {
                if (dp[j] < m && source[i] == pattern[dp[j]]) {
                    dp[j] ++;
                }
            }
            if (idx < targetIndices.size() && targetIndices[idx] == i) {
                for (int j = 1; j <= idx; j ++) {
                    if (tmp[j-1] > dp[j]) {
                        dp[j] = tmp[j-1];
                    }
                }
                dp[idx+1] = tmp[idx];
                idx ++;
            }
        }
        for (int j = dp.size()-1; j >= 0; j --) {
            if (dp[j] == m) {
                return j;
            }
        }
        return -1;
    }
static constexpr auto testEntry = &Solution::maxRemovals;
};

} // end namespace LC3316

#endif /* LC3316_h */
