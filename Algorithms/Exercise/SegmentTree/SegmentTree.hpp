//
//  SegmentTree.hpp
//  Algorithms
//
//  Created by Jun Chen on 4/23/25.
//

#ifndef SegmentTree_hpp
#define SegmentTree_hpp

namespace SegmentTree {
    template <typename Derived>
    class Mergeable {
    public:
        static void merge(Derived& dst, const Derived& src1, const Derived& src2) {
            static_cast<Derived*>(&dst)->mergeImpl(src1, src2);
        }

        static Derived mergeNew(const Derived& src1, const Derived& src2) {
            Derived merged;
            static_cast<Derived*>(&merged)->mergeImpl(src1, src2);
            return merged;
        }

        void mergeFrom(const Derived& src1, const Derived& src2) {
            static_cast<Derived*>(this)->mergeImpl(src1, src2);
        }
        
        void mergeLeft(const Derived& srcLeft) {
            static_cast<Derived*>(this)->mergeLeftImpl(srcLeft);
        }

        void mergeRight(const Derived& srcRight) {
            static_cast<Derived*>(this)->mergeRightImpl(srcRight);
        }

    protected:
        template <typename T = Derived,
        typename = std::enable_if_t<std::is_same<T, Mergeable<T>>::value>>
        void mergeImpl(const Derived& src1, const Derived& src2) {
            static_assert(!std::is_same<Mergeable<Derived>, Derived>::value,
                "Mergeable is not meant to provide mergeImpl(); override it in the final class.");
        }
        template <typename T = Derived,
        typename = std::enable_if_t<std::is_same<T, Mergeable<T>>::value>>
        void mergeLeftImpl(const Derived& srcLeft) {
            static_assert(!std::is_same<Mergeable<Derived>, Derived>::value,
                "Mergeable is not meant to provide mergeLeftImpl(); override it in the final class.");
        }
        template <typename T = Derived,
        typename = std::enable_if_t<std::is_same<T, Mergeable<T>>::value>>
        void mergeRightImpl(const Derived& srcRight) {
            static_assert(!std::is_same<Mergeable<Derived>, Derived>::value,
                "Mergeable is not meant to provide mergeRightImpl(); override it in the final class.");
        }
    };


    template <typename Derived>
    class Mergeable_Cummulative : public Mergeable<Derived> {
        static_assert(!std::is_same<Derived, Mergeable_Cummulative<Derived>>::value,
            "Mergeable_Cummulative<Derived> cannot be instantiated directly as a final class.");
    public:
        static constexpr bool is_cumulative = true;

    protected:
        template <typename T = Derived,
        typename = std::enable_if_t<std::is_same<T, Mergeable_Cummulative<T>>::value>>
        void mergeImpl(const Derived& src1, const Derived& src2) {
            static_assert(!std::is_same<Mergeable_Cummulative<Derived>, Derived>::value,
                "Mergeable_Cummulative is not meant to provide mergeImpl(); override it in the final class.");
        }
        template <typename T = Derived,
        typename = std::enable_if_t<std::is_same<T, Mergeable_Cummulative<T>>::value>>
        void mergeLeftImpl(const Derived& srcLeft) {
            static_assert(!std::is_same<Mergeable_Cummulative<Derived>, Derived>::value,
                "Mergeable_Cummulative is not meant to provide mergeLeftImpl(); override it in the final class.");
        }
        template <typename T = Derived,
        typename = std::enable_if_t<std::is_same<T, Mergeable_Cummulative<T>>::value>>
        void mergeRightImpl(const Derived& srcRight) {
            static_assert(!std::is_same<Mergeable_Cummulative<Derived>, Derived>::value,
                "Mergeable_Cummulative is not meant to provide mergeRightImpl(); override it in the final class.");
        }
    };

    template <typename Derived>
    class Mergeable_Ordered : public Mergeable<Derived> {
        static_assert(!std::is_same<Derived, Mergeable_Ordered<Derived>>::value,
            "Mergeable_Ordered<Derived> cannot be instantiated directly as a final class.");
    public:
        static constexpr bool is_cumulative = false;

