// vector is good too, instead of a unordered_map
    int hIndex(vector<int>& citations) {
        int n = citations.size();
        vector<int>bin(n,0);
        int cnt=0;
        for(int i=0; i<n; i++){
            if(citations[i]>=n)cnt++;
            else bin[citations[i]]++;
        }
        int h = n;
        while(cnt<h){
            cnt+=bin[h-1];h--;
        }
        return h;
    }

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
