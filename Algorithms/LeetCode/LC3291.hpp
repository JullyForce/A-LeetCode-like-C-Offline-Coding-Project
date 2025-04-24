//
//  LC3291.hpp
//  Algorithms
//
//  Created by J.C. on 9/22/24.
//

#ifndef LC3291_h
#define LC3291_h

#include <vector>
#include <algorithm>

using namespace std;

namespace LC3291 {

class Solution {
private:
    struct TrieNode {
        TrieNode * child[26];

        TrieNode * suff{nullptr};
        int depth{0};
        int cost{-1};

        TrieNode(int depth = 0, int cost = -1) : depth(depth), cost(cost) {
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
                if (tRoot.child[c-'a'] != nullptr) {
                    p = &tRoot;
                } else {
                    return mem[n-1];
                }
            }
            p = p->child[c-'a'];
            
            if (p->depth == i) {
                mem[i] = 1;
            } else if (i - p->depth - 1 >= 0 && mem[i - p->depth - 1] != -1) {
                int newLen = mem[i - p->depth - 1] + 1;
                if (mem[i] == -1) {
                    mem[i] = newLen;
                } else {
                    mem[i] = min(mem[i], newLen);
                }
            }

            TrieNode * q = p->suff;
            while (q) {
                if (q->cost != -1 && mem[i - q->depth - 1] != -1) {
                    int newLen = mem[i - q->depth - 1] + 1;
                    if (mem[i] == -1) {
                        mem[i] = newLen;
                    } else {
                        mem[i] = min(mem[i] , newLen);
                    }
                }
                q = q->suff;
            }
        }
        return mem[n-1];
    }
    void buildTrie(TrieNode & tRoot, const vector<string> & words) {
        for (int i = 0; i < words.size(); i ++) {
            TrieNode * p = &tRoot;
            const string & s = words[i];
            int depth{0};
            for (const char & c : s) {
                if (p->child[c-'a'] == nullptr) {
                    p->child[c-'a'] = new TrieNode(depth);
                }
                p = p->child[c-'a'];
                depth ++;
            }
            p->cost = 1;
        }
    }
    void DFSLink(TrieNode & tRoot, TrieNode * aNode, string & w) {
        for (int i = 0; i < 26; i ++) {
            if (aNode->child[i] != nullptr) {
                TrieNode * childNode = aNode->child[i];
                w += ('a'+i);
                int j = 1;
                for (; j < w.length(); j ++) {
                    int idx{j};
                    TrieNode * p = &tRoot;
                    while (p != nullptr && idx < w.length()) {
                        TrieNode * q = p->child[w[idx]-'a'];
                        if (q != nullptr) {
                            p = q;
                            idx ++;
                        } else {
                            break;
                        }
                    }
                    if (idx == w.length()) {
                        childNode->suff = p;
                        break;
                    }
                }
                DFSLink(tRoot, childNode, w);
                w.pop_back();
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
                }
            }
        }
    }
    void linkAutomaton(TrieNode & tRoot) {
        for (int i = 0; i < 26; i ++) {
            if (tRoot.child[i]) {
                tRoot.child[i]->suff = &tRoot;
            }
        }
        queue<TrieNode*> Q;
        Q.push(&tRoot);
        BFSLink(Q, tRoot);
    }
public:
    int minValidStrings(vector<string>& words, string target) {
        TrieNode tRoot;
        buildTrie(tRoot, words);
        
        linkAutomaton(tRoot);

        vector<int> mem(target.length(), -1);

        return minHelper(target, tRoot, mem, target.length());
    }
static constexpr auto testEntry = &Solution::minValidStrings;
};

} // end namespace LC3291

#endif /* LC3291_h */