    protected:
        template <typename T = Derived,
        typename = std::enable_if_t<std::is_same<T, Mergeable_Ordered<T>>::value>>
        void mergeImpl(const Derived& src1, const Derived& src2) {
            static_assert(!std::is_same<Mergeable_Ordered<Derived>, Derived>::value,
                "Mergeable_Ordered is not meant to provide mergeImpl(); override it in the final class.");
        }
        template <typename T = Derived,
        typename = std::enable_if_t<std::is_same<T, Mergeable_Ordered<T>>::value>>
        void mergeLeftImpl(const Derived& srcLeft) {
            static_assert(!std::is_same<Mergeable_Ordered<Derived>, Derived>::value,
                "Mergeable_Ordered is not meant to provide mergeLeftImpl(); override it in the final class.");
        }
        template <typename T = Derived,
        typename = std::enable_if_t<std::is_same<T, Mergeable_Ordered<T>>::value>>
        void mergeRightImpl(const Derived& srcRight) {
            static_assert(!std::is_same<Mergeable_Ordered<Derived>, Derived>::value,
                "Mergeable_Ordered is not meant to provide mergeRightImpl(); override it in the final class.");
        }
    };

namespace utils {
    size_t smallestPowerOf2(size_t n) {
        if (n == 0) return 1;
        n--;
        n |= n >> 1;
        n |= n >> 2;
        n |= n >> 4;
        n |= n >> 8;
        n |= n >> 16;
        n++;
        return n;
    }
}

namespace SegmentArithmetics {
template<typename RecType, typename ValType = RecType>
class MaxSum : public Mergeable_Ordered<MaxSum<RecType, ValType>> {
    static_assert(std::is_arithmetic<RecType>::value, "RecType must be a numeric type.");
    static_assert(std::is_arithmetic<ValType>::value, "ValType must be a numeric type.");
    // Default initialization of node is essential for correct merging and notational convenience
public:
    using Node = MaxSum<RecType, ValType>;
    using T = RecType;
    using V = ValType;
    MaxSum<RecType, ValType>()
    : maxSum{std::numeric_limits<V>::min()}
    , prefSum{0}
    , suffSum{0}
    , totalSum{std::numeric_limits<V>::min()} {
    }

    MaxSum<RecType, ValType>(V maxSum, V prefSum, V suffSum, V totalSum)
    : maxSum{maxSum}
    , prefSum{prefSum}
    , suffSum{suffSum}
    , totalSum{totalSum} {
    }


    MaxSum<RecType, ValType>(const T& rec)
    : maxSum(rec)
    , prefSum(rec > 0 ? rec : 0)
    , suffSum(rec > 0 ? rec : 0)
    , totalSum(rec) {
    }

    void operator= (const T& rec) {
        maxSum = rec;
        prefSum = rec > 0 ? rec : 0;
        suffSum = rec > 0 ? rec : 0;
        totalSum = rec;
    }

    void leafInit(const T& rec = std::numeric_limits<T>::min()) {
        maxSum = rec;
        prefSum = rec > 0 ? rec : 0;
        suffSum = rec > 0 ? rec : 0;
        totalSum = rec;
    }

    static void leafInit(Node& node, const T& rec = std::numeric_limits<T>::min()) {
        node = Node{rec, V{rec > 0 ? rec : 0}, V{rec > 0 ? rec : 0}, V{rec}};
    }

    static V extractVal(const Node& node) {
        return node.maxSum;
    }

public:
    void mergeImpl(const Node& sL, const Node& sR) {
        maxSum = max(max(sL.maxSum, sR.maxSum), sL.suffSum + sR.prefSum);
        prefSum = max(sL.prefSum, sL.totalSum + sR.prefSum);
        suffSum = max(sL.suffSum + sR.totalSum, sR.suffSum);
        totalSum = sL.totalSum + sR.totalSum;
    }
    void mergeLeftImpl(const Node& sL) {
        maxSum = max(max(sL.maxSum, maxSum), sL.suffSum + prefSum);
        prefSum = max(sL.prefSum, sL.totalSum + prefSum);
        suffSum = max(sL.suffSum + totalSum, suffSum);
        totalSum += sL.totalSum;
    }
    void mergeRightImpl(const Node& sR) {
        maxSum = max(max(maxSum, sR.maxSum), suffSum + sR.prefSum);
        prefSum = max(prefSum, totalSum + sR.prefSum);
        suffSum = max(suffSum + sR.totalSum, sR.suffSum);
        totalSum += sR.totalSum;
    }
private:
    V maxSum;
    V prefSum;
    V suffSum;
    V totalSum;
};
}

template<class NodeType>
class SegTree_Efficient {
    using T = NodeType::T;
    using V = NodeType::V;
    size_t _m;
    size_t _n;
    std::vector<NodeType> _t;

#define CANNOT_WRAP_AROUND 1;

    public:

#ifndef CANNOT_WRAP_AROUND
    /* For a tree to cover an array of size _m == 7, make space-efficient
       memory layout where the tree is of minimal size to contain all
       elements, with 0 being discarded by convention and for notational
       convenience.
       NOTE the first element in array corresponds to the first leaf node,
       which wraps around into the same parent node as the last leaf.
                   1
            /              \
          2                  3
        /   \              /   \
       4     5            6    (7)
      / \   / \         /   \
    (8)(9)(10)(11)   (12)  (13)
    */
   
