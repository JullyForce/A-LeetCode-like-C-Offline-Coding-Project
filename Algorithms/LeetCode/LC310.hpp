//
//  LC310.hpp
//  Algorithms
//
//  Created by J.C. on 9/4/24.
//

#ifndef LC310_h
#define LC310_h

#include <vector>
#include <algorithm>

using namespace std;

namespace LC310 {

class Solution {
private:
    void BFSPropIn(const vector<vector<int>>& adj, vector<int>& deg, vector<int>& height, queue<int>& Q) {
        while (!Q.empty()) {
            int node = Q.front();
            Q.pop();
            for (int neigh : adj[node]) {
                if (height[neigh] == 0 && -- deg[neigh] <= 1) {
                    height[neigh] = height[node] + 1;
                    Q.push(neigh);
                }
            }
        }
    }
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n, vector<int>());
        vector<int> deg(n, 0);
        for (auto & e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
            deg[e[0]] ++;
            deg[e[1]] ++;
        }
        vector<int> height(n, 0);
        queue<int> Q;
        for (int i = 0; i < n; i ++) {
            if (deg[i] == 1) {
                height[i] = 1;
                Q.push(i);
            }
        }
        BFSPropIn(adj, deg, height, Q);
        auto it = max_element(height.begin(), height.end());
        auto it2 = max_element(it+1, height.end());
        vector<int> ans{(int)distance(height.begin(), it)};
        if (it2 != height.end() && *it2 == *it) {
            ans.push_back(distance(height.begin(), it2));
        }
        return ans;
    }
static constexpr auto testEntry = &Solution::findMinHeightTrees;
};

} // end namespace LC310

#endif /* LC310_h */
