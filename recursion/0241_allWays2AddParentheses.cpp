    vector<int> diffWaysToCompute(string input) {
        int n = input.size();
        vector<int>ans;
        for(int i=0; i<n; i++){
            if(input[i]=='+'||input[i]=='-'||input[i]=='*'){
                vector<int>left=diffWaysToCompute(input.substr(0,i));
                vector<int>right=diffWaysToCompute(input.substr(i+1));
                for(int l=0; l<left.size(); l++){
                    for(int r=0; r<right.size(); r++){
                        if(input[i]=='+')ans.push_back(left[l]+right[r]);
                        if(input[i]=='-')ans.push_back(left[l]-right[r]);
                        if(input[i]=='*')ans.push_back(left[l]*right[r]);
                    }
                }
            }
        }
        if(ans.empty())ans.push_back(stoi(input));
        return ans;
    }
