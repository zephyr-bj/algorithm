    string minWindow(string s, string t) {
        vector<int>tofind(256,0);
        vector<int>hasfound(256,0);
        int L = t.size();
        for(int i=0; i<L; i++)tofind[t[i]]++;
        int cnt=0;
        int left = 0;
        int n = s.size();
        int start = -1; int end =-1;
        for(int r=0; r<n; r++){
            hasfound[s[r]]++;
            if(hasfound[s[r]]<=tofind[s[r]])cnt++;
            if(cnt==L){
                int k = left;
                while(k<n&&hasfound[s[k]]>tofind[s[k]]){
                    hasfound[s[k]]--;
                    k++;
                }
                left=k;
                if(start==-1||end-start>r-k){
                    start=k; end=r;
                }
            }
        }
        return start==-1?"":s.substr(start,end-start+1);
    }
