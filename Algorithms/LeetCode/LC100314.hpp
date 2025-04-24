//
//  LC100314.hpp
//  Algorithms
//
//  Created by Jun Chen on 5/25/24.
//

#ifndef LC100314_h
#define LC100314_h

#include <algorithm>
#include <vector>

using namespace std;

namespace LC100314{

class Solution {
public:
    vector<bool> getResults(vector<vector<int>>& queries) {
        vector<int> rangeB{0, INT_MAX};
        vector<bool> ret;
        for (auto & q : queries) {
            int & qType = q[0];
            int & x = q[1];
            if (qType == 1) {
                auto it = upper_bound(rangeB.begin(), rangeB.end(), x);
                rangeB.insert(it, x);
            } else {
                int & sz = q[2];
                bool fit(false);
                auto it = upper_bound(rangeB.begin(), rangeB.end(), x);
                int lastL = distance(rangeB.begin(), it);
                for (int i = 1; i < lastL; i ++) {
                    if (rangeB[i] - rangeB[i-1] >= sz) {
                        fit = true;
                        break;
                    }
                }
                if (x - rangeB[lastL-1] >= sz) {
                    fit = true;
                }
                ret.push_back(fit);
            }
        }
        return ret;
    }
    static constexpr auto testEntry = &Solution::getResults;
};

} // end namespace LC100314

#endif /* LC100314_h */
