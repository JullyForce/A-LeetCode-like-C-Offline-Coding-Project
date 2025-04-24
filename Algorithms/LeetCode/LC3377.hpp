//
//  LC3377.hpp
//  Algorithms
//
//  Created by J.C. on 12/24/24.
//

#ifndef LC3377_h
#define LC3377_h

#include <vector>
#include <queue>

using namespace std;

namespace LC3377 {

#define N 10000
#define N 10000
class Solution {
private:
    vector<bool> buildPrimeTable(int sz) {
        vector<bool> isPrime(sz+1, true);
        vector<int> primes{2, 3, 5, 7};
        isPrime[0] = false;
        isPrime[1] = false;
        isPrime[4] = false;
        isPrime[6] = false;
        isPrime[8] = false;
        isPrime[9] = false;
        for (int i = 10; i <= sz; i ++) {
            bool isP(true);
            for (int f : primes) {
                if (f * f > i) {
                    break;
                }
                if (i % f == 0) {
                    isP = false;
                    break;
                }
            }
            if (isP) {
                primes.push_back(i);
            }
            isPrime[i] = isP;
        }
        // for (int p : primes) {
        //     cout << p << ", ";
        // }
        // cout << endl;
        return isPrime;
    }
    void BFSHelper(vector<int>& cost, const vector<bool>& forbidden, int nDigits, int n) {
        queue<int> Q;
        if (!forbidden[n]) {
            Q.push(n);
            cost[n] = n;
        }
        while (!Q.empty()) {
            int x = Q.front();
            Q.pop();
            int e(1);
            int t(x), currCost(cost[x]);
            // cout << "x: " << x << endl;
            for (int i = 0; i < nDigits; i ++) {
                int d = t % 10;
                t /= 10;
                if (d > 0 && i != nDigits-1 || d > 1) {
                    int y = x - e;
                    if (!forbidden[y] && (currCost + y < cost[y] || cost[y] == -1)) {
                        cost[y] = currCost + y;
                        // cout << "cost[" << y << "] update: " << cost[y] << endl;
                        Q.push(y);
                    }
                }
                if (d < 9) {
                    int y = x + e;
                    if (!forbidden[y] && (currCost + y < cost[y] || cost[y] == -1)) {
                        cost[y] = currCost + y;
                        // cout << "cost[" << y << "] update: " << cost[y] << endl;
                        Q.push(y);
                    }
                }
                e *= 10;
            }
        }
    }
public:
    int minOperations(int n, int m) {
        auto isPrime = buildPrimeTable(N);
        vector<int> cost(N+1, -1);
        
        int nDigits(0);
        int x(n);
        while (x > 0) {
            nDigits ++;
            x /= 10;
        }
        // cout << "nDigits: " << nDigits << endl;
        BFSHelper(cost, isPrime, nDigits, n);
        
        return cost[m];
        
    }
    static constexpr auto testEntry = &Solution::minOperations;
};

} // end namespace LC3377

#endif /* LC3377_h */
