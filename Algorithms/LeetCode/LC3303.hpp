//
//  LC3303.hpp
//  Algorithms
//
//  Created by Jun Chen on 10/8/24.
//

#ifndef LC3303_h
#define LC3303_h

#include <string>
#include <vector>

using namespace std;

namespace LC3303 {

class Solution {
private:
    vector<int> prefix_match(const string & s) {
        int n(s.length());
        vector<int> pi(n);
        for (int i = 1; i < n; i ++) {
            int j = pi[i-1];
            while (j > 0 && s[i] != s[j]) {
                j = pi[j-1];
            }
            if (s[i] == s[j]) {
                j ++;
            }
            pi[i] = j;
        }
        return pi;
    }
    vector<int> suffix_match(const string & s) {
        int n(s.length());
        vector<int> pi(n);
        for (int i = n-2; i >= 0; i --) {
            int j = pi[i+1];
            while (j > 0 && s[i] != s[n-1-j]) {
                j = pi[n-j];
            }
            if (s[i] == s[n-1-j]) {
                j ++;
            }
            pi[i] = j;
        }
        return pi;
    }
public:
    int minStartingIndex(string s, string pattern) {
        int nS(s.size()), nP(pattern.size());
        if (nP == 1) {
            return 0;
        }

        auto prefP = prefix_match(pattern);
        auto suffP = suffix_match(pattern);
        
        vector<int> pref(nS);
        if (pattern[0] == s[0]) {
            pref[0] = 1;
        }
        for (int i = 1; i < nS; i ++) {
            int j = pref[i-1];
            while (j >= nP || j > 0 && s[i] != pattern[j]) {
                j = prefP[j-1];
            }
            if (s[i] == pattern[j]) {
                j ++;
            }
            pref[i] = j;
        }

        vector<int> suff(nS);
        if (pattern[nP-1] == s[nS-1]) {
            suff[nS-1] = 1;
        }
        for (int i = nS-2; i >= 0; i --) {
            int j = suff[i+1];
            while (j >= nP || j > 0 && s[i] != pattern[nP-1-j]) {
                j = suffP[nP-j];
            }
            if (s[i] == pattern[nP-1-j]) {
                j ++;
            }
            suff[i] = j;
        }

        if (suff[0] == nP || suff[1] + 1 == nP || suff[1] > 0 && suffP[nP-suff[1]] + 1 == nP) {
            return 0;
        }
        for (int i = 1; i < nS-1; i++) {
            if (pref[i] == nP || pref[i-1] + 1 == nP || suff[i+1] + pref[i-1] + 1 == nP ||
                suff[i+1] > 0 && suffP[nP-suff[i+1]] + pref[i-1] + 1 == nP) {
                return i - pref[i-1];
            }
            if (suff[i] == nP || suff[i+1] + 1 == nP || suff[i+1] > 0 && suffP[nP-suff[i+1]] + 1 == nP) {
                return i;
            }
        }
        if (pref[nS-1] == nP || pref[nS-2] + 1 == nP) {
            return nS - nP;
        }
        return -1;
        
    }
static constexpr auto testEntry = &Solution::minStartingIndex;
};

} // end namespace LC3303


#endif /* LC3303_h */
