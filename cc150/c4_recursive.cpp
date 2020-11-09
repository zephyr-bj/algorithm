#include <stdio.h>
#include <stack>
#include <vector>
#include <list>
#include <iostream>
using namespace std;

//print all permutations of a string
//power sets (recursive and non-recursive algorithms), 
//Print all possible combinations of r elements in a given array of size n 
//Print all possible combinations with a given sum of key words ??

//eight queens
//sum of coins
//paths in a matrix
//valid parentheses


//print all permutations of a string
void permute(char *a, int i, int n) 
{
	int j; 
	if(i == n){
		printf("%s\n", a);
	}
	else{
        for(j = i; j <= n; j++){
			char tmp;
			tmp = *(a+i); *(a+i)= *(a+j); *(a+j) = tmp;
			permute(a, i+1, n);
			tmp = *(a+i); *(a+i)= *(a+j); *(a+j) = tmp; //backtrack
		}
	}
} 
//Power set
typedef vector<vector<int> > vvi;
typedef vector<int> vi;
vvi get_subsets(int a[], int n){ //O(n2^n)
    vvi subsets;
    int max = 1<<n;
    for(int i=0; i<max; ++i){
        vi subset;
        int idx = 0;
        int j = i;
        while(j > 0){
            if(j&1){
                subset.push_back(a[idx]);
            }
            j >>= 1;
            ++idx;
        }
        subsets.push_back(subset);
    }
    return subsets;
}
vvi get_subsets1(int a[], int idx, int n){
    vvi subsets;
    if(idx == n){
        vi subset;
        subsets.push_back(subset); //empty set
    }
    else{
        vvi rsubsets = get_subsets1(a, idx+1, n);
        int v = a[idx];
        for(int i=0; i<rsubsets.size(); ++i){
            vi subset = rsubsets[i];
            subsets.push_back(subset);
            subset.push_back(v);
            subsets.push_back(subset);
        }
    }
    return subsets;
}
//prints all combinations of size r
void printCombination(int arr[], int n, int r)
{
    int *data = new int[r]; 
    combinationUtil(arr, data, 0, n-1, 0, r);
}
void combinationUtil(int arr[], int data[], int start, int end, int index, int r)
{
    if (index == r){
        for (int j=0; j<r; j++)
            printf("%d ", data[j]);
        printf("\n");
        return;
    }
    for (int i=start; i<=end && end-i+1 >= r-index; i++){
        data[index] = arr[i];
        combinationUtil(arr, data, i+1, end, index+1, r);
    }
}

//8 queens
int Qmap[8];int cnt=0;
void search(int r){
    if(r == 8){
        ++cnt;
        return;
    }
    for(int i=0; i<8; ++i){
        Qmap[r] = i;
        int ok = 1;
        for(int j=0; j<r; ++j)
            if(Qmap[r]==Qmap[j] || r-j==Qmap[r]-Qmap[j] || r-j==Qmap[j]-Qmap[r]){
                ok = 0;
                break;
            }
        if(ok) search(r+1);
    }
}


//sum of coins
int sum_n(int sum, int c, int n){
    int ways = 0;
    if(sum <= n){
        if(sum == n) return 1;
        if(c >= 25)
            ways += sum_n(sum+25, 25, n);
        if(c >= 10)
            ways += sum_n(sum+10, 10, n);
        if(c >= 5)
            ways += sum_n(sum+5, 5, n);
        if(c >= 1)
            ways += sum_n(sum+1, 1, n);
    }
    return ways;
}
std::list<int> comb;
int sumN2(int * superset, int L, int sum1, int c, int sum2){
	int ways = 0;
    if(sum1 >= sum2){
        if(sum1 == sum2) {
			//do something with comb;
			return 1;
		}
        return 0;
    }
    else{
		for(int i = L-1; i>=0; i--){
			if(c >= i){
				comb.push_back(superset[i]);
				ways += sumN2(superset,L,sum1+superset[i], i, sum2);
				comb.pop_back();
			}
		}
    }
	return ways;
}


//paths in a matrix
typedef struct point{
    int x, y;
}point;
stack<point> sp;
const int MAXN = 20;
int g[MAXN][MAXN];
point vp[MAXN+MAXN];
bool get_path(int m, int n){
    point p; p.x=n; p.y=m;
    sp.push(p);
    if(n==1 && m==1) return true;
    bool suc = false;
    if(m>1 && g[m-1][n])
        suc = get_path(m-1, n);
    if(!suc && n>1 && g[m][n-1])
        suc = get_path(m, n-1);
    if(!suc) sp.pop();          //back tracking
    return suc;
}

void print_paths(int m, int n, int M, int N, int len){
    if(g[m][n] == 0 || m>M || n>N) return;
    point p; p.x=n; p.y=m;
    vp[len++] = p;
    if(m == M && n == N){
        for(int i=0; i<len; ++i)
            cout<<"("<<vp[i].y<<", "<<vp[i].x<<")"<<" ";
        cout<<endl;
    }
    else{
        print_paths(m, n+1, M, N, len);
        print_paths(m+1, n, M, N, len);
    }
}

//valid parentheses
void print_pare(int l, int r, char str[], int cnt){//we know the length of the string before start, so set a c string with fixed length
    if(l<0 || r<l) return;
    if(l==0 && r==0){
        for(int i=0; i<cnt; ++i){
            cout<<str[i];
        }
        cout<<", ";
    }
    else{
        if(l > 0){
            str[cnt] = '(';
            print_pare(l-1, r, str, cnt+1);
        }
        if(r > l){
            str[cnt] = ')';
            print_pare(l, r-1, str, cnt+1);
        }
    }
}

