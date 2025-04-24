//
//  LC1717.hpp
//  Algorithms
//
//  Created by Jun Chen on 10/26/24.
//

#ifndef LC1717_h
#define LC1717_h

#include <string>
#include <stack>
#include <vector>

using namespace std;

namespace LC1717 {

class Solution {
private:
    int scoreSubStr(string& s, const char cL, const char cR, int x, int y) {
        int score(0);
        stack<int> stk;
        auto clearStack = [] (stack<int> & stk, const char cL, const char cR, int y) {
            if (stk.empty()) {
                return 0;
            }
            int score(0);
            char prevChar = stk.top();
            stk.pop();
            while (!stk.empty()) {
                if (prevChar == cL && stk.top() == cR) {
                    score += y;
                    stk.pop();
                }
                if (!stk.empty()) {
                    prevChar = stk.top();
                    stk.pop();
                }
            }
            return score;
        };
        for (char c : s) {
            if (c == cR) {
                if (!stk.empty() && stk.top() == cL) {
                    stk.pop();
                    score += x;
                } else {
                    stk.push(c);
                }
                continue;
            }
            if (c == cL) {
                stk.push(c);
                continue;
            }
            score += clearStack(stk, cL, cR, y);
        }
        score += clearStack(stk, cL, cR, y);
        return score;
    }
public:
    int maximumGain(string s, int x, int y) {
        int score(0);
        if (x >= y) {
            score += scoreSubStr(s, 'a', 'b', x, y);
        } else {
            score += scoreSubStr(s, 'b', 'a', y, x);
        }
        return score;
    }
static constexpr auto testEntry = &Solution::maximumGain;
};

} // end namespace LC1717

#endif /* LC1717_h */
