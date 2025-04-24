//
//  LC3281.hpp
//  Algorithms
//
//  Created by J.C. on 9/7/24.
//

#ifndef LC3281_h
#define LC3281_h

#include <vector>
#include <algorithm>

using namespace std;

namespace LC3281 {

class Solution {
private:
    int devideHelper(const vector<int>& start, int d, int r, int l, int & lim) {
            int L(start[l]), R(start[r-1]+d);
            if (r - l > 1) {
                lim = min(lim, (R - L) / (r-1-l));
            }
            int lastPos(start[l]-lim);

            for (int i = l; i < r; i ++) {
                int expPos(lastPos + lim);
                if (expPos < start[i]) {
                    return devideHelper(start, d, r, i, lim);
                } else if (expPos > start[i] + d) {
                    lastPos = devideHelper(start, d, i+1, l, lim);
                } else {
                    lastPos += lim;
                }
            }
            return lastPos;
        }
public:
    int maxPossibleScore(vector<int>& start, int d) {
        int n(start.size());
        sort(start.begin(), start.end());
        int L(start[0]), R(start[n-1]+d);
        int lim((R - L) / (n-1));
        devideHelper(start, d, n, 0, lim);
        return lim;
    }
static constexpr auto testEntry = &Solution::maxPossibleScore;
};

} // end namespace LC3281

#endif /* LC3281_h */
