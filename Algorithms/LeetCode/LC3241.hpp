//
//  LC3241.hpp
//  Algorithms
//
//  Created by J.C. on 8/6/24.
//

#ifndef LC3241_h
#define LC3241_h

#include <vector>
#include <utility>
#include <array>

using namespace std;

namespace LC3241 {

class Solution {
private:
    void updateUpwardDelay(const vector<vector<int>> & adj, vector<array<pair<int,int>,2>> & dp, int n, int i, pair<int,int> upDelay) {
        pair<int,int> & dpToOverwrite = dp[i][0].second == upDelay.second ? dp[i][0] :
            dp[i][1].second == upDelay.second ? dp[i][1] :
            dp[i][0].first < dp[i][1].first ? dp[i][0] : dp[i][1];
        pair<int,int> & dpTheOther = dp[i][0].second == upDelay.second ? dp[i][1] :
            dp[i][1].second == upDelay.second ? dp[i][0] :
            dp[i][0].first < dp[i][1].first ? dp[i][1] : dp[i][0];
        if (dpToOverwrite.first >= upDelay.first) {
            return;
        }
        dpToOverwrite = upDelay;
        auto selfboundNewDelay = make_pair(upDelay.first + ((i % 2 == 0) ? 2 : 1), i);
        if (upDelay.first > dpTheOther.first) {
            for (auto & neigh : adj[i]) {
                if (neigh == upDelay.second) {
                    continue;
                }
                updateUpwardDelay(adj, dp, n, neigh, selfboundNewDelay);
            }
        } else {
            updateUpwardDelay(adj, dp, n, dpTheOther.second, selfboundNewDelay);
        }
    }
    int findDelay(const vector<vector<int>> & adj, vector<array<pair<int,int>,2>> & dp, int n, int i, pair<int,int> upDelay) {
        auto selfboundDelay = make_pair(upDelay.first + ((i % 2) == 0 ? 2 : 1), i);
        for(auto & neigh : adj[i]) {
            if (neigh == upDelay.second) {
                continue;
            }
            auto branchDelay = findDelay(adj, dp, n, neigh, selfboundDelay);
            if (dp[i][0].first < dp[i][1].first) {
                if (dp[i][0].first < branchDelay) {
                    dp[i][0] = make_pair(branchDelay, neigh);
                }
            } else {
                if (dp[i][1].first < branchDelay) {
                    dp[i][1] = make_pair(branchDelay, neigh);
                }
            }
        }
        auto maxSubDelay = MAX(dp[i][0].first, dp[i][1].first);
        if (upDelay.first >= maxSubDelay) {
            pair<int,int> & dpToOverwrite = /*dp[i][0].second == upDelay.second ? dp[i][0] :
                dp[i][1].second == upDelay.second ? dp[i][1] :*/
                dp[i][0].first < dp[i][1].first ? dp[i][0] : dp[i][1];
            dpToOverwrite = upDelay;
        } else {
            pair<int,int> & dpToProp = dp[i][0].first > dp[i][1].first ? dp[i][0] : dp[i][1];
            pair<int,int> & dpTheOther = dp[i][0].first > dp[i][1].first ? dp[i][1] : dp[i][0];

            selfboundDelay = make_pair(dpToProp.first + ((i % 2) == 0 ? 2 : 1), i);
            for (auto & neigh : adj[i]) {
                if (neigh == upDelay.second || neigh == dpToProp.second) {
                    continue;
                }
                updateUpwardDelay(adj, dp, n, neigh, selfboundDelay);
            }
            if (dpTheOther.first <= upDelay.first) {
                dpTheOther = upDelay;
            } else {
                selfboundDelay = make_pair(dpTheOther.first + ((i % 2) == 0 ? 2 : 1), i);
                updateUpwardDelay(adj, dp, n, dpToProp.second, selfboundDelay);
            }
        }
        return maxSubDelay + ((i % 2) == 0 ? 2 : 1);
    }
public:
    vector<int> timeTaken(vector<vector<int>>& edges) {
        int n(edges.size()+1);
        vector<vector<int>> adj(n, vector<int>{});
        for (auto & e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<array<pair<int,int>,2>> dp(n, {{{0,-1},{0,-1}}});
        findDelay(adj, dp, n, 0, {0,-1});
        vector<int> ans;
        for (auto & x : dp) {
            ans.push_back(MAX(x[0].first, x[1].first));
        }
        return ans;
    }
    static constexpr auto testEntry = &Solution::timeTaken;
};

} // end namespace LC3241

#endif /* LC3241_h */
