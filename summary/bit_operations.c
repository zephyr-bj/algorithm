/number of set bits (what about input int or float)
//Rotate an integer n left by k (what about input int)
//reverse bits of an integer 
//swap the neighboring bits. (hits:2)
//find out msb: floor(log2(number)) (hits:3) (log2(x)=log(x)/log(2)) (what about input int)
//is power of two
//is big endian or little endian
//Implement in-place swap. Now implement one won't cause overflow (i.e: can't use addition)

//write a macro to check if nth bit was set
/*The idea is create enough 1's, and move them to the proper*/
#define isSet(num,n) (num) & (1<<(n-1))
//Implement a MACRO(i,j,k) where i is a Hex number, j is the bit position and k is 0/1. So based on k, jth bit in i should be replaced.
#define setbit(i,j,k) i=(k==0)?((~(1<<j))&i):((1<<j)|i)//not very satisfied with this 
//Macro to set the bits
#define Set_Bit(num, start_bit_pos, end_bit_pos) (num) | ((1<<(end_bit_pos-start_bit_pos+1))-1)<<((start_bit_pos)-1)

//Find the Maximum of 2 numbers without using any if-else or any other comparison operator
//cci.20.1 Write a function that adds two numbers. You should not use + or any arithmetic operators.
//int replacePartInt(int N, int B, int A, int k) (hits:2)
//binary print of a float
//find the missing number from a set of successive integers
//reverse bits in a c string (hits:2)
//function to give mask for first 2 non zero (anything except 00) values in int.


//Given an int, write code to return the number of bits that are 1 in O(m) time, where m is the number of bits that are 1.
/*Some CPUs have a single built-in instruction to do it, like: int __builtin_popcount (unsigned int x);*/
int nsetbits(unsigned int n){
	int i;
	for( i=0; n > 0 ; i++ ) n &= (n-1);
	return i;
}
//solution2: by hash table
int table[] = {0,1,1,2,1,2,2,3, 1,2,2,3,2,3,3,4}; 
#define f(x) table[x&(0xf)] 

int count(short num){ 
return f(num) + f(num>>4) + f(num>>8) + f(num>>12); 
}

// Rotate an integer n left by k
int rotLeft32(int n, int k)
{
  return (n << k) | ((unsigned int)n >> (32 - k));
}

//reverse the bits in a integer (hits:3)
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

//swap the neighboring bits. 
unsigned int swapneighborBits(unsigned int a){
	unsigned int mask = 0xaaaaaaaa;
	unsigned int num1 = a & mask;
	unsigned int num2 = a & (mask >> 1);
	return num1 | num2;
}

//Is the given number is of the power of 2 (hits:2)
//alternative method return ((n&(n-1))==0)&&(n!=0))
bool isPower2(unsigned int num){
	unsigned int mask = 0x1;
	if(num & mask != 0) return true;
	else return false;
}

//find whether a machine is big endian or little endian
bool isSmall_endian(){
	short int word = 0x0001;
	char * byte = (char *)&word;
	if(*byte == 1) return true;
	else return false;
}

//Implement in-place swap. 
void swap(int a, int b){
	a ^= b;
	b ^= a;
	a ^= b;
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

//find the missing number from a set of successive integers
//int * x;
//list<int> y(x,x+sizeof(x)/sizeof(x[0]));
int missingN(std::list<int> x, int col){
	if(x.size() == 1) return x.back();
	int out = 0;
	std::list<int> zeros;
	std::list<int> ones;
	std::list<int>::iterator it;
	for(it = x.begin(); it!=x.end(); it++){
		if((*it & (1<<col)) > 0)
			ones.push_back(*it);
		else
			zeros.push_back(*it);
	}
	if(zeros.size() > ones.size()){
		return missingN(ones,col+1);
	}
	else{
		return missingN(zeros,col+1);
	}
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

//cci.20.1 Write a function that adds two numbers. You should not use + or any arithmetic operators.
int add_no_arithm(int a, int b) {
	if (b == 0) return a;
	int sum = a ^ b; // add without carrying
	int carry = (a & b) << 1; // carry, but don’t add
	return add_no_arithm(sum, carry); // recurse
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

