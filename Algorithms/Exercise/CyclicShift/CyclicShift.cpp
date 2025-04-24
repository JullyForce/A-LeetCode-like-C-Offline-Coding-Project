//
//  CyclicShift.cpp
//  Algorithms
//
//  Created by Jun Chen on 4/23/25.
//

#include <cassert>
#include <numeric> // std::gcd
#include <utility> // std::swap

#include "./CyclicShift.hpp"


namespace CyclicShift {

void shiftInplace(std::vector<int>& arr, int l, int r, int shift) {
    // Taking an array "arr", a range ["l", "r"), perform in-place, cyclic right shift by "shift" elements
    // A negative "shift" means shifting left
    assert(l >= 0 && r > l && r <= arr.size());
    int len(r - l);
    shift %= len;
    shift += len;
    shift %= len;
    if (len == 0 || shift == 0) {
        return;
    }
    
    int segLen(std::gcd(shift, len)), nRep(len / segLen);
    
    for (int i = 0; i < segLen; i ++) {
        int idx(i);
        int temp(arr[l + idx]);
        for (int j = 0; j < nRep; j ++) {
            idx += shift;
            idx %= len;
            std::swap(temp, arr[l + idx]);
        }
    }
}

} // end namespace CyclicShift
