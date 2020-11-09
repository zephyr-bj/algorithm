/*
 * Power-of-Double-Float.cpp
 *
 *  Created on: Mar 12, 2017
 *      Author: Zephyr
 */

    double myPow(double x, int n) {
        if(x==0)return 0;
        if(x==1)return 1;
        if(x==-1)return n%2?-1:1;
        if(n==0)return 1;
        if(n==1)return x;
        unsigned long long maxd=0x7ff0000000000000;
        double *maxdouble=(double *)(&maxd);
        double ans=1;
        double tmp=ans>=0?ans:(ans*(-1));
        if(n>0){
            while(n>0 && tmp>0 && tmp<(*maxdouble)){
                ans*=x;
                n--;
                tmp=ans>=0?ans:(ans*(-1));
            }
        }else{
            while(n<0 && tmp>0 && tmp<(*maxdouble)){
                ans/=x;
                n++;
                tmp=ans>=0?ans:(ans*(-1));
            }
        }
        return ans;
    }