    SegTree_Efficient(size_t n) : _m(n), _n(_m), _t(2*_n) {}
#else
    /* To prevent the wrap-around menthioned above, allocate extra spaces
       by making a perfect binary tree
                       1
              /                  \
            2                      3
         /     \               /        \
        4       5            6           7
      /  \     /  \        /  \        /    \
    (8) (9) (10) (11)   (12) (13)    (14)   15
    */
    SegTree_Efficient(size_t n) : _m(n), _n(utils::smallestPowerOf2(_m)),  _t(2*_n) {}
#endif

    void build(const std::vector<T>& arr) {
        for (size_t i = 0; i < _m; i ++) {
            NodeType::leafInit(_t[_n+i], arr[i]);
        }
        for (size_t i = _m; i < _n; i ++) {
            NodeType::leafInit(_t[_n+i], INT_MIN);
        }
        for (size_t i = _n-1; i > 0; i --) {
            _t[i].mergeFrom(_t[i<<1], _t[i<<1 | 1]);
        }
    }

    void update(size_t i, T v) {
        NodeType::leafInit(_t[_n+i], v);
        for (size_t j = (_n+i) >> 1; j > 0; j >>= 1) {
            _t[j].mergeFrom(_t[j<<1], _t[j<<1 | 1]);
        }
    }

    V queryRange(size_t l, size_t r) {
        if constexpr (NodeType::is_cumulative) {
            NodeType res;
            for (l += _n, r += _n; l < r; l >>= 1, r >>= 1) {
                if (l & 1) {
                    res = NodeType::mergeNew(res, _t[l++]);
                }
                if (r & 1) {
                    res = NodeType::mergeNew(_t[--r], res);
                }
            }
            return NodeType::extractVal(res);
        } else {
            NodeType resL{}, resR{};
            for (l += _n, r += _n; l < r; l >>= 1, r >>= 1) {
                if (l & 1) {
                    resL.mergeRight(_t[l++]);
                }
                if (r & 1) {
                    resR.mergeLeft(_t[--r]);
                }
            }
            return NodeType::extractVal(NodeType::mergeNew(resL, resR));
        }
    }

    V queryFullRange() {
        if constexpr (NodeType::is_cumulative) {
            return NodeType::extractVal(_t[1]);
        } else {
            return NodeType::extractVal(queryRange(0, _m));
        }
    }
};

template<class NodeType>
class SegTree_Hierarchical {
    using T = NodeType::T;
    using V = NodeType::V;
    size_t _m;
    size_t _n;
    std::vector<NodeType> _t;

public:

    SegTree_Hierarchical(size_t n) : _m(n), _n(utils::smallestPowerOf2(_m)), _t(2*_n) {}
    
    void build(const std::vector<T>& arr) {
        buildHelper(arr, 0, _n, 0, _m, 1);
    }

    void update(size_t i, T v) {
        NodeType::leafInit(_t[_n+i], v);
        for (size_t j = (_n+i) >> 1; j > 0; j >>= 1) {
            NodeType::merge(_t[j], _t[j<<1], _t[j<<1 | 1]);
        }
    }
    
    V queryRange(size_t l, size_t r) {
        return NodeType::extractVal(queryHelper(0, _n, l, r, 1));
    }
    
    V queryFullRange() {
        return NodeType::extractVal(_t[1]);
    }

private:

    void buildHelper(const std::vector<T>& arr, size_t L, size_t R, size_t l, size_t r, size_t root) {
        if (l >= R || r <= L) {
             NodeType::leafInit(_t[root]);
            return;
        }
        if (R - L == 1) {
            NodeType::leafInit(_t[root], arr[l]);
        } else {
            size_t M((L + R) / 2);
            buildHelper(arr, L, M, l, M < r ? M : r, root << 1);
            buildHelper(arr, M, R, l > M ? l : M, r, root << 1 | 1);
            NodeType::merge(_t[root], _t[root << 1], _t[root << 1 | 1]);
        }
    }

    NodeType queryHelper(size_t L, size_t R, size_t l, size_t r, size_t root) {
        NodeType ret;
        if (l >= R || r <= L) {
             NodeType::leafInit(ret);
            return ret;
        }
        if (l == L && r == R) {
            return _t[root];
        } else {
            size_t M((L + R) / 2);
            NodeType tL = queryHelper(L, M, l, M, root << 1);
            NodeType tR = queryHelper(M, R, M, r, root << 1 | 1);
            NodeType::mergeNode(ret, tL, tR);
        }
        return ret;
    }
};

} // end namespace SegmentTree

#endif /* SegmentTree_hpp */
