//
//  LC165.hpp
//  Algorithms
//
//  Created by Jun Chen on 9/9/24.
//

#ifndef LC165_h
#define LC165_h

#include <string>
#include <algorithm>

using namespace std;

namespace LC165 {

class Solution_old {
public:
    int compareVersion(string version1, string version2) {
        auto itL1 = version1.begin();
        auto itL2 = version2.begin();
        while (itL1 != version1.end() && itL2 != version2.end()) {
            auto itR1 = find(itL1, version1.end(), '.');
            auto itR2 = find(itL2, version2.end(), '.');
            int v1 = stoi(string(itL1, itR1));
            int v2 = stoi(string(itL2, itR2));
            if (v1 > v2) {
                return 1;
            }
            if (v1 < v2) {
                return -1;
            }
            itL1 = itR1 == version1.end() ? itR1 : next(itR1, 1);
            itL2 = itR2 == version2.end() ? itR2 : next(itR2, 1);
        }
        while (itL1 != version1.end()) {
            auto itR1 = find(itL1, version1.end(), '.');
            if (stoi(string(itL1, itR1)) != 0) {
                return 1;
            }
            itL1 = itR1 == version1.end() ? itR1 : next(itR1, 1);
        }
        while (itL2 != version2.end()) {
            auto itR2 = find(itL2, version2.end(), '.');
            if (stoi(string(itL2, itR2)) != 0) {
                return 1;
            }
            itL2 = itR2 == version2.end() ? itR2 : next(itR2, 1);
        }
        return 0;
    }
};

class Solution {
public:
    int compareVersion(string version1, string version2) {
        auto posL1 = 0;
        auto posL2 = 0;
        while (posL1 != string::npos && posL2 != string::npos) {
            auto posR1 = version1.find('.', posL1);
            auto posR2 = version2.find('.', posL2);
            int v1 = stoi(version1.substr(posL1, posR1 == string::npos ? posR1 : posR1 - posL1));
            int v2 = stoi(version2.substr(posL2, posR2 == string::npos ? posR2 : posR2 - posL2));
            if (v1 > v2) {
                return 1;
            }
            if (v1 < v2) {
                return -1;
            }
            posL1 = posR1 == string::npos ? posR1 : posR1 + 1;
            posL2 = posR2 == string::npos ? posR2 : posR2 + 1;
        }
        while (posL1 != string::npos) {
            auto posR1 = version1.find('.', posL1);
            int v1 = stoi(version1.substr(posL1, posR1 == string::npos ? posR1 : posR1 - posL1));
            if (v1 != 0) {
                return 1;
            }
            posL1 = posR1 == string::npos ? posR1 : posR1 + 1;
        }
        while (posL2 != string::npos) {
            auto posR2 = version2.find('.', posL2);
            int v2 = stoi(version2.substr(posL2, posR2 == string::npos ? posR2 : posR2 - posL2));
            if (v2 != 0) {
                return -1;
            }
            posL2 = posR2 == string::npos ? posR2 : posR2 + 1;
        }
        return 0;
    }
static constexpr auto testEntry = &Solution::compareVersion;
};

} // end namespace LC165

#endif /* LC165_h */
