//
//  LC3342.hpp
//  Algorithms
//
//  Created by J.C. on 11/3/24.
//

#ifndef LC3342_h
#define LC3342_h

#include <algorithm>
#include <vector>

using namespace std;

namespace LC3342 {

class Solution {
public:
    int minTimeToReach(vector<vector<int>>& moveTime) {
        int n(moveTime.size()), m(moveTime[0].size());
        vector<vector<int>> visited(n, vector<int>(m, -1));
        for (int i = 0; i < n; i ++) {
            for (int j = 0; j < m; j ++) {
                moveTime[i][j] += 2 - (i + j) % 2;
            }
        }
        using coord = tuple<int, int, int>;
        auto cmp = [](const coord& a, const coord& b) {
            return get<0>(a) > get<0>(b);
        };
        priority_queue<coord, vector<coord>, decltype(cmp)> pQ(cmp);
        pQ.push({0,0,0});
        while (!pQ.empty()) {
            auto [t, i, j] = pQ.top();
            pQ.pop();
            if (visited[i][j] >= 0 && t >= visited[i][j]) {
                continue;
            }
            visited[i][j] = t;
            int ETA(t + 1 + (i + j) % 2);
            if (i > 0 && visited[i-1][j] < 0) {
                int eta = MAX(ETA, moveTime[i-1][j]);
                // if (eta == moveTime[i-1][j]) {
                //     visited[i-1][j] = eta;
                // }
                pQ.push({eta, i-1, j});
            }
            if (i < n-1 && visited[i+1][j] < 0) {
                int eta = MAX(ETA, moveTime[i+1][j]);
                // if (eta == moveTime[i+1][j]) {
                //     visited[i+1][j] = eta;
                // }
                pQ.push({eta, i+1, j});
                if (i+1 == n-1 && j == m-1) {
                    return eta;
                }
            }
            if (j > 0 && visited[i][j-1] < 0) {
                int eta = MAX(ETA, moveTime[i][j-1]);
                // if (eta == moveTime[i][j-1]) {
                //     visited[i][j-1] = eta;
                // }
                pQ.push({eta, i, j-1});
            }
            if (j < m-1 && visited[i][j+1] < 0) {
                int eta = MAX(ETA, moveTime[i][j+1]);
                // if (eta == moveTime[i][j+1]) {
                //     visited[i][j+1] = eta;
                // }
                pQ.push({eta, i, j+1});
                if (i == n-1 && j+1 == m-1) {
                    return eta;
                }
            }
        }
        return visited[n-1][m-1];
    }
static constexpr auto testEntry = &Solution::minTimeToReach;
};

} // end namespace LC3342

#endif /* LC3342_h */
