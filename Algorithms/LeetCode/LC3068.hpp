//
//  LC3068.hpp
//  Algorithms
//
//  Created by J.C. on 9/21/24.
//

#ifndef LC3068_h
#define LC3068_h

#include <vector>

using namespace std;

namespace LC3068 {

class Solution {
private:
    pair<long long, long long> visit(const vector<vector<int>>& adj, const vector<int>& nums, int n, int k, int node, int from) {
        pair<long long, long long> ret(nums[node], nums[node] ^ k);
        for (int neigh : adj[node]) {
            if (neigh == from) {
                continue;
            }
            auto sub = visit(adj, nums, n, k, neigh, node);
            ret = {MAX(sub.first + ret.first, sub.second + ret.second),
                    MAX(sub.first + ret.second, sub.second + ret.first)};
        }
        return ret;
    }
public:
    long long maximumValueSum(vector<int>& nums, int k, vector<vector<int>>& edges) {
        int n(nums.size());
        vector<vector<int>> adj(n);
        for (auto & e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        [[maybe_unused]] auto [ret, unused] = visit(adj, nums, n, k, 0, -1);
        return ret;
    }
static constexpr auto testEntry = &Solution::maximumValueSum;
};

} // end namespace LC3068


#endif /* LC3068_h */
