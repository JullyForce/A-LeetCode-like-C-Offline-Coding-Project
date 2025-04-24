//
//  LC3275.hpp
//  Algorithms
//
//  Created by Jun Chen on 8/31/24.
//

#ifndef LC3275_h
#define LC3275_h

#include <vector>
#include <algorithm>

using namespace std;

namespace LC3275 {

class Solution {
public:
#define ABS(x) ((x) > 0 ? (x) : (-x))
    vector<int> resultsArray(vector<vector<int>>& queries, int k) {
        vector<int> ans;
        multiset<int,greater<int>> dist;
        for (int i = 0; i < queries.size(); i ++) {
            auto & q = queries[i];
            int d = ABS(q[0]) + ABS(q[1]);
            dist.emplace(d);
            if (dist.size() > k) {
                dist.erase(dist.begin());
            }
            if (i >= k-1) {
                ans.push_back(*dist.begin());
            } else {
                ans.push_back(-1);
            }
        }
        return ans;
    }
static constexpr auto testEntry = &Solution::resultsArray;
};

} // end namespace LC3275

#endif /* LC3275_h */
