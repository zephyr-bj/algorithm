    int peakIndexInMountainArray(vector<int>& arr) {
        int a = 0; int b = arr.size()-1;
        while(a<b){
            int m = (a+b)/2;
            if(arr[m]>arr[m+1])b=m;
            else a=m+1;
        }
        return a;
    }
