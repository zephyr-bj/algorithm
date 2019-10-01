    void parentheseTool(int n, int left, int right, vector<string>&ans, string &path){
        if(path.size()==n*2){
            ans.push_back(path);return;
        }
        if(left>0){
            path.push_back('(');
            parentheseTool(n,left-1,right,ans,path);
            path.pop_back();
        }
        if(right>left){
            path.push_back(')');
            parentheseTool(n,left,right-1,ans,path);
            path.pop_back();
        }
    }
    vector<string> generateParenthesis(int n) {
        vector<string>ans;
        string path;
        parentheseTool(n,n,n,ans,path);
        return ans;
    }
