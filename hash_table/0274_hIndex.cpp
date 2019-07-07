    int hIndex(vector<int>& citations) {
        unordered_map<int,int>bin;
        int n = citations.size();
        int t = 0;
        for(int i=0; i<n; i++){
            if(citations[i]>n)t++;
            if(bin.find(citations[i])!=bin.end())bin[citations[i]]++;
            else bin[citations[i]]=1;
        }
        for(int i=n; i>0; i--){
            if(bin.find(i)!=bin.end()){
                t+=bin[i];  
            }
            if(t>=i)return i;
        }
        return t;
    }
