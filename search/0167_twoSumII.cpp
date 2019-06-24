    vector<int> twoSum(vector<int>& numbers, int target) {
        int L = numbers.size();
        int x=0; int y=L-1;
        vector<int>ans(2,0);
        while(x<y){
            if(numbers[x]+numbers[y]==target){
                ans[0]=x+1;
                ans[1]=y+1;
                return ans;
            }else if(numbers[x]+numbers[y]<target){
                x++;
            }else{
                y--;
            }
        }
        return ans;
    }
