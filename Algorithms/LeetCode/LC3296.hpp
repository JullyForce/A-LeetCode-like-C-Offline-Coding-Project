//
//  LC3296.hpp
//  Algorithms
//
//  Created by J.C. on 9/21/24.
//

#ifndef LC3296_h
#define LC3296_h

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

namespace LC3296 {

class Solution {
public:
    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
        using pair_time_mul = pair<int,int>;
        int n(workerTimes.size());
        vector<pair_time_mul> costHeap(n);
        for (int i = 0; i < n; i ++) {
            costHeap[i] = {workerTimes[i], 1};
        }
        auto highTotalCost = [] (const pair_time_mul & a, const pair_time_mul & b) {
            int tA(0), tB(0);
            for (int i = 1; i <= a.second; i ++) {
                tA += i;
            }
            tA *= a.first;
            for (int i = 1; i <= b.second; i ++) {
                tB += i;
            }
            tB *= b.first;
            return tA > tB;
        };
        make_heap(costHeap.begin(), costHeap.end(), highTotalCost);
        for (int i = 0; i < mountainHeight; i ++) {
            pop_heap(costHeap.begin(), costHeap.end(), highTotalCost);
            auto & x = costHeap.back();
            x.second ++;
            push_heap(costHeap.begin(), costHeap.end(), highTotalCost);
        }
        int ans(0);
        for (auto x : costHeap) {
            int t(0);
            for (int i = 1; i < x.second; i ++) {
                t += i;
            }
            t *= x.first;
            if (t > ans) {
                ans = t;
            }
        }
        return ans;
    }
static constexpr auto testEntry = &Solution::minNumberOfSeconds;
};

} // end namespace LC3296



#endif /* LC3296_h */
