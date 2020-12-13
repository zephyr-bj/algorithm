#include <bits/stdc++.h> 
using namespace std; 
  
// Function to print intersecting intervals 
void printIntervals(vector<vector<int> > arr1, 
                    vector<vector<int> > arr2) 
{ 
  
    // i and j pointers for 
    // arr1 and arr2 respectively 
    int i = 0, j = 0; 
  
    // Size of the two lists 
    int n = arr1.size(), m = arr2.size(); 
  
    // Loop through all intervals unless 
    // one of the interval gets exhausted     
    while (i < n && j < m) { 
        // Left bound for intersecting segment 
        int l = max(arr1[i][0], arr2[j][0]); 
  
        // Right bound for intersecting segment 
        int r = min(arr1[i][1], arr2[j][1]); 
  
        // If segment is valid print it 
        if (l <= r) 
            cout << "{" << l << ", "
                 << r << "}\n"; 
  
        // If i-th interval's right 
        // bound is smaller 
        // increment i else 
        // increment j 
        if (arr1[i][1] < arr2[j][1]) 
            i++; 
        else
            j++; 
    } 
} 
  
// Driver code 
int main() 
{ 
  
    vector<vector<int> > arr1 
        = { { 0, 4 }, { 5, 10 }, 
            { 13, 20 }, { 24, 25 } }; 
  
    vector<vector<int> > arr2 
        = { { 1, 5 }, { 8, 12 }, 
            { 15, 24 }, { 25, 26 } }; 
  
    printIntervals(arr1, arr2); 
  
    return 0; 
} 
