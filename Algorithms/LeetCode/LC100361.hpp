//
//  LC100361.hpp
//  Algorithms
//
//  Created by J.C. on 7/14/24.
//

#ifndef LC100361_h
#define LC100361_h

#include <algorithm>
#include <vector>

using namespace std;

namespace LC100361{


class Solution {
private:
    int cutHelper(int m, int n, vector<int>& hCut, vector<int>& vCut, int u, int d, int l, int r) {
        if (m == 1) {
            return accumulate(vCut.begin()+l, vCut.begin()+r-1, 0);
        }
        if (n == 1) {
            return accumulate(hCut.begin()+u, hCut.begin()+d-1, 0);
        }
        int iH = distance(hCut.begin(), max_element(hCut.begin()+u, hCut.begin()+d-1));
        int iV = distance(vCut.begin(), max_element(vCut.begin()+l, vCut.begin()+r-1));
        int sumH(0), sumV(0);
        for (int i = u; i < d-1; i ++) {
            sumH += hCut[i];
        }
        for (int i = l; i < r-1; i ++) {
            sumV += vCut[i];
        }
        if (vCut[iV] - sumH > hCut[iH] - sumV) {
            return vCut[iV] + cutHelper(m, iV+1-l, hCut, vCut, u, d, l, iV+1) + cutHelper(m, r-iV-1, hCut, vCut, u, d, iV+1, r);
        } else {
            return hCut[iH] + cutHelper(iH+1-u, n, hCut, vCut, u, iH+1, l, r) + cutHelper(d-iH-1, n, hCut, vCut, iH+1, d, l, r);
        }
    }
public:
    int minimumCost(int m, int n, vector<int>& horizontalCut, vector<int>& verticalCut) {
        return cutHelper(m, n, horizontalCut, verticalCut, 0, m, 0, n);
    }
    static constexpr auto testEntry = &Solution::minimumCost;
};

} // end namespace LC100361

#endif /* LC100361_h */
