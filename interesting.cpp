//Find number of friday 13th's from today to the end of 2012.

#include <stdlib.h>
#include <stdio.h>

// find the Fridays on 13th. 
// inplace merge
// hex print
// sqrt(x) with Newton's iterative method

int main(void)
{
 /* days in months for 2012 year */
	int days[12]=
	{
	31,29,
	31,30,
	31,30,
	31,31,
	30,31,
	30,31
	};
 
	int i;/*month: 0,1,...11;*/
	int j;/*day of month: 0,1..;*/
  
	int day_of_week = 0;/*Sunday, Jan 1st, 2012*/    
	for(i = 0; i < 12; i++){
		for(j = 0; j < days[i]; j++){     
			day_of_week = day_of_week %7;
			if(day_of_week == 5  //Fri
					&& j == 12)//13th
			{
				printf("2012/%02d/%02d\n",i+1,j+1);
			}
			day_of_week++;
		}
	}
	return(0);
}

// inplace merging
void inplaceMerge(int * arr1, int * arr2)
{
	int L1 = sizeof(arr1)/sizeof(arr1[0]);
	int L2 = sizeof(arr1)/sizeof(arr1[0]);
	for(int i=0;i<L1;i++) { 
		if(arr1[i]>arr2[0]) { 
			int tmp = arr2[0];
			arr2[0] = arr1[i];
			arr1[i] = tmp;
			for(int j=0;j<L2-1;j++){ 
				if(arr2[j]>arr2[j+1]){ 
					int tmp = arr2[j];
					arr2[j] = arr2[j+1];
					arr2[j+1] = tmp;
				}
				else break; 
			} 
		}
	}
}

//Write an printhex function which implements "%x" in printf without using printf. Example :- printhex(10) output is A . (hits:2)
void hex(int num){ 
	int rem; 
	if(!num) 
		return; 
	hex(num/16) ; 
	rem=num%16; 
	printf("%c",(rem<10)? '0'+rem :('A'+rem-10)); 
	return; 
}

char table[16] = { '0', '1', '2','3','4','5','6','7','8','9','A','B','C','D', 'E','F' };
void printhex(int input)
{  
     int index = input%16;
     input/=16;
     if(input) printhex(input);
     putchar(table[index]);
}

// 13. implement sqrt(x) // Newton's iterative method  x_n+1 = x_n - f(x_n)/f'(x_n);
float SquareRoot(float num) { 
    if(num >= 0) { 
		float x = num; 
		int i; 
		for(i = 0; i < 20; i ++) { 
			x = (((x * x) + num) / (2 * x)); 
		} 
		return x; 
    } 
}

// 3. running average of an array with N elements.
//



//count the number of lines in a big file

//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <ctime>
using namespace std;

unsigned int FileRead( istream & is, vector <char> & buff ) {
    is.read( &buff[0], buff.size() );
    return is.gcount();
}

unsigned int CountLines( const vector <char> & buff, int sz ) {
    int newlines = 0;
    const char * p = &buff[0];
    for ( int i = 0; i < sz; i++ ) {
    	if ( p[i] == '\n' ) {
    		newlines++;
    	}
    }
    return newlines;
}

int main( int argc, char * argv[] ) {
    time_t now = time(0);
    if ( argc == 1  ) {
    	cout << "lines\n";
    	ifstream ifs( "lines.dat" );
    	int n = 0;
    	string s;
    	while( getline( ifs, s ) ) {
    		n++;
    	}
    	cout << n << endl;
		 }
    else {
    	cout << "buffer\n";
    	const int SZ = 1024 * 1024;
    	std::vector <char> buff( SZ );
    	ifstream ifs( "lines.dat" );
    	int n = 0;
    	while( int cc = FileRead( ifs, buff ) ) {
    		n += CountLines( buff, cc );
    	}
    	cout << n << endl;
    }
    cout << time(0) - now << endl;
}

//get rand7 by rand5
int rand7() //random number from 1 - 7
{
    int r = 0;
    do
    {
       int a = rand(5) - 1; //uniformly at random from 0 to 4
       int b = rand(5) - 1;  //uniformly at random from 0 to 4
       r = 5*b + a;  //uniformly at random from 0 to 24
    }
    while (r >= 21); // in this event, we have to roll again
   //postcondition of loop: we have a number uniformly at random between 0 and 20

  return r % 7 + 1; 
  
  //there are 3 numbers in [0, 20] for each possible return value
  //so each has equal probability.
}

//search rotated array
int searchRotArr(int a[], int low, int high, int x){
    while(low <= high){
        int mid = low + (high - low)/2;
        if(a[mid] == x) return mid;
        if(a[mid] >= a[low]) {
            if(x<a[mid] && x>=a[low])
                high = mid - 1;
            else
                low = mid + 1;
        }
        else {
            if(x>a[mid] && x<a[low])
                low = mid + 1;
            else
                high = mid - 1;
        }
    }
    return -1;
}
//n-way merge