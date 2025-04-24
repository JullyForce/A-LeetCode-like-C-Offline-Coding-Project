//
//  LC1255.hpp
//  Algorithms
//
//  Created by J.C. on 9/24/24.
//

#ifndef LC1255_h
#define LC1255_h

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

namespace LC1255 {

class Solution {
private:
    int consumeList(const vector<string>& words, int wIdx, const vector<int>& scoreList, vector<int>& nLetters) {
        int score(0);
        const string & w = words[wIdx];
        int n(w.length());
        int i(0);
        while (i < n) {
            int charIdx(w[i] - 'a');
            if (nLetters[charIdx] == 0) {
                break;
            }
            score += scoreList[charIdx];
            -- nLetters[charIdx];
            i ++;
        }
        if (i < n) {
            while (i > 0) {
                -- i;
                int charIdx(w[i] - 'a');
                nLetters[charIdx] ++;
            }
            return -1;
        }
        return score;
    }
    void revertList(const vector<string>& words, int wIdx, vector<int>& nLetters) {
        const string & w = words[wIdx];
        int i(w.length());

        while (i > 0) {
            -- i;
            int charIdx(w[i] - 'a');
            nLetters[charIdx] ++;
        }
    }
    int maxHelper(const vector<string>& words, const vector<int>& scoreList, vector<int>& nLetters, int l, int r) {
        int ans(0);
        if (l == r) {
            return ans;
        }
        for (int i = l; i < r; i ++) {
            int score = consumeList(words, i, scoreList, nLetters);
            if (score >= 0) {
                score += maxHelper(words, scoreList, nLetters, i+1, r);
                ans = MAX(ans, score);
                revertList(words, i, nLetters);
            }
        }
        return ans;
    }
public:
    int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score) {
        vector<int> nLetters(26);
        int n(letters.size());
        for (int i = 0; i < n; i ++) {
            nLetters[letters[i] - 'a'] ++;
        }
        return maxHelper(words, score, nLetters, 0, words.size());
    }
static constexpr auto testEntry = &Solution::maxScoreWords;
};

} // end namespace LC1255

#endif /* LC1255_h */
