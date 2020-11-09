/*
 * Divide-Two-Integers.cpp
 *
 *  Created on: Mar 2, 2017
 *      Author: Zephyr
 */
#define INT_MAX (1<<31)-1
#define INT_MIN (1<<31)*(-1)
int divide(int dividend, int divisor){
	if(dividend == 0)return 0;
	int flag = 1;
	long long int a = dividend; long long int b = divisor;
	if(a<0){flag=0-flag; a=0-a;}
	if(b<0){flag=0-flag; b=0-b;}
	if(b==1 && flag==1 && a>=INT_MAX)return INT_MAX;
	if(b==1 && flag==-1 && -a<=INT_MIN)return INT_MIN;
	long long int ans = 0;
	while(a>=b){
		long long int tmp = b;
		int i=0;
		while(a>=tmp){
			tmp<<=1;
			i++;
		}
		i--;
		tmp>>=1;
		ans += (1<<i);
		a-=tmp;
	}
	if(flag == 1 && ans>=INT_MAX)return INT_MAX;
	if(flag == -1 && -ans<=INT_MIN)return INT_MIN;
	if(flag == -1)return 0-ans;
	return ans;
}
