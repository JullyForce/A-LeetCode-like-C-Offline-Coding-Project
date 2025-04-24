//
//  LC3255.hpp
//  Algorithms
//
//  Created by J.C. on 8/17/24.
//

#ifndef LC3255_h
#define LC3255_h

#include <vector>
#include <unordered_set>

using namespace std;

namespace LC3255 {

class Solution {
private:
    long long rookHelper(const vector<vector<int>> & board, unordered_set<int> & colsTaken, int startRow, int nRooks) {
        long long maxVal(INT_MIN);
        for (int i = startRow; i < board.size(); i ++) {
            for (int j = 0; j < board[0].size(); j ++) {
                if (colsTaken.find(j) != colsTaken.end()) {
                    continue;
                }
                colsTaken.emplace(j);
                long long val = board[i][j];
                if (nRooks > 1) {
                    val += rookHelper(board, colsTaken, i+1, nRooks-1);
                }
                colsTaken.erase(j);
                if (val > maxVal) {
                    maxVal = val;
                }
            }
        }
        return maxVal;
    }
public:
    long long maximumValueSum(vector<vector<int>>& board) {
        unordered_set<int> colsTaken{};
        return rookHelper(board, colsTaken, 0, 3);
    }
static constexpr auto testEntry = &Solution::maximumValueSum;
};

} // end namespace LC3255

#endif /* LC3255_h */
