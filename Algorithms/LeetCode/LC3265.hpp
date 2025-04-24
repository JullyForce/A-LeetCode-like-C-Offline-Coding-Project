//
//  LC3265.hpp
//  Algorithms
//
//  Created by J.C. on 8/24/24.
//

#ifndef LC3265_h
#define LC3265_h

#include <vector>
#include <algorithm>

using namespace std;

namespace LC3265 {

class Solution {
private:
    int encode(int x) {
        int y(0);
        int ds(0);
        while (x != 0) {
            y |= ((x % 10) << ds);
            x /= 10;
            ds += 4;
        }
        return y;
    }
    int countAsPair(int x, int y) {
        if (x == y) {
            return 1;
        }
        int X[3] = {0};
        int Y[3] = {0};
        int countDiff(0);
        for (int i = 0; i < 32; i += 4) {
            int x1(x & 15);
            int y1(y & 15);
            if (x1 != y1) {
                X[countDiff] = x1;
                Y[countDiff] = y1;
                countDiff ++;
            }
            if (countDiff > 2) {
                return 0;
            }
            x >>= 4;
            y >>= 4;
        }
        return (countDiff == 2 && X[0] == Y[1] && X[1] == Y[0]) ? 1 : 0;
    }
public:
    int countPairs(vector<int>& nums) {
        int n(nums.size());
        for (int & x : nums) {
            x = encode(x);
        }
        int ans(0);
        for (int i = 0; i < n; i ++) {
            for (int j = i + 1; j < n; j ++) {
                ans += countAsPair(nums[i], nums[j]);
            }
        }
        return ans;
    }
    static constexpr auto testEntry = &Solution::countPairs;
};

} // end namespace LC3265

#endif /* LC3265_h */
