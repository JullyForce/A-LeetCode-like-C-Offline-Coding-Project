//
//  LC857.hpp
//  Algorithms
//
//  Created by J.C. on 9/13/24.
//

#ifndef LC857_h
#define LC857_h

#include <algorithm>
#include <tuple>
#include <queue>
#include <vector>

using namespace std;

namespace LC857 {

class Solution {
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
        int n(quality.size());
        vector<pair<int,int>> pairQualWage(n);
        transform(quality.begin(), quality.end(), wage.begin(), pairQualWage.begin(),
            [] (int q, int w) { return make_pair(q, w); });
        auto cmpByRate = [] (const pair<int,int> & a, const pair<int,int> & b) {
            double rateA(double(a.second) / double(a.first));
            double rateB(double(b.second) / double(b.first));
            return rateA < rateB || rateA == rateB && a.first < b.first;
        };
        sort(pairQualWage.begin(), pairQualWage.end(), cmpByRate);
        priority_queue<int> pQ;
        int sumQual(0);
        double rate(0.0);
        for (int i = 0; i < k; i ++) {
            sumQual += pairQualWage[i].first;
            pQ.push(pairQualWage[i].first);
            rate = double(pairQualWage[i].second) / double(pairQualWage[i].first);
        }
        double minCost(double(sumQual) * rate);
        for (int i = k; i < n; i ++) {
            sumQual += pairQualWage[i].first;
            pQ.push(pairQualWage[i].first);
            rate = double(pairQualWage[i].second) / double(pairQualWage[i].first);
            sumQual -= pQ.top();
            pQ.pop();
            minCost = min(minCost, double(sumQual) * rate);
        }

        return minCost;
    }
static constexpr auto testEntry = &Solution::mincostToHireWorkers;
};

} // end namespace LC857


#endif /* LC857_h */
