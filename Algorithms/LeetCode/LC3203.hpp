//
//  LC3203.hpp
//  Algorithms
//
//  Created by Jun Chen on 6/30/24.
//

#ifndef LC3203_h
#define LC3203_h

#include <vector>
#include <map>

using namespace std;

namespace LC3203 {

class Solution {
public:
    int minimumDiameterAfterMerge(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        auto diameter = [&](vector<vector<int>>& edges) -> int {
            vector<vector<int>> adj(edges.size()+1);
            for (auto & e :edges) {
                adj[e[0]].push_back(e[1]);
                adj[e[1]].push_back(e[0]);
            }

            int n(adj.size() + 1);
            vector<int> depth(n, 0);
            function<void(int,int)> dfs = [&](int x, int p) -> void {
                for(int y : adj[x]) {
                    if (y == p) continue;
                    depth[y] = depth[x] + 1;
                    dfs(y, x);
                }
            };

            dfs(0, -1);
            int e = distance(depth.begin(), max_element(depth.begin(), depth.end()));
            fill(depth.begin(), depth.end(), 0);
            dfs(e, -1);

            return *max_element(depth.begin(), depth.end());
        };
        int d1 = diameter(edges1);
        int d2 = diameter(edges2);
        int d3 = (d1+1)/2 + (d2+1)/2 + 1;

        return max({d1, d2, d3});
    }
    static constexpr auto testEntry = &Solution::minimumDiameterAfterMerge;
};

} // end namespace LC3203

#endif /* LC3203_h */
