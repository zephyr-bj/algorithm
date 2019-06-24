    int peakFindUtil(vector<int>&arr, int x, int y, int n){
        int mid = (x+y)/2;
        if(mid>0&&arr[mid]>arr[mid-1]&&mid<n-1&&arr[mid]>arr[mid+1])return mid;
        else if(mid>0&&arr[mid]<arr[mid-1])return peakFindUtil(arr, x, mid-1, n);
        else return peakFindUtil(arr, mid+1, y, n);
    }
    int peakIndexInMountainArray(vector<int>& A) {
        int n = A.size();
        return peakFindUtil(A,0,n-1,n);
    }
