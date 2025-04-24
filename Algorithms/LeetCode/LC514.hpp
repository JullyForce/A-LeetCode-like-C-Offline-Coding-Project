//
//  LC514.hpp
//  Algorithms
//
//  Created by Jun Chen on 9/5/24.
//

#ifndef LC514_h
#define LC514_h

#include <vector>
#include <algorithm>

using namespace std;

namespace LC514 {

class Solution {
private:
    int rotateHelper(const string & circBuff, int n, int idx, const string & key, int m, int i) {
        if (i == m) {
            return 0;
        }
        if (circBuff[idx] == key[i]) {
            return rotateHelper(circBuff, n, idx, key, m, i+1) + 1;
        } else {
            idx += n;
            int l = circBuff.find_last_of(key[i], idx);
            int r = circBuff.find_first_of(key[i], idx);
            if (r - l == n) {
                int move = r-idx < idx-l ? r-idx : idx-l;
                int newIdx = (r-idx < idx-l ? r : l) % n;
                return rotateHelper(circBuff, n, newIdx, key, m, i+1) + move + 1;
            } else {
                int countL = rotateHelper(circBuff, n, l%n, key, m, i+1) + idx-l + 1;
                int countR = rotateHelper(circBuff, n, r%n, key, m, i+1) + r-idx + 1;
                return countL < countR ? countL : countR;
            }
        }
    }
public:
    int findRotateSteps(string ring, string key) {
        int n(ring.length());
        // string circBuff = ring + ring + ring;
        // return rotateHelper(circBuff, n, 0, key, key.length(), 0);
        vector<int> dp(n, 0);
        vector<int> dpTmp(n, -1);
        for (auto it = key.crbegin(); it != key.crend(); ++ it) {
            char c = *it;
            for (int i = 0; i < n; i ++) {
                if (ring[i] != c) {
                    dpTmp[i] = -1;
                    continue;
                }
                int minSteps(INT_MAX);
                for (int s = 0; s < n / 2 + 1; s ++) {
                    int dpR = dp[(i+s)%n];
                    if (dpR != -1) {
                        minSteps = min(minSteps, dpR + s);
                    }
                    int dpL = dp[(i+n-s)%n];
                    if (dpL != -1) {
                        minSteps = min(minSteps, dpL + s);
                    }
                }
                dpTmp[i] = minSteps + 1;
            }
            swap(dp, dpTmp);
        }
        int minSteps(INT_MAX);
        for (int s = 0; s < n / 2 + 1; s ++) {
            int dpR = dp[s];
            if (dpR != -1) {
                minSteps = min(minSteps, dpR + s);
            }
            int dpL = dp[(n-s)%n];
            if (dpL != -1) {
                minSteps = min(minSteps, dpL + s);
            }
        }
        return minSteps;
    }
static constexpr auto testEntry = &Solution::findRotateSteps;
};

} // end namespace LC514

#endif /* LC514_h */
