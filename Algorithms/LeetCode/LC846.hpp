//
//  LC846.hpp
//  Algorithms
//
//  Created by J.C. on 9/29/24.
//

#ifndef LC846_h
#define LC846_h

#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

namespace LC846 {

class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        int n(hand.size());
        if (n % groupSize) {
            return false;
        }
        if (groupSize == 1) {
            return true;
        }
        sort(hand.begin(), hand.end());
        unordered_multimap<int, int> expect;
        for (int x : hand) {
            if (expect.count(x) == 0) {
                expect.emplace(x+1, groupSize-1);
            } else {
                auto range = expect.equal_range(x);
                auto first = range.first;
                int need(first->second - 1);
                if (need != 0) {
                    expect.emplace(x+1, need);
                }
                expect.erase(first, next(first));
            }
        }
        return expect.empty();
    }
static constexpr auto testEntry = &Solution::isNStraightHand;
};

} // end namespace LC846


#endif /* LC846_h */
