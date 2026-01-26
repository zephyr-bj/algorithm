//
/* n&(n-1) */ [3]
//(0191) number of set bits (what about input int or float)
//(0231) is power of two
//(0342) power of four

/* bit mask */ [4] 
//write a macro to check if nth bit was set
//Implement a MACRO(i,j,k) where i is a Hex number, j is the bit position and k is 0/1. So based on k, jth bit in i should be replaced.
//Macro to set the bits
//int replacePartInt(int N, int B, int A, int k) (hits:2)

/*Xor */ [5]
//Implement in-place swap. Now implement one won't cause overflow (i.e: can't use addition)
//cci.20.1 Write a function that adds two numbers. You should not use + or any arithmetic operators.
//(0136) single number
//(0137) single number II
//(0260) single number III

/* bit reverse */ [2]
//(0190) reverse bits of an integer 
//reverse bits in a c string (hits:2

/* bit shift */ [2]
//Rotate an integer n left by k (what about input int)
//alternate big endian and small endian

/* misc */ [7]
//swap the neighboring bits. (hits:2)
//find out msb (hits:3)
//Find the Maximum of 2 numbers without using any if-else or any other comparison operator
//binary print of a float
//function to give mask for first 2 non zero (anything except 00) values in int.
//(0201) bitwise AND of numbers range

/* check memory pin */ [2]
//check data pin
//check address pin

//(0191) Given an int, write code to return the number of bits that are 1 in O(m) time, where m is the number of bits that are 1.
int nsetbits(int x){
    int ans = 0;
    unsigned int num = (unsigned int)x;
    while(num!=0){
        num &=(num-1);
        ans++;
    }
    return ans;
}

//(0231) Is the given number is of the power of 2 (hits:2)
//alternative method return ((n&(n-1))==0)&&(n!=0))
bool isPowerOfTwo(int n) {
    if (n <= 0) return 0;
    return (n & (n-1)) == 0;
}

//(0342) power of four
// (a x b) (mod m) = ((a (mod m)) x (b (mod m))) (mod m)
bool isPowerOfFour(int n) {
    if (n <= 0) return false;
    return ((n & (n-1)) == 0) && (n % 3 == 1);
}
   
