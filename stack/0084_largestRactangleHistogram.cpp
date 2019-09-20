    int largestRectangleArea(vector<int>& heights) {
        stack<int>bin;
        bin.push(-1);                   // keep a left limit
        heights.push_back(0);           // add a check point at the end
        int n = heights.size();
        int ans = 0;
        for(int i=0; i<n; i++){         // i iterates the righ limit
            while(bin.size()>1&&heights[bin.top()]>heights[i]){
                int idx = bin.top();
                bin.pop();
                int area = heights[idx]*(i-bin.top()-1);
                ans=max(ans,area);
            }
            bin.push(i);
        }
        return ans;
    }
