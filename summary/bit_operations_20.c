//
/* n&(n-1) */ [3]
//(0191) number of set bits (what about input int or float)
//(0231) is power of two
//(0342) power of four

/* bit mask */ [1] 
//Implement a MACRO(i,j,k) where i is a Hex number, j is the bit position and k is 0/1. So based on k, jth bit in i should be replaced.
#define setbit(i,j,k) i=(k==0)?((~(1<<j))&i):((1<<j)|i)//not very satisfied with this 
//Macro to set the bits
#define Set_Bit(num, start_bit_pos, end_bit_pos) (num) | ((1<<(end_bit_pos-start_bit_pos+1))-1)<<((start_bit_pos)-1)
//int replacePartInt(int N, int B, int A, int k) (hits:2)

/*Xor */ [5]
//Implement in-place swap. Now implement one won't cause overflow (i.e: can't use addition)
//cci.20.1 Write a function that adds two numbers. You should not use + or any arithmetic operators.
//(0136) single number
//(0137) single number II
//(0260) single number III

/* bit reverse */ [2]
//(0190) reverse bits of an integer 
//reverse bits in a c string (hits:2)

/* misc */ [9]
//Rotate an integer n left by k (what about input int)
//swap the neighboring bits. (hits:2)
//find out msb (hits:3)
//is big endian or little endian
//Find the Maximum of 2 numbers without using any if-else or any other comparison operator
//binary print of a float
//function to give mask for first 2 non zero (anything except 00) values in int.
//write a macro to check if nth bit was set
//(0201) bitwise ADN of numbers range

/*The idea is create enough 1's, and move them to the proper*/
#define isSet(num,n) (num) & (1<<(n-1))

//(0191) Given an int, write code to return the number of bits that are 1 in O(m) time, where m is the number of bits that are 1.
/*Some CPUs have a single built-in instruction to do it, like: int __builtin_popcount (unsigned int x);*/
int nsetbits(unsigned int n){
	int i;
	for( i=0; n > 0 ; i++ ) n &= (n-1);
	return i;
}

//(0231) Is the given number is of the power of 2 (hits:2)
//alternative method return ((n&(n-1))==0)&&(n!=0))
bool isPower2(unsigned int num){
	unsigned int mask = 0x1;
	if(num & mask != 0) return true;
	else return false;
}

//(0342) power of four
    bool isPowerOfFour(int num) {
        if(num<1)return false;
        return ((num&(num-1))==0) && ((num&0xAAAAAAAA)==0);
    }

/*given a 32 bit number N and 2 numbers(A & B) that determine 2 different bit positions of N how do you make all the bits between A and B 
	equal to another given integer k. given (A,B is in the range [0 to 31] and k<=2^(B-A+1) 
	(so that k fits between B-A+1 bits). Give an O(1) solution for this (hits:2)*/
int replacePartInt(int N, int B, int A, int k){
    unsigned int mask = ((1<<B)-1)&(~((1<<A)-1));
    N &= ~mask;
    N |= k<<A;
    return N;
}

//Implement in-place swap. 
void swap(int a, int b){
	a ^= b;
	b ^= a;
	a ^= b;
}

//cci.20.1 Write a function that adds two numbers. You should not use + or any arithmetic operators.
int add_no_arithm(int a, int b) {
    if (b == 0) return a;
    int sum = a ^ b; // add without carrying
    int carry = (a & b) << 1; // carry, but don’t add
    return add_no_arithm(sum, carry); // recurse
}

//(0136) single number
    int singleNumber(vector<int>& nums) {
        int x = 0;
        for(auto y:nums)x^=y;
        return x;
    }
//(0137) single number II
int singleNumber(vector<int>& s) {
    int t[32] = {0};////Made a array contain 32 elements.
    int sz = s.size();
    int i, j, n;
    for (i = 0; i < sz; ++i){
        n = s[i];
        for (j = 31; j >= 0; --j){
    	    t[j] += n & 1;//Find the last digit.
    	    n >>= 1;
            if (!n) break;
    	}
    }
    int res = 0;
    for (j = 31; j >= 0; --j){
        n = t[j] % 3;//"3" represents k times. 
	if (n) res += 1 << (31 - j);
    }
    return res;
}
//(0260) signle number III
    vector<int> singleNumber(vector<int>& nums) {
        long long i, j, xnor=0;
        int xorG1=0,xorG2=0;
        int n=nums.size();
        for(i=0;i<nums.size();i++){
            xnor^=nums[i];            
        }
        long long m=(xnor&(~(xnor-1)));
        for(i=0;i<nums.size();i++){
            if((m&nums[i])!=0)
                xorG1^=nums[i];
            else
                xorG2^=nums[i];
        }
        return {xorG1,xorG2};
    }

