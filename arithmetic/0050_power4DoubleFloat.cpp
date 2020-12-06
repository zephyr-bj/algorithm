/*
 * Power-of-Double-Float.cpp
 *
 *  Created on: Mar 12, 2017
 *  Updated on: Dec 06, 2020
 *      Author: Zephyr
 */
    double myPow(double x, int n) {
        if(x==double(1)||x==double(0)||n==1)return x;
        double ans = 1;
        unsigned long long p;
        if (n < 0) {
            p = -(long long)(n);
            x = 1 / x;
        } else {
            p = n;
        }
        while (p) {
            if (p & 1)ans *= x;
            x *= x;
            p >>= 1;
        }
        return ans;
    }
};
