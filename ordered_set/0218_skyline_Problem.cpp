    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        multiset<pair<int,int>> s;
        // Nlog(N)
        for(auto& b:buildings){
            //so taller building will be at front when start points are same
            s.insert({b[0],-b[2]});
            //shorter building will be at front when ending points are same
            s.insert({b[1],b[2]});
        }
        multiset<int> sh ({0});
        vector<vector<int>> res;
        for(auto& p:s){
            // it is a start
            if(p.second<0){
                int height = -p.second;
                //use reverse begin, pointing at last element
                if(height > *sh.rbegin()){
                    res.push_back({p.first,height});
                }
                sh.insert(height);
            }else{
                //it is the end
                int max = *sh.rbegin();
                sh.erase(sh.find(p.second));
                // when deleted the max, ...
                if(max != *sh.rbegin()){
                    res.push_back({p.first, *sh.rbegin()});
                }
                // cout<<max<<"    "<<*sh.rbegin()<<endl;
            }
            //cout<<res.size()<<endl;
        }
        return res;
    }
