//
//  LC752.hpp
//  Algorithms
//
//  Created by J.C. on 8/30/24.
//

#ifndef LC752_h
#define LC752_h

#include <vector>
#include <algorithm>

using namespace std;

namespace LC752 {

class Solution {
private:
    int str2bcd(string & s) {
        int ans(0);
        int d(0);
        for (auto it = s.crbegin(); it != s.crend(); ++ it, d+= 4) {
            ans |= ((*it - '0') << d);
        }
        return ans;
    }
    void findAdj(vector<int>& adj, int x) {
        adj.clear();

        for (int i = 0; i < 4; i ++) {
            int neigh(x);
            int bitOffset(i << 2);
            int d = neigh & (15 << bitOffset);
            adj.push_back((neigh ^ d) | ((((d >> bitOffset) + 1) % 10) << bitOffset));
            adj.push_back((neigh ^ d) | ((((d >> bitOffset) + 9) % 10) << bitOffset));
        }

    }
    int BFSHelper(vector<bool>& avoid, int src, int dst) {
        int count(0);
        if (avoid[src]) {
            return -1;
        }
        if (src == dst) {
            return count;
        }
        queue<int> Q;
        avoid[src] = true;
        count ++;
        Q.push(src);
        Q.push(-1);
        vector<int> adj;
        while (!Q.empty()) {
            int i = Q.front();
            Q.pop();
            if (i == -1) {
                if (Q.empty()) {
                    break;
                }
                count ++;
                Q.push(-1);
                continue;
            }
            findAdj(adj, i);
            for (int neigh : adj) {
                if (neigh == dst) {
                    return count;
                }
                if (!avoid[neigh]) {
                    avoid[neigh] = true;
                    Q.push(neigh);
                }
            }
        }
        return -1;
    }
public:
    int openLock(vector<string>& deadends, string target) {
        vector<bool> avoid(65536, false);
        for (auto & s : deadends) {
            avoid[str2bcd(s)] = true;
        }
        return BFSHelper(avoid, 0, str2bcd(target));
    }
static constexpr auto testEntry = &Solution::openLock;
};

} // end namespace LC752


#endif /* LC752_h */
