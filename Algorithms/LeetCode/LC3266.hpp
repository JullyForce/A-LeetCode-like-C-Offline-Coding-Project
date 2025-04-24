//
//  LC3266.hpp
//  Algorithms
//
//  Created by J.C. on 8/25/24.
//

#ifndef LC3266_h
#define LC3266_h

#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

namespace LC3266 {

class Solution {
private:
    long long pow_mod(int x, int pow) {
        long long ans(1);
        long long x_p(x);
        while (pow > 0) {
            if (pow & 1) {
                ans *= x_p;
                ans %= 1000000007;
            }
            pow >>= 1;
            x_p *= x_p;
            x_p %= 1000000007;
        }
        return ans;
    }
public:
    vector<int> getFinalState(vector<int>& nums, int k, int multiplier) {
        int n(nums.size());
        priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pQ;
        long long maxNum = *max_element(nums.begin(), nums.end());
        for (int i = 0; i < n; i ++) {
            pQ.emplace(nums[i], i);
        }

        while (k > 0) {
            auto data = pQ.top();
            if ((data.first *= multiplier) >= maxNum) {
                break;
            }
            pQ.pop();
            pQ.push(data);
            k --;
        }
        int nMinMuls = k / n;
        int nExtraMuls = k % n;
        long long mulMin(1);
        mulMin = pow_mod(multiplier, nMinMuls);
        long long mulExtra(mulMin * multiplier % 1000000007);
        for (int i = 0; i < n; i ++) {
            auto d = pQ.top();
            pQ.pop();
            int val = d.first;
            int idx = d.second;
            if (i < nExtraMuls) {
                nums[idx] = (int)(val * mulExtra % 1000000007);
            } else {
                nums[idx] = (int)(val * mulMin % 1000000007);
            }
        }
        return nums;
    }
    static constexpr auto testEntry = &Solution::getFinalState;
};

} // end namespace LC3266

#endif /* LC3266_h */
