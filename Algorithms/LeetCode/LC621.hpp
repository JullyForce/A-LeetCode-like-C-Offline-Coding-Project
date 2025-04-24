//
//  LC621.hpp
//  Algorithms
//
//  Created by Jun Chen on 8/13/24.
//

#ifndef LC621_h
#define LC621_h

#include <vector>
#include <algorithm>

using namespace std;

namespace LC621 {

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> hist(26, 0);
        for(auto c : tasks) {
            hist[c-'A'] ++;
        }
        // Needs some mental acrobatics to figure out it all
        // depends on the following 4 states, once the mind
        // trick is done (there will always be an optimal
        // compaction of tasks without violating the separation)
        // we are up to the easy math.
        sort(hist.begin(), hist.end());
        int maxFreq = hist[25];
        int nMaxFreq = distance(hist.crbegin(), find_if(hist.crbegin(), hist.crend(), [=](const int x) {return x != maxFreq;}));
        int total = tasks.size();
        int period = n + 1;
        
        int minLen = (maxFreq - 1) * period + nMaxFreq;
        return total < minLen ? minLen : total;
    }
//    int leastInterval(vector<char>& tasks, int n) {
//        vector<pair<int,int>> hist(26, {0, 0});
//        for (int i = 0; i < 26; i ++) {
//            hist[i].second = i;
//        }
//        for(auto c : tasks) {
//            hist[c-'A'].first ++;
//        }
//        int count(tasks.size());
//        int time(0);
//        int popped(0);
//        vector<int> lastTime(26, -n-1);
//        make_heap(hist.begin(), hist.end());
//        while (count > 0) {
//            while(popped < 26) {
//                pop_heap(hist.begin(), hist.end()-popped++);
//                if (hist[26-popped].first == 0) {
//                    break;
//                }
//                int task = hist[26-popped].second;
//                if (time - lastTime[task] > n) {
//                    lastTime[task] = time;
//                    hist[26-popped].first --;
//                    count --;
//                    break;
//                }
//            }
//            time ++;
//            while (popped > 0) {
//                push_heap(hist.begin(), hist.end()-(--popped));
//            }
//        }
//        return time;
//    }
    static constexpr auto testEntry = &Solution::leastInterval;
};

} // end namespace LC621

#endif /* LC621_h */
