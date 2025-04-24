//
//  StableDutchFlag.hpp
//  Algorithms
//
//  Created by J.C. on 4/19/25.
//  Coding question:
//    Give you an array which has n integers, t has both positive and negative integers. Now you need
//    sort this array in a special way. After that, the negative integers should in the front, and the positive
//    integers should in the back. Also the relative position should not be changed.
//    eg. -1 1 3 -2 2 ans: -1 -2 1 3 2.
//    o(n)time complexity and o(1) space complexity is required.
//

#ifndef StableDutchFlag_h
#define StableDutchFlag_h

#include <vector>
#include <algorithm>

#include "../Exercise/CyclicShift/CyclicShift.hpp"

using namespace std;

namespace GP_StableDutchFlag {

class Solution {
    int stablePartition2(vector<int>& arr, int l, int r, const function<bool (const int&)> predLeft) {
        // Partition a region ["l", "r") of "arr", with all satisfying predLeft moved left, return index
        // to first element partitioned right (not satisfying predLeft)
        if (r - l <= 1) {
            return predLeft(arr[l]) ? r : l;
        }
        int m((l + r + 1) / 2);
        int sL = stablePartition2(arr, l, m, predLeft);
        int sR = stablePartition2(arr, m, r, predLeft);
        CyclicShift::shiftInplace(arr, sL, sR, sR - m);
        return sL + sR - m;
    }
public:
    vector<int> stablePartition3(vector<int>& nums) {
        int n(nums.size());
        stablePartition2(nums, 0, n, [](const int& a) { return a < 0; });
        stablePartition2(nums, 0, n, [](const int& a) { return a <= 0; });
        return nums;
    }
    static constexpr auto testEntry = &Solution::stablePartition3;
};

} // end namespace GP_StableDutchFlag


#endif /* StableDutchFlag_h */
