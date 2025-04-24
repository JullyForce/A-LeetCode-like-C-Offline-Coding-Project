//
//  LC950.hpp
//  Algorithms
//
//  Created by J.C. on 8/22/24.
//

#ifndef LC950_h
#define LC950_h

#include <vector>
#include <algorithm>

using namespace std;

namespace LC950 {

class Solution {
public:
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        int n(deck.size());
        vector<int> idx(n, 0);
        for (int i = 0; i < n; i ++) {
            idx[i] = i;
        }
        vector<int> idx2(n, 0);
        int count(0);
        int l(0), i(0);
        while (count < n) {
            // while (idx[i] < 0) {
            //     i = (i + 1 - l) % (n-l) + l;
            // }
            idx2[count ++] = idx[i];
            idx[i] = -1;
            if (count == n) {
                break;
            }
            // next card and shrink the circular buffer if able
            if (i == l) {
                while (idx[i] < 0) {
                    i = (i + 1 - l) % (n-l) + l;
                }
                l = i;
            } else {
                while (idx[i] < 0) {
                    i = (i + 1 - l) % (n-l) + l;
                }
            }

            // put to bottom deck
            do {
                i = (i + 1 - l) % (n-l) + l;
            } while (idx[i] < 0);
        }
        sort(deck.begin(), deck.end());
        for (int i = 0; i < n; i ++) {
            idx[idx2[i]] = deck[i];
        }
        return idx;
    }

static constexpr auto testEntry = &Solution::deckRevealedIncreasing;
};

} // end namespace LC950

#endif /* LC950_h */
