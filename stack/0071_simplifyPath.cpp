    // parse the path
    // update j right after getting the substr
    
    string simplifyPath(string path) {
        list<string>que;
        int l = path.size();
        int j=0;
        for(int i=1; i<=l; i++){
            if(i==l||path[i]=='/'){
                string dir = path.substr(j+1, i-j-1);
                j=i;
                if(dir.size()==0)continue;
                else if(dir.compare(".")==0)continue;
                else if(dir.compare("..")==0){
                    if(!que.empty())que.pop_back();
                }else que.push_back(dir);
            }
        }
        string ans="/";
        while(!que.empty()){
            ans+=que.front();
            que.pop_front();
            if(!que.empty())ans+="/";
        }
        return ans;
    }
