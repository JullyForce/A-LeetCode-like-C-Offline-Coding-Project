//
//  LC834.hpp
//  Algorithms
//
//  Created by J.C. on 9/7/24.
//

#ifndef LC834_h
#define LC834_h

#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

namespace LC834 {

class Solution_NonTrivial {
private:
    tuple<int,int,int> DFSVisit(const vector<vector<int>> & adj, vector<vector<tuple<int,int,int>>> & branchSize, int n, int node, int from) {
        tuple<int,int,int> ans(node, 0, 0);
        for (auto neigh : adj[node]) {
            if (neigh == from) {
                continue;
            }
            auto ret = DFSVisit(adj, branchSize, n, neigh, node);
            get<1>(ans) += get<1>(ret);
            get<2>(ans) += get<2>(ret);
            branchSize[node].push_back(move(ret));
        }
        get<2>(ans) ++;
        get<1>(ans) += get<2>(ans);
        return ans;
    }
    void DFSPropRoot(vector<vector<tuple<int,int,int>>> & branchSize, vector<int> & dist, int n, int node, tuple<int,int,int> from) {
        if (get<0>(from) != -1) {
            branchSize[node].push_back(from);
        }
        tuple<int,int,int> distToNeigh(node, 0, 0);
        for (auto & b : branchSize[node]) {
            get<1>(distToNeigh) += get<1>(b);
            get<2>(distToNeigh) += get<2>(b);
        }
        dist[node] = get<1>(distToNeigh);
        for (auto & b : branchSize[node]) {
            int neigh = get<0>(b);
            if (neigh == get<0>(from)) {
                continue;
            }
            auto rootBoundDist(distToNeigh);
            get<1>(rootBoundDist) -= get<1>(b);
            get<2>(rootBoundDist) -= get<2>(b);
            get<2>(rootBoundDist) ++;
            get<1>(rootBoundDist) += get<2>(rootBoundDist);
            DFSPropRoot(branchSize, dist, n, neigh, rootBoundDist);
        }
    }
public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n, vector<int>());
        for (auto & e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        vector<vector<tuple<int,int,int>>> branchSize(n, vector<tuple<int,int,int>>());
        DFSVisit(adj, branchSize, n, 0, -1);
        vector<int> dist(n, 0);
        DFSPropRoot(branchSize, dist, n, 0, {-1, 0, 0});
        return dist;
    }
};

class Solution {
private:
    int DFSCount(const vector<vector<int>> & adj, vector<int> & branchSize, int n, int node, int from) {
        int rootBoundDist(0);
        branchSize[node] = 1;
        for (auto neigh : adj[node]) {
            if (neigh == from) {
                continue;
            }
            int subSize = DFSCount(adj, branchSize, n, neigh, node);
            branchSize[node] += branchSize[neigh];
            rootBoundDist += subSize;
        }
        rootBoundDist += branchSize[node];
        return rootBoundDist;
    }
    void dpPropDist(const vector<vector<int>> & adj, vector<int> & branchSize, vector<int> & dist, int n, int node, int from) {
        for (int neigh : adj[node]) {
            if (neigh == from) {
                continue;
            }
            dist[neigh] = dist[node] + (n-branchSize[neigh]) - branchSize[neigh];
            dpPropDist(adj, branchSize, dist, n, neigh, node);
        }
    }
public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n, vector<int>());
        for (auto & e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        vector<int> branchSize(n, 0);
        vector<int> dist(n, 0);
        dist[0] = DFSCount(adj, branchSize, n, 0, -1) - branchSize[0];

        dpPropDist(adj, branchSize, dist, n, 0, -1);

        return dist;
    }
static constexpr auto testEntry = &Solution::sumOfDistancesInTree;
};

} // end namespace LC834

#endif /* LC834_h */
