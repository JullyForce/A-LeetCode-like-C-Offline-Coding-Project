//
//  LC85.hpp
//  Algorithms
//
//  Created by Jun Chen on 8/27/24.
//

#ifndef LC85_h
#define LC85_h

#include <vector>
#include <algorithm>

using namespace std;

namespace LC85 {

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int m(matrix.size()), n(matrix[0].size());
        int maxArea(0);
        vector<int> hStk;
        vector<unsigned short> dpLast(n, 0);
        for (int i = 0; i < m; i ++) {
            vector<unsigned short> dp(n, 0);
            transform(matrix[i].begin(), matrix[i].end(), dpLast.begin(), dp.begin(),
                [](const char a, const unsigned short b) -> unsigned short { return a == '0' ? 0 : b + 1; });

            hStk.clear();
            int lastH(0);
            for (int j = 0; j < n; j ++) {
                if (dp[j] > lastH) {
                    hStk.push_back(j);
                }
                lastH = dp[j];
            }
            while (!hStk.empty()) {
                int l = hStk.back();
                hStk.pop_back();
                for (int j = l, ht = dp[l]; j < n && ht > 0; j ++) {
                    if (dp[j] < ht) {
                        ht = dp[j];
                    }
                    int area = (j-l+1) * ht;
                    if (maxArea < area) {
                        maxArea = area;
                    }
                }
            }

            dpLast = move(dp);
        }
        return maxArea;
    }
static constexpr auto testEntry = &Solution::maximalRectangle;
};

} // end namespace LC85

#endif /* LC85_h */
