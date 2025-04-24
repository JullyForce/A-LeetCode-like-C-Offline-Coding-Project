//
//  LC768.hpp
//  Algorithms
//
//  Created by Jun Chen on 9/11/24.
//

#ifndef LC768_h
#define LC768_h

#include <string>
#include <algorithm>

using namespace std;

namespace LC768 {

class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
        int n(arr.size());
        int count(0);
        auto fracCmp = [&arr] (int EnumA, int DenomA, int EnumB, int DenomB) {
            return arr[EnumA] * arr[DenomB] < arr[EnumB] * arr[DenomA];
        };
        pair<int,int> ans;
        vector<int> enumIdx(n, 0);
        while (count < k) {
            int minDenomIdx(n-1);
            int denomIdx(n-2);
            while (denomIdx > 0) {
                if (fracCmp(enumIdx[denomIdx], denomIdx, enumIdx[minDenomIdx], minDenomIdx)) {
                    minDenomIdx = denomIdx;
                }
                if (enumIdx[denomIdx] == 0) {
                    break;
                }
                denomIdx --;
            }
            ans = make_pair(enumIdx[minDenomIdx] ++, minDenomIdx);
            count ++;
        }
        return vector<int>{arr[ans.first], arr[ans.second]};
    }
static constexpr auto testEntry = &Solution::kthSmallestPrimeFraction;
};

} // end namespace LC768


#endif /* LC768_h */
