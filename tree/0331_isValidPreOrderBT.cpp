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
    //actually do not need a real stack
    bool isValidSerialization(string preorder) {
        int x = 0;
        int stk=1;
        for(int y=0; y<=preorder.size(); y++){
            if(preorder[y]==','||y==preorder.size()){
                string s = preorder.substr(x,y-x);
                stk--;
                if(stk<0)return false;
                if(s.compare("#")!=0)stk+=2;
                x=y+1;
            }
        }
        return stk==0;
    }
    */
