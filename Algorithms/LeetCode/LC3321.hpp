//
//  LC3321.hpp
//  Algorithms
//
//  Created by J.C. on 10/13/24.
//

#ifndef LC3321_h
#define LC3321_h

#include <unordered_map>
#include <vector>

using namespace std;

namespace LC3321 {

class Solution {
private:
    using setType = set<pair<int,int>, greater<>>;
    using setIterType = setType::iterator;
    long long insertToSet(unordered_map<int,int>& hist, setType& freqValSet, setIterType& itE, long long sum, int nTop, int x) {
            pair<int,int> newSetRec{hist[x], x};
            if (freqValSet.size() >= nTop && newSetRec > *prev(itE)) {
                -- itE;
                sum -= (long long)itE->first * (long long)itE->second;
                sum += (long long)hist[x] * (long long)x;
                freqValSet.insert(newSetRec);
            } else if (freqValSet.size() == nTop || freqValSet.size() > nTop && newSetRec > *itE) {
                freqValSet.insert(newSetRec);
                -- itE;
            } else if (freqValSet.size() < nTop) {
                sum += (long long)hist[x] * (long long)x;
                freqValSet.insert(newSetRec);
            } else {
                freqValSet.insert(newSetRec);
            }
            return sum;
        }
    long long eraseFromSet(unordered_map<int,int>& hist, setType& freqValSet, setIterType& itE, long long sum, int nTop, int x) {
            auto it = freqValSet.find({hist[x], x});
            if (it == freqValSet.end()) {
            } else if (it == itE) {
                itE = freqValSet.erase(itE);
            } else {
                if (freqValSet.size() > nTop && *it > *itE) {
                    sum -= (long long)it->first * (long long)it->second;
                    sum += (long long)itE->first * (long long)itE->second;
                    ++ itE;
                } else if (freqValSet.size() <= nTop) {
                    sum -= (long long)it->first * (long long)it->second;
                }
                freqValSet.erase(it);
            }
            
            return sum;
        }
public:
    vector<long long> findXSum(vector<int>& nums, int k, int nTop) {
        unordered_map<int, int> hist;
        setType freqValSet;
        int n(nums.size());
        auto itE = freqValSet.end();
        long long sum(0);
        for (int i = 0; i < k; i ++) {
            int x(nums[i]);
            sum = eraseFromSet(hist, freqValSet, itE, sum, nTop, x);
            hist[x] ++;
            sum = insertToSet(hist, freqValSet, itE, sum, nTop, x);
        }
        vector<long long> ans{sum};
        for (int i = k; i < n; i ++) {
            int x0(nums[i-k]);
            int x1(nums[i]);

            sum = eraseFromSet(hist, freqValSet, itE, sum, nTop, x0);
            hist[x0] --;
            if (hist[x0] == 0) {
                hist.erase(x0);
            } else {
                sum = insertToSet(hist, freqValSet, itE, sum, nTop, x0);
            }
            sum = eraseFromSet(hist, freqValSet, itE, sum, nTop, x1);
            hist[x1] ++;
            sum = insertToSet(hist, freqValSet, itE, sum, nTop, x1);
            ans.push_back(sum);
        }
        return ans;
    }
static constexpr auto testEntry = &Solution::findXSum;
};

} // end namespace LC3321

#endif /* LC3321_h */
