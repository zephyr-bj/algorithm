    int largestRectangleArea(vector<int>& heights) {
        int L=heights.size();
        vector<int>bin;
        heights.push_back(0);
        int ans=0;
        int begin=0;
        for(int i=0; i<=L; i++){
            if(bin.empty()||heights[i]>=heights[bin.back()]){
                bin.push_back(i);
            }else{
                int tmp=bin.back();
                while(!bin.empty()&&heights[tmp]>heights[i]){
                    bin.pop_back();
                    int area=i*heights[tmp];
                    if(!bin.empty()) area=(i-bin.back()-1)*heights[tmp];
                    if(ans<area)ans=area;
                    if(!bin.empty())tmp=bin.back();
                }
                bin.push_back(i);
            }
        }
        return ans;
    }
