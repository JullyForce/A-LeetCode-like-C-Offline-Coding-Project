//
//  IntegerEncoding.hpp
//  Algorithms
//
//  Created by Jun Chen on 4/20/25.
//

#ifndef IntegerEncoding_h
#define IntegerEncoding_h

namespace IntegerEncoding {

// Generic implementation capable of handling negative integers
class IntEncoder {
    static int getCodeLen(int x);
public:
    static void encodeInt(void * const dstBuff, int x);
    static int decodeInt(void const * const srcBuff);
};


// Positive only implementation
class IntEncoder_Positive {
    static int getCodeLen(int x);
public:
    static void encodeInt(void * const dstBuff, int x);
    static int decodeInt(void const * const srcBuff);
};

} // end namespace IntegerEncoding

#endif /* IntegerEncoding_h */
