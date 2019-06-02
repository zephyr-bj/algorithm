    bool isValidSerialization(string preorder) {
        vector<int>bin;
        int n = preorder.size();
        int j = 0; 
        for(int i=0; i<=n; i++){
            if(preorder[i]==','||i==n){
                string s = preorder.substr(j, i-j);
                if(j==0){
                    if(s.compare("#")==0){
                        if(i==n)return true;
                        else return false;
                    }else{
                        bin.push_back(2);
                    }
                }else{
                    if(bin.empty())return false;
                    
                    if(bin.back()==2) bin.back()-=1;
                    else if(bin.back()==1) bin.pop_back();
                    else return false;
                    
                    if(s.compare("#")!=0)bin.push_back(2);
                }
                j=i+1;
            }
        }
        return bin.empty();
    }
    /*
    //another way without a stack
        bool isValidSerialization(string preorder) {
        int cnt=1;
        int n = preorder.size();
        int j = 0; 
        for(int i=0; cnt>0&&i<=n; i++){
            if(preorder[i]==','||i==n){
                string s = preorder.substr(j, i-j);
                if(s.compare("#")==0){
                    cnt--;
                }else{
                    cnt++;
                }
                j=i+1;
            }
        }
        return cnt==0&&j==n+1;
    }
    */
