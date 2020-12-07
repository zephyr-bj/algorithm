/*
 * Single-Number-II.cpp
 *
 *  Created on: May 10, 2017
 *      Author: Zephyr
 */
using namespace std;

int singleNumber(int A[], int n){
	vector<int>bin(32,0);
	for(int i=0; i<n; i++){
		for(int j=0; j<32; j++){
			if(A[i]&(1<<j))bin[j]++;
		}
	}
	int ans=0;
	for(int j=0; j<32; j++){
		if(bin[j]%3!=0)ans |= (1<<j);
	}
	return ans;
}

int singleNumber(vector<int> A) {
    int ones = 0, twos = 0;
    for(int i = 0; i < A.size; i++){
        ones = (ones ^ A[i]) & ~twos;
        twos = (twos ^ A[i]) & ~ones;
    }
    return ones;
}

