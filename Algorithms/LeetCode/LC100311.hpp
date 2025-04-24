//
//  LC100311.hpp
//  Algorithms
//
//  Created by J.C. on 6/1/24.
//

#ifndef LC100311_h
#define LC100311_h

#include <algorithm>
#include <vector>

using namespace std;

namespace LC100311{

class Solution {
public:
    int countDays(int days, vector<vector<int>>& meetings) {
        sort(meetings.begin(), meetings.end(), [](vector<int> a,
        vector<int> b) {return a[0] < b[0];
        });
        int daysAvail(0);
        int lastEnd(0);
        int i = 0;
        while (i < meetings.size()) {
            int mStart = meetings[i][0];
            int mEnd = meetings[i][1];
            daysAvail += mStart - lastEnd - 1;
            int nextStart = days+1;
            while ( ++ i < meetings.size()) {
                if (mEnd < meetings[i][0]) {
                    break;
                }
                if (mEnd < meetings[i][1]) {
                    mEnd = meetings[i][1];
                }
            }
            lastEnd = mEnd;
        }
        if (lastEnd < days) {
            daysAvail += days - lastEnd;
        }
        return daysAvail;
    }
    static constexpr auto testEntry = &Solution::countDays;
};

} // end namespace LC100311

#endif /* LC100311_h */