//(0190) reverse the bits in a integer (hits:3)
unsigned int reverseBits(unsigned int num)
{
    unsigned int count = sizeof(num) * 8 - 1;
    unsigned int reverse_num = num;
     
    num >>= 1; 
    while(num)
    {
       reverse_num <<= 1;       
       reverse_num |= num & 1;
       num >>= 1;
       count--;
    }
    reverse_num <<= count;
    return reverse_num;
}

//How will you efficiently bitwise reverse a very long character string efficiently(Dont use the typical bitwise swapping)
/*1) Reverse the long character string at byte level. 
  2) Then do the table look-up to reverse bits in every character of the reversed string*/
void reverseStr(char * str){
	int L = sizeof(str)/sizeof(str[0]);
	for(int i = 0; i<L/2; i++){
		char tmp = str[i];
		str[L-i-1] = tmp;
		str[i] = str[L-i-1];
	}
	for(int i = 0; i<L; i++){
		char a = str[i]; 
		char b = a;
		int count = 7;
		a >>= 1;
		while(a>0){
			b <<= 1;	
			b = b | (a & 1);
			a >>= 1;
			count--;
		}
		b <<= count; 
		str[i] = b;
	}
}

// Rotate an integer n left by k
int rotLeft32(int n, int k){
    return (n << k) | ((unsigned int)n >> (32 - k));
}

//swap the neighboring bits. 
unsigned int swapneighborBits(unsigned int a){
	unsigned int mask = 0xaaaaaaaa;
	unsigned int num1 = a & mask;
	unsigned int num2 = a & (mask >> 1);
	return num1 | num2;
}

// find out msb: floor(log2(number)) (hits:3) (log2(x)=log(x)/log(2)) (what about input int)
int setBitNumber(int n) { 
    if (n == 0) 
        return 0; 
  
    int msb = 0; 
    n = n / 2; 
    while (n != 0) { 
        n = n / 2; 
        msb++; 
    } 
  
    return msb; 
} 

//find whether a machine is big endian or little endian
bool isSmall_endian(){
	short int word = 0x0001;
	char * byte = (char *)&word;
	if(*byte == 1) return true;
	else return false;
}

//binary print
std::string print_binary(std::string val){
	std::string front;
	std::string rear;
	std::string *sp = &front;
	for(int i=0; i<val.size();i++){
		if(val[i] == '.'){
			sp = &rear;
		}
		sp->push_back(val[i]);
	}
	int intpart = atoi(front.c_str());
	double decpart = atof(rear.c_str());
	std::string fpart;
	for(int i=0; i<32;i++){
		if(intpart & (1<<i)){
			fpart[i] = '1';
		}
		else{
			fpart[i] = '0';
		}
	}
	std::string bpart;
	for(int i=0; i<32; i++){
		decpart*=2;
		if(decpart > 1){
			bpart[i] = '1';
			decpart-=1;
		}
		else{
			bpart[i] = '0';
		}
	}
	return fpart+"."+bpart;
}

//Find the Maximum of 2 numbers without using any if-else or any other comparison operator
int maximum(int a, int b){
    int k = ((a-b)&0x8000000)>>31;
    return (1-k)*a+k*b;
}

//function to give mask for first 2 non zero (anything except 00) values in int.
int mask2nz(int a){
    int L = 8*sizeof(char);
    unsigned int mask = 0;
    int N = 2;
    for(int i = L-1; i>=0; i--){
        if (a & (1<<i) ){
            --N;
            mask |= 1<<i;
        }
        if(N<1) break;
    }
    return mask;
}

//(0201) bitwise ADN of numbers range
// only the highest NO zero bits left
    int rangeBitwiseAnd(int m, int n) {
        int trans = 0;
        while(m != n) 
        {
            ++ trans;
            m >>= 1;
            n >>= 1;
        }
        return m << trans;
    }

