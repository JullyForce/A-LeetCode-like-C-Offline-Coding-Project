//
//  LC3410.hpp
//  Algorithms
//
//  Created by J.C. on 2/22/25.
//

#ifndef LC3410_h
#define LC3410_h

#include <vector>
#include <limits>
#include <algorithm>

#include "../Exercise/SegmentTree/SegmentTree.hpp"

using namespace std;

namespace LC3410 {

//namespace SegmentTree {
//
//template<typename T, typename V>
//struct Node {
//    V maxSum;
//    V prefSum;
//    V suffSum;
//    V rangeSum;
//    using InputType = T;
//    using ValType = V;
//    static const Node<T, V> nodeInit;
//    static void leafInit(Node<T, V>& d, const T& v) {
//        d = Node<T, V>{V{v}, V{v>0 ? v : 0}, V{v>0 ? v : 0}, V{v}};
//    }
//    static V extractVal(const Node<T, V>& a) {
//        return a.maxSum;
//    }
//    static void mergeNode(Node<T, V>& d, const Node<T, V>& sL, const Node<T, V>& sR) {
//        d.maxSum = max(max(sL.maxSum, sR.maxSum), sL.suffSum + sR.prefSum);
//        d.prefSum = max(sL.prefSum, sL.rangeSum + sR.prefSum);
//        d.suffSum = max(sL.suffSum + sR.rangeSum, sR.suffSum);
//        d.rangeSum = sL.rangeSum + sR.rangeSum;
//    }
//    static Node<T, V> mergeNode(const Node<T, V>& sL, const Node<T, V>& sR) {
//        Node<T, V> d;
//        d.maxSum = max(max(sL.maxSum, sR.maxSum), sL.suffSum + sR.prefSum);
//        d.prefSum = max(sL.prefSum, sL.rangeSum + sR.prefSum);
//        d.suffSum = max(sL.suffSum + sR.rangeSum, sR.suffSum);
//        d.rangeSum = sL.rangeSum + sR.rangeSum;
//        return d;
//    }
//};
//
//size_t smallestPowerOf2(size_t n) {
//    if (n == 0) return 1;
//    n--;
//    n |= n >> 1;
//    n |= n >> 2;
//    n |= n >> 4;
//    n |= n >> 8;
//    n |= n >> 16;
//    n++;
//    return n;
//}
//
//template<typename T, typename V>
//const Node<T, V> Node<T, V>::nodeInit = {std::numeric_limits<V>::min, 0, 0, 0};
//
//template<class NodeType>
//class SegTree_trivial {
//    using T = NodeType::InputType;
//    size_t _m;
//    size_t _n;
//    vector<NodeType> _t;
//#define CANNOT_WRAP_ARROUND 1;
//
//    public:
//
//#ifndef CANNOT_WRAP_ARROUND
//    SegTree_trivial(size_t n) : _m(n), _n(_m), _t(2*_n) {}
//#else
//    SegTree_trivial(size_t n) : _m(n), _n(smallestPowerOf2(_m)),  _t(2*_n) {}
//#endif
//
//    void build(const vector<T>& arr) {
//        for (size_t i = 0; i < _m; i ++) {
//            NodeType::leafInit(_t[_n+i], arr[i]);
//        }
//        for (size_t i = _m; i < _n; i ++) {
//            NodeType::leafInit(_t[_n+i], INT_MIN);
////            _t[_n+i] = NodeType::nodeInit;
//        }
//        for (size_t i = _n-1; i > 0; i --) {
//            NodeType::mergeNode(_t[i], _t[i<<1], _t[i<<1 | 1]);
//        }
//    }
//
//    void update(size_t i, T v) {
//        NodeType::leafInit(_t[_n+i], v);
//        for (size_t j = (_n+i) >> 1; j > 0; j >>= 1) {
//            NodeType::mergeNode(_t[j], _t[j<<1], _t[j<<1 | 1]);
//        }
//    }
//
//#ifndef CANNOT_WRAP_ARROUND
//    // TODO: use two intermediary nodes for left- and right- merging
//    NodeType::ValType queryRange(size_t l, size_t r) {
//        NodeType res = NodeType::nodeInit;
//        for (l += _n, r += _n; l < r; l >>= 1, r >>= 1) {
//            if (l & 1) {
//                res = NodeType::mergeNode(_t[l++], res);
//            }
//            if (r & 1) {
//                res = NodeType::mergeNode(res, _t[--r]);
//            }
//        }
//        return NodeType::extractVal(res);
//    }
//#endif
//
//    NodeType::ValType queryFullRange() {
//        return NodeType::extractVal(_t[1]);
//    }
//};
//
//// TODO: still not buggy, and needs clean up
//template<class NodeType>
//class SegTree_completeBinary {
//    using T = NodeType::InputType;
//    size_t _m;
//    size_t _n;
//    vector<NodeType> _t;
//
//public:
//
//    SegTree_completeBinary(size_t n) : _m(n), _n(smallestPowerOf2(_m)), _t(2*_n) {}
//    
//    void build(const vector<T>& arr) {
////        for (size_t i = 0; i < _m; i ++) {
////            NodeType::leafInit(_t[_n+i], arr[i]);
////        }
//        buildHelper(arr, 0, _n, 0, _m, 1);
//    }
//
//    void update(size_t i, T v) {
//        NodeType::leafInit(_t[_n+i], v);
//        for (size_t j = (_n+i) >> 1; j > 0; j >>= 1) {
//            NodeType::mergeNode(_t[j], _t[j<<1], _t[j<<1 | 1]);
//        }
//    }
//    
//    NodeType::ValType queryRange(size_t l, size_t r) {
//        return NodeType::extractVal(queryHelper(0, _n, l, r, 1));
//    }
//    
//    NodeType::ValType queryFullRange() {
//        return NodeType::extractVal(_t[1]);
//    }
//
//private:
//
//    void buildHelper(const vector<T>& arr, size_t L, size_t R, size_t l, size_t r, size_t root) {
//        if (l >= R || r <= L) {
//            NodeType::leafInit(_t[root], INT_MIN);
////            _t[idxRoot] = NodeType::nodeInit;
//            return;
//        }
//        if (R - L == 1) {
//            NodeType::leafInit(_t[root], arr[l]);
//        } else {
//            size_t M((L + R) / 2);
//            buildHelper(arr, L, M, l, M < r ? M : r, root << 1);
//            buildHelper(arr, M, R, l > M ? l : M, r, root << 1 | 1);
//            NodeType::mergeNode(_t[root], _t[root << 1], _t[root << 1 | 1]);
//        }
//    }
//
//    NodeType queryHelper(size_t L, size_t R, size_t l, size_t r, size_t root) {
//        NodeType ret;
//        if (l >= R || r <= L) {
//            NodeType::leafInit(ret, INT_MIN);
////            _t[idxRoot] = NodeType::nodeInit;
//            return ret;
//        }
//        if (l == L && r == R) {
//            return _t[root];
//        } else {
//            size_t M((L + R) / 2);
//            NodeType tL = queryHelper(L, M, l, M, root << 1);
//            NodeType tR = queryHelper(M, R, M, r, root << 1 | 1);
//            NodeType::mergeNode(ret, tL, tR);
//        }
//        return ret;
//    }
//};
//
////#define TRIVIAL_OP
//
//#ifdef TRIVIAL_OP
//template<class NodeType>
//using SegTree = SegTree_trivial<NodeType>;
//#else
//template<class NodeType>
//using SegTree = SegTree_completeBinary<NodeType>;
//#endif
//
//};

template<class NodeType>
//using SegTree = SegmentTree::SegTree_Efficient<NodeType>;
using SegTree = SegmentTree::SegTree_Hierarchical<NodeType>;

class Solution {
public:
    long long maxSubarraySum(vector<int>& nums) {
        using Node = SegmentTree::SegmentArithmetics::MaxSum<int, long long>;
        using SegTree = SegTree<Node>;
        size_t n(nums.size());

        long long sumVal(0), minVal(LLONG_MAX), maxVal(LLONG_MIN);
        unordered_map<int, vector<int>> mapVal2Pos;
        for (int i = 0; i < n; i ++) {
            mapVal2Pos[nums[i]].push_back(i);
            sumVal += nums[i];
            minVal = min(minVal, (long long)nums[i]);
            maxVal = max(maxVal, (long long)nums[i]);
        }

        if (maxVal < 0) {
            return maxVal;
        }
        if (minVal >= 0) {
            return sumVal;
        }

        SegTree t(n);
        t.build(nums);
        maxVal = t.queryFullRange();
        for (auto & [x, v] : mapVal2Pos) {
            if (x >= 0) {
                continue;
            }
            for (int i : v) {
                t.update(i, 0);
            }

            maxVal = max(maxVal, t.queryFullRange());

            for (int i : v) {
                t.update(i, x);
            }
        }

        return maxVal;
    }
    static constexpr auto testEntry = &Solution::maxSubarraySum;
};

} // end namespace LC3410

#endif /* LC3410_h */
