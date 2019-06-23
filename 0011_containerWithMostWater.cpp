    int maxArea(vector<int>& height) {
        int L = height.size();
        int i=0; int j=L-1;
        int m=0;
        while(i<j){
            int h = height[i]<height[j]?height[i]:height[j];
            int c = h*(j-i);
            m = c>m?c:m;
            if(height[i]<height[j])i++;
            else j--;
        }
        return m;
    }
