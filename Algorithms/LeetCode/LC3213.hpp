//
//  LC3213.hpp
//  Algorithms
//
//  Created by Jun Chen on 7/18/24.
//

#ifndef LC3213_h
#define LC3213_h

#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

namespace LC3213 {

class Solution {
private:
    struct TrieNode {
        TrieNode * child[26];
        TrieNode * parent{nullptr};

        TrieNode * suff{nullptr};
        TrieNode * dict{nullptr};
        int depth{0};
        int cost{-1};

        TrieNode(int depth = 0, int cost = -1, TrieNode * parent = nullptr) : depth(depth), cost(cost), parent(parent) {
            fill(begin(child), end(child), nullptr);
        }
    };
    int minHelper(string & target, TrieNode & tRoot, vector<int> & mem, int n) {
        TrieNode * p = &tRoot;
        for (int i = 0; i < n; i ++) {
            char c = target[i];
            if (p->child[c-'a'] == nullptr) {
                while ((p = p->suff) != nullptr) {
                    if (p->child[c-'a'] != nullptr) {
                        break;
                    }
                }
            }
            if (p == nullptr) {
                // if (tRoot.child[c-'a'] != nullptr) {
                //     p = &tRoot;
                // } else {
                    return mem[n-1];
                // }
            }
            p = p->child[c-'a'];
            if (p->cost != -1) {
                if (p->depth == i) {
                    mem[i] = p->cost;
                } else if (i - p->depth - 1 >= 0 && mem[i - p->depth - 1] != -1) {
                    int newCost = p->cost + mem[i - p->depth - 1];
                    if (mem[i] == -1) {
                        mem[i] = newCost;
                    } else {
                        mem[i] = min(mem[i], newCost);
                    }
                }
            }
            TrieNode * q = p->dict;
            while (q) {
                if (q->cost != -1 && mem[i- q->depth -1] != -1) {
                    int newCost = q->cost + mem[i - q->depth - 1];
                    if (mem[i] == -1) {
                        mem[i] = newCost;
                    } else {
                        mem[i] = min(mem[i] , newCost);
                    }
                }
                q = q->dict;
            }
        }
        return mem[n-1];
    }
    void buildTrie(TrieNode & tRoot, const vector<string> & words, const vector<int> & costs) {
        for (int i = 0; i < words.size(); i ++) {
            TrieNode * p = &tRoot;
            const string & s = words[i];
            int depth{0};
            for (const char & c : s) {
                if (p->child[c-'a'] == nullptr) {
                    p->child[c-'a'] = new TrieNode(depth, -1, p);
                }
                p = p->child[c-'a'];
                p->suff = &tRoot;
                depth ++;
            }
            if (p->cost == -1) {
                p->cost = costs[i];
            } else {
                p->cost = min(p->cost, costs[i]);
            }
        }
    }
    void BFSLink(queue<TrieNode*> & Q, TrieNode & tRoot) {
        while (!Q.empty()) {
            TrieNode * aNode = Q.front();
            Q.pop();
            for (int i = 0; i < 26; i ++) {
                if (aNode->child[i] != nullptr) {
                    TrieNode * childNode = aNode->child[i];
                    Q.push(childNode);
                    TrieNode * p = aNode->suff;
                    while (p != nullptr) {
                        if (p->child[i] != nullptr) {
                            childNode->suff = p->child[i];
                            break;
                        }
                        p = p->suff;
                    }
                    while (p != nullptr) {
                        if (p->child[i] != nullptr && p->child[i]->cost != -1) {
                            childNode->dict = p->child[i];
                            break;
                        }
                        p = p->suff;
                    }
                }
            }
        }
    }
    void linkAutomaton(TrieNode & tRoot) {
        queue<TrieNode*> Q;
        Q.push(&tRoot);
        BFSLink(Q, tRoot);
    }
public:
    int minimumCost(string target, vector<string>& words, vector<int>& costs) {
        TrieNode tRoot;
        buildTrie(tRoot, words, costs);
        
        linkAutomaton(tRoot);

        vector<int> mem(target.length(), -1);

        return minHelper(target, tRoot, mem, target.length());
    }
    static constexpr auto testEntry = &Solution::minimumCost;
};

} // end namespace LC3213

#endif /* LC3213_h */
