//
//  LC3305.hpp
//  Algorithms
//
//  Created by Jun Chen on 9/28/24.
//

#ifndef LC3305_h
#define LC3305_h

#include <string>
#include <vector>

using namespace std;

namespace LC3305 {

class Solution {
private:
    bool vowelsGood(const vector<int>& hist) {
        return hist['a' - 'a'] > 0 && hist['e' - 'a'] > 0 && hist['i' - 'a'] > 0 && hist['o' - 'a'] > 0 && hist['u' - 'a'] > 0;
    }
    int consonCount(const vector<int>& hist, int n) {
        int nVowels = hist['a' - 'a'] + hist['e' - 'a'] + hist['i' - 'a'] + hist['o' - 'a'] + hist['u' - 'a'];
        return n - nVowels;
    }
    bool canMove(const vector<int>& hist, char c) {
        return !((c == 'a' || c == 'e' || c == 'i' || c == 'o' || c== 'u') && hist[c-'a'] <= 1);
    }
    bool canMoveVowel(const vector<int>& hist, char c) {
        return ((c == 'a' || c == 'e' || c == 'i' || c == 'o' || c== 'u') && hist[c-'a'] > 1);
    }
public:
    int countOfSubstrings(string word, int k) {
        int n(word.length());
        int l(0), r(0);
        int count(0);
        vector<int> hist(26, 0);
        for (int i = 0; i < n; i ++) {
            hist[word[i] - 'a'] ++;
            while (vowelsGood(hist) && consonCount(hist, i+1 - r) > k && canMove(hist, word[r])) {
                hist[word[r++] - 'a'] --;
                l = r;
            }
            while (vowelsGood(hist) && consonCount(hist, i+1 - r) == k && canMoveVowel(hist, word[r])) {
                hist[word[r++] - 'a'] --;
            }
            if (vowelsGood(hist) && consonCount(hist, i+1 - r) == k) {
                count += r+1-l;
            }
        }
        return count;
    }
static constexpr auto testEntry = &Solution::countOfSubstrings;
};

} // end namespace LC3305


#endif /* LC3305_h */
