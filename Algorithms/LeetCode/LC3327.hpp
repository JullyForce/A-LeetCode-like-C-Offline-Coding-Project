//
//  LC3327.hpp
//  Algorithms
//
//  Created by J.C. on 10/19/24.
//

#ifndef LC3327_h
#define LC3327_h

#include <string>
#include <vector>

using namespace std;

namespace LC3327 {

// TLE, Need to implement optimal Palindrome algorithm (Manacher)
class Solution {
private:
    // };
    bool isPalindrome(const string& s, int l, int r) {
        // int l(0), r(s.length()-1);
        while (r > l) {
            if (s[r--] != s[l++]) {
                return false;
            }
        }
        return true;
    }
    void checkHelper(const vector<vector<int>>& child, const vector<int>& parent, vector<bool>& ans, const string& s, int n, int i, string& tmp) {
        int l(tmp.length());
        for (int c : child[i]) {
            checkHelper(child, parent, ans, s, n, c, tmp);
        }
        tmp += s[i];
        ans[i] = isPalindrome(tmp, l, tmp.length()-1);
    }
public:
    vector<bool> findAnswer(vector<int>& parent, string s) {
        int n(parent.size());
        vector<vector<int>> childList(n);
        for (int i = 0; i < n; i ++) {
            if (parent[i] >= 0) {
                childList[parent[i]].push_back(i);
            }
        }
        vector<bool> ans(n);
        string tmp("");
        checkHelper(childList, parent, ans, s, n, 0, tmp);
        return ans;
    }
static constexpr auto testEntry = &Solution::findAnswer;
};

} // end namespace LC3327


#endif /* LC3327_h */