#define setmask1(B, A) ((1<<(B-A+1))-1)<<A
#define setmask2(B, A) ((1<<B)-1)&(~((1<<A)-1))
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
unsigned int reverseBits(unsigned int num){
    unsigned int count = sizeof(num) * 8 - 1;
    unsigned int reverse_num = num;
     
    num >>= 1; 
    while(num){
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

// alternate big / small endian
#define SWAP_INT32(x) ((((x) >> 24) & 0xFF) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | ((x) << 24))

//swap the neighboring bits. 
//   $$$$$$$$$ never right shift mask like this, the 1 at highest bit will be kept. $$$$$$$$$$
// define another mask2 = 0x55555555
unsigned int swapneighborBits(unsigned int a){
    unsigned int mask = 0xaaaaaaaa;
    unsigned int num1 = a & mask;
    unsigned int num2 = a & (mask >> 1);
    num1 >>= 1;
    num2 <<= 1;
    return num1 | num2;
}

// find out msb: floor(log2(number)) (hits:3) (log2(x)=log(x)/log(2)) (<math.h>)
int numberMsb(int n) { 
    int msb = 0; 
    n = n / 2; 
    while (n != 0) { 
        n = n / 2; 
        msb++; 
    } 
    return msb; 
} 

//Find the Maximum of 2 numbers without using any if-else or any other comparison operator
int maximum(int a, int b){
    int k = ((a-b)&0x8000000)>>31;
	// int k = ((a-b) >> 31) & 1;
    return (1-k)*a+k*b;
}

//function to give mask for first 2 non zero (anything except 00) values in int.
int mask2nz(int a){
    int L = 8*sizeof(int);
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

//(0201) bitwise AND of numbers range
// only the highest NO zero bits left
int rangeBitwiseAnd(int m, int n) {
    int trans = 0;
    while (m != n) {
        ++ trans;
        m >>= 1;
        n >>= 1;
    }
    return m << trans;
}

//binary print
// Define a union to access the float's bit pattern
typedef union {
    float f;
    unsigned int u;
} FloatUnion;

int main() {
    float myFloat = 12.345f;
    FloatUnion fu;
    fu.f = myFloat; // Assign the float value

    // or this works too
    // memcpy(&u, &myFloat, sizeof(float));

    printf("Binary representation of %.3f: ", myFloat);
    for (int i = 31; i >= 0; i--) {
        printf("%d", (fu.u >> i) & 1);
        if (i == 31 || i == 23) { // Add spaces for sign, exponent, and mantissa
            printf(" ");
        }
    }
    printf("\n");

    return 0;
}

// find a defect data pin
// The Logic: Walking 1s and 0s
#include <stdio.h>
#include <stdint.h>

void find_defective_pins(volatile uint8_t *address) {
    uint8_t pattern;
    uint8_t read_back;
    int pin_found = 0;

    printf("Starting Memory Data Bus Test...\n");
    printf("---------------------------------\n");

    // Test for 'Stuck-at-High' (Walking 0s)
    // We write 0 to each pin and see if it stays 0
    for (int i = 0; i < 8; i++) {
        pattern = ~(1 << i);
        *address = pattern;
        read_back = *address;

        if (read_back != pattern) {
            printf("FAULT: Pin %d is stuck HIGH (Expected %02X, Got %02X)\n", i, pattern, read_back);
            pin_found = 1;
        }
    }

    // Test for 'Stuck-at-Low' (Walking 1s)
    // We write 1 to each pin and see if it stays 1
    for (int i = 0; i < 8; i++) {
        pattern = (1 << i);
        *address = pattern;
        read_back = *address;

        if (read_back != pattern) {
            printf("FAULT: Pin %d is stuck LOW (Expected %02X, Got %02X)\n", i, pattern, read_back);
            pin_found = 1;
        }
    }

    if (!pin_found) {
        printf("All data pins are functioning correctly.\n");
    }
}

int main() {
    // In a real system, this would be a hardware address:
    // uint8_t *mem_ptr = (uint8_t *)0x40001000;

    uint8_t dummy_mem = 0;

    // Simulate a fault for demonstration: Pin 3 is stuck LOW
    // In real hardware, the read_back would fail automatically.
    find_defective_pins(&dummy_mem);

    return 0;
}

//Short Circuits: If two pins are shorted together, writing a 1 to one might cause the other to also read as 1. You can detect this by writing 0x00 and then 0x01, 0x02, etc., and checking if multiple bits flip simultaneously.

//Volatile Keyword: In the code above, volatile is crucial. It tells the C compiler not to optimize away the memory access, ensuring the CPU actually hits the hardware every time.

// find a defect address line
// The Logic: Power-of-Two Testing
#include <stdio.h>
#include <stdint.h>

/**
 * Checks for defective address pins within a range of memory.
 * @param base_addr The starting address of the memory block to test.
 * @param n_bytes   The size of the memory block (should be a power of 2).
 */
void find_defective_address_pins(volatile uint32_t *base_addr, uint32_t n_bytes) {
    uint32_t n_words = n_bytes / sizeof(uint32_t);
    uint32_t offset;
    uint32_t test_pattern = 0xAAAAAAAA;
    uint32_t initial_pattern = 0x55555555;

    printf("Starting Address Bus Test...\n");
    printf("-----------------------------\n");

    // 1. Initialize the base address with a pattern
    base_addr[0] = initial_pattern;

    // 2. Write unique patterns to each power-of-two offset
    // This checks if any pin is "Stuck High" or "Shorting"
    for (offset = 1; offset < n_words; offset <<= 1) {
        base_addr[offset] = test_pattern;
    }

    // 3. Check the base address to see if it was overwritten
    if (base_addr[0] != initial_pattern) {
        printf("FAULT: Address pin 0 or a related control line is defective.\n");
    }

    // 4. Check each power-of-two offset
    // If a pin is "Stuck Low", the write to base_addr[offset]
    // would have gone to base_addr[0] instead.
    for (offset = 1; offset < n_words; offset <<= 1) {
        if (base_addr[offset] != test_pattern) {
            // Log2 of offset gives the pin number
            int pin = 0;
            uint32_t temp = offset;
            while (temp >>= 1) pin++;

            printf("FAULT: Address Pin A%d is likely defective (Stuck Low or Shorted).\n", pin);
        }
    }

    printf("Test Complete.\n");
}

int main() {
    // Example: Testing a 4KB block of memory starting at a specific pointer
    // In a real embedded system, this might be:
    // uint32_t *mem_start = (uint32_t *)0x20000000;

    uint32_t simulated_memory[1024]; // 4KB of local RAM for simulation
    find_defective_address_pins(simulated_memory, sizeof(simulated_memory));

    return 0;
}

// Destructive Test: This test is "destructive"—it overwrites whatever was in memory. Do not run this on memory containing your active stack or program code.
