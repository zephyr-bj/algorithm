    bool isValidSerialization(string preorder) {
        stack<int>bin;
        bin.push(INT_MIN);
        int x = 0; int n = preorder.size();
        for(int y=0; y<=n; y++){
            if(y==n||preorder[y]==','){
                string str=preorder.substr(x,y-x);
                if(bin.empty())return false;
                bin.pop();
                if(str.compare("#")!=NULL){
                    bin.push(atoi(str.c_str()));
                    bin.push(atoi(str.c_str()));
                }
                x=y+1;
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
