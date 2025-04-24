//
//  LC3318.hpp
//  Algorithms
//
//  Created by Jun Chen on 10/13/24.
//

#ifndef LC3318_h
#define LC3318_h

#include <unordered_map>
#include <vector>

using namespace std;

namespace LC3318 {

class Solution {
private:
    long long countHist(const unordered_map<int,int>& hist, const set<pair<int,int>>& fvSet, int x) {
        int count(0);
        long long val(0);
        for (auto it = fvSet.rbegin(); it != fvSet.rend() && count < x; ++ it) {
            val += (long long)it->first * (long long)it->second;
            count ++;
        }
        return val;
    }
public:
    vector<long long> findXSum(vector<int>& nums, int k,  int nTop) {
        unordered_map<int, int> hist;
        set<pair<int,int>> freqValSet;
        int n(nums.size());
        for (int i = 0; i < k; i ++) {
            int x(nums[i]);
            freqValSet.erase({hist[x], x});
            hist[x] ++;
            freqValSet.emplace(hist[x], x);
        }
        vector<long long> ans;
        ans.push_back(countHist(hist, freqValSet, nTop));
        for (int i = k; i < n; i ++) {
            int x0(nums[i-k]);
            int x1(nums[i]);
            freqValSet.erase({hist[x0], x0});
            hist[x0] --;
            if (hist[x0] == 0) {
                hist.erase(x0);
            } else {
                freqValSet.emplace(hist[x0], x0);
            }
            freqValSet.erase({hist[x1], x1});
            hist[x1] ++;
            freqValSet.emplace(hist[x1], x1);
            ans.push_back(countHist(hist, freqValSet, nTop));
        }
        return ans;
    }
static constexpr auto testEntry = &Solution::findXSum;
};

} // end namespace LC3318

#endif /* LC3318_h */
