/* reverse integer [2] : (0007) reverse integer (0009) palindrome number
 * add integers [3] : (0067) add binary (0066) Plus One (0371) add integers
 * divide integers [1] :  (0027) divide two integers
 * multiply strings [1] : (0043) multiply strings
 * power of double [1] : (0050) power of double float
 * roman [2] : (0012) integer to Roman (0013) Roman to Integer
 * single number [2] : (0136) single number (0137) single number ii
 * bezout's identity [1] : (0365) the water jug problem
 */

// (0009) palindrome number
bool isPalindrome(int x) {
    if(x<0)return 0;
    int y=0;
    int tmp=x;
    while(tmp>0){
        int digit=tmp%10;
        y*=10;
        y+=digit;
        tmp/=10;
    }
    if(x==y)return 1;
    else return 0;
}
// (0007) reverse integer
    int reverse(int x) {
        long long val = 0;
	      do {
		        val = val * 10 + x % 10;
		        x /= 10;
	      } while (x);
	
	      return (val > INT_MAX || val < INT_MIN) ? 0 : val;
    }

// (0066) Plus One
vector<int> plusOne(vector<int>& digits) {
    int n = digits.size();
    for (int i = n - 1; i >= 0; --i){
        if (digits[i] == 9){
            digits[i] = 0;
        }else{
            digits[i]++;
            return digits;
        }
    }
    digits[0] =1;
    digits.push_back(0);
    return digits;
}
// (0067) add binary
    string addBinary(string a, string b) {
        int sza = a.size();
        int szb = b.size();
        string ss = string(max(sza,szb),'0');
        int i=sza-1; int j=szb-1; int p=max(i,j);
        int c = 0;
        while(i>=0 || j>=0){
            int x = 0;
            if(i>=0)x=a[i]-'0';
            int y = 0;
            if(j>=0)y=b[j]-'0';
            ss[p--]=(x+y+c)%2+'0';
            c = (x+y+c)/2;
            i--;j--;
        }
        if(c>0)ss.insert(0,string(1,c+'0'));
        return ss;
    }
// (0371) add integers
    int getSum(int a, int b) {
        return b==0?a:getSum(a^b,((unsigned)(a&b))<<1);
    }
    
// (0027) divide two integers
    int divide(int dividend, int divisor) {
        if (dividend == INT_MIN && divisor == -1) {
            return INT_MAX;
        }
        long dvd = labs(dividend), dvs = labs(divisor), ans = 0;
        int sign = dividend > 0 ^ divisor > 0 ? -1 : 1;
        while (dvd >= dvs) {
            long temp = dvs, m = 1;
            while (temp << 1 <= dvd) {
                temp <<= 1;
                m <<= 1;
            }
            dvd -= temp;
            ans += m;
        }
        return sign * ans;
    }
    
// (0043) multiply strings
    string multiply(string num1, string num2) {
        int n = num1.size(); 
        int m = num2.size();
        string sum(n+m, '0');
    
        for (int i = n - 1; 0 <= i; --i) {
            int carry = 0;
            for (int j = m - 1; 0 <= j; --j) {
                int tmp = (sum[i+j+1] - '0') + (num1[i] - '0') * (num2[j] - '0') + carry;
                sum[i+j+1] = tmp % 10 + '0';
                carry = tmp / 10;
            }
            sum[i] += carry;
        }
        int p=0;
        while(p<n+m && sum[p]=='0')p++;
        if(p!=n+m)return sum.substr(p);
        else return "0";
    }

// (0050) power of double float
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

// (0012) integer to Roman
    string intToRoman(int num) {
        string res;
        vector<string>sym = vector<string>({"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"});
        vector<int>val = vector<int>({1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1});
        for(int i=0; num != 0; i++){
            while(num >= val[i]){
                num -= val[i];
                res += sym[i];
            }
        }
        return res;
    }
// (0013) Roman to Integer
    int romanToInt(string s) {
        unordered_map<char, int> T = { { 'I' , 1 }, { 'V' , 5 }, { 'X' , 10 }, { 'L' , 50 }, { 'C' , 100 }, { 'D' , 500 }, { 'M' , 1000 } };
                                   
       int sum = T[s.back()];
       for (int i = s.length() - 2; i >= 0; --i) {
           if (T[s[i]] < T[s[i + 1]]){
               sum -= T[s[i]];
           }else{
               sum += T[s[i]];
           }
       }
   
       return sum;        
    }


// (0136) single number
    int singleNumber(vector<int>& nums) {
        int x = 0;
        for(auto y:nums)x^=y;
        return x;
    }
// (0137) single number II
    int singleNumber(vector<int> A) {
        int ones = 0, twos = 0;
        for(int i = 0; i < A.size; i++){
            ones = (ones ^ A[i]) & ~twos;
            twos = (twos ^ A[i]) & ~ones;
        }
        return ones;
    }

// (0365) the water jug problem
    int gcd(int x, int y){
        while(y!=0){
            int r = x%y;
            x=y;
            y=r;
        }
        return x;
    }
    bool canMeasureWater(int x, int y, int z) {
        if(z==0)return true;
        if(z-x>y)return false;
        return z%gcd(x,y)==0;
    }
    
