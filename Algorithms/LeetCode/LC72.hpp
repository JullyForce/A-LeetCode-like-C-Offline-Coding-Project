//
//  LC72.hpp
//  Algorithms
//
//  Created by Jun Chen on 4/18/25.
//

#ifndef LC72_h
#define LC72_h

#include <vector>
#include <algorithm>

using namespace std;

namespace LC72 {

class Solution {
public:
    int minDistance(string word1, string word2) {
        int n1(word1.length()), n2(word2.length());
        vector<vector<int>> costSubstr(n1, vector<int>(n2, 0));

        if (n1 == 0 || n2 == 0) {
            return max(n1, n2);
        }

        if (word1[0] != word2[0]) {
            costSubstr[0][0] = 1;
        }
        // Two loops below can be optimized by finding the first match of in each string the start char in the other
        for (int j = 1; j < n2; j ++) {
            if (word1[0] == word2[j]) {
                costSubstr[0][j] = j;
            } else {
                costSubstr[0][j] = costSubstr[0][j-1] + 1;
            }
        }
        for (int i = 1; i < n1; i ++) {
            if (word1[i] == word2[0]) {
                costSubstr[i][0] = i;
            } else {
                costSubstr[i][0] = costSubstr[i-1][0] + 1;
            }
        }

        for (int i = 1; i < n1; i ++) {
            for (int j = 1; j < n2; j ++) {
                costSubstr[i][j] = max(i, j) + 1;
                costSubstr[i][j] = min(costSubstr[i][j], costSubstr[i-1][j-1] + 1);
                costSubstr[i][j] = min(costSubstr[i][j], costSubstr[i][j-1] + 1);
                costSubstr[i][j] = min(costSubstr[i][j], costSubstr[i-1][j] + 1);
                if (word1[i] == word2[j]) {
                    costSubstr[i][j] = costSubstr[i-1][j-1];
                }
            }
        }

        return costSubstr.back().back();
    }
static constexpr auto testEntry = &Solution::minDistance;
};

} // end namespace LC72

#endif /* LC72_h */
