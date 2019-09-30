    //use long for pre and cur to prevent integer overflow
    
    void addOPTool(string & num, int p, int target, long pre, long cur, string & path, int l, vector<string>&ans){
        if(p==num.size()&&cur==target){
            ans.push_back(path.substr(0,l));return;
        }
        long x = 0;
        int q = l;
        if(p!=0)q++;
        for(int i=p; i<num.size(); i++){
            x = x*10+(long)(num[i]-'0');
            path[q++]=num[i];
            if(p==0){
                addOPTool(num,i+1,target,x,cur+x,path,q,ans);
            }else{
                path[l]='+'; addOPTool(num,i+1,target, x, cur+x, path, q, ans);
                path[l]='-'; addOPTool(num,i+1,target, -x, cur-x, path, q, ans);
                path[l]='*'; addOPTool(num,i+1,target, pre*x, cur-pre+pre*x, path, q, ans);
            }
    // if the first digit is 0, we do not grow from it. 
            if(num[p]=='0')break;
        }
    }
    vector<string> addOperators(string num, int target) {
        vector<string>ans;
        string path(num.size()*2,' ');
        addOPTool(num,0,target,0,0,path,0,ans);
        return ans;
    }
