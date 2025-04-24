//
//  LC100283.hpp
//  Algorithms
//
//  Created by J.C. on 5/5/24.
//

#ifndef LC100283_h
#define LC100283_h

#include <vector>
#include <set>

using namespace std;

namespace LC100283{

class Solution {
public:
    int minAnagramLength(string s) {
        set<int> len;
        int n = s.length();
        for (int i = 1; i * i <= n; i ++) {
            if (n % i == 0) {
                len.emplace(i);
                len.emplace(n/i);
            }
        }
        vector<int> periods(len.begin(), len.end());
        vector<vector<short>> freqByPeriod(periods.size(), vector<short>(26, 0));
        vector<short> count(26, 0);
        for (int i = 0; i < s.length(); i ++) {
            const char & c = s[i];
            const int idx = c - 'a';
            count[idx] ++;
            for (int j = 0; j < periods.size(); j ++) {
                int & aPeriod = periods[j];
                if (aPeriod < 0) {
                    continue;
                }
                if (aPeriod > (i + 1)) {
                    break;
                }
                if ((i + 1) % aPeriod == 0) {
                    bool checkPassed(true);
                    if ((i + 1) / aPeriod == 1) {
                        freqByPeriod[j] = count;
                    } else {
                        for (int k = 0; k < 26; k ++) {
                            const int nPeriods = (i + 1) / aPeriod;
                            if (count[k] % nPeriods != 0 || count[k] / nPeriods != freqByPeriod[j][k]) {
                                checkPassed = false;
                                break;
                            }
                        }
                    }
                    if (!checkPassed) {
                        periods[j] = -1; // Remove this period from candidacy
                    }
                }
            }
        }
        auto it = find_if(periods.begin(), periods.end(), [](int & x) { return x > 0;});
        return *it;
    }
    static constexpr auto testEntry = &Solution::minAnagramLength;
};

} // end namespace LC100283

#endif /* LC100283_h */
