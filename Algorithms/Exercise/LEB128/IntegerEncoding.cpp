//
//  IntegerEncoding.cpp
//  Algorithms
//
//  Created by Jun Chen on 4/20/25.
//

#include <cassert>
#include "IntegerEncoding.hpp"

#define SEGMENT_LEN 7

namespace IntegerEncoding {

// Generic implementation capable of handling negative integers
int IntEncoder::getCodeLen(int x) {
    int vTerminal(x >> 31); // This terminal value is -1 for negatives and 0 otherwise

    int nShiftR = SEGMENT_LEN;
    x >>= SEGMENT_LEN - 1; // Explicitly reserving 1 sign bit

    while (x != vTerminal) {
        x >>= SEGMENT_LEN;
        nShiftR += SEGMENT_LEN;
    }
    return nShiftR;
}

void IntEncoder::encodeInt(void * const dstBuff, int x) {
    unsigned char *p = static_cast<unsigned char*>(dstBuff);
    int firstSegPos(getCodeLen(x) - SEGMENT_LEN);
    for (int i = firstSegPos; i > 0; i -= SEGMENT_LEN) {
        *p = ((x >> i) & 0x7F) | 0x80;
        p ++;
    }
    *p = (x & 0x7F);
}

int IntEncoder::decodeInt(void const * const srcBuff) {
    unsigned char const *p = static_cast<unsigned char const *>(srcBuff);
    int nBits(0), nBitsMax(int((sizeof(int) * 8 + SEGMENT_LEN - 1) / SEGMENT_LEN) * SEGMENT_LEN );
    
    int y(!(p[0] & 0x40) ? 0 : -1); // Starting negatives with -1, otherwise 0

    while(nBits < nBitsMax) {
        // Clear off, and assign to, lower SEGMENT_LEN bits
        y &= ~0x7F;
        y |= *p & 0x7F;
        nBits += SEGMENT_LEN;

        bool isLastSeg = !(*p & 0x80);
        if (isLastSeg) {
            break;
        }

        p ++;
        y <<= SEGMENT_LEN;
    }
    assert(nBits <= nBitsMax);
    
    return y;
}

// Positive-only implementation
int IntEncoder_Positive::getCodeLen(int x) {
    int nShiftR = SEGMENT_LEN;
    while ((x >> nShiftR) != 0) {
        nShiftR += SEGMENT_LEN;
    }
    return nShiftR;
}

void IntEncoder_Positive::encodeInt(void * const dstBuff, int x) {
    assert(x > 0);
    unsigned char *p = static_cast<unsigned char*>(dstBuff);
    int firstSegPos(getCodeLen(x) - SEGMENT_LEN);
    for (int i = firstSegPos; i > 0; i -= SEGMENT_LEN){
        *p = ((x >> i) & 0x7F) | 0x80;
        p ++;
    }
    *p = (x & 0x7F);
}

int IntEncoder_Positive::decodeInt(void const * const srcBuff) {
    unsigned char const *p = static_cast<unsigned char const *>(srcBuff);
    int nBits(0), nBitsMax(int((sizeof(int) * 8 + SEGMENT_LEN - 1) / SEGMENT_LEN) * SEGMENT_LEN );

    int y(0);
    
    while(nBits < nBitsMax) {
        y |= *p & 0x7F;
        nBits += SEGMENT_LEN;

        bool isLastSeg = !(*p & 0x80);
        if (isLastSeg) {
            break;
        }

        p ++;
        y <<= SEGMENT_LEN;
    }
    assert(nBits <= nBitsMax);
    
    return y;
}

} // end namespace IntegerEncoding
