    // skip the 0 case, no different numbers generates from a start of "0"
    void IPTool(int k, int n, string &s, int p, string&ip, vector<string>&ans){
        if(k==n){
            ans.push_back(ip);return;
        }
        for(int i=1; i<=3; i++){
            if(p+i>s.size())break;
            string seg=s.substr(p,i);
            int segN = atoi(seg.c_str());
            int leftc = s.size()-p-i;
            if(segN>=0&&segN<=255&&leftc>=n-k-1&&leftc<=(n-k-1)*3){
                int Lip = ip.size();
                int L = i;
                if(!ip.empty()){
                    ip+="."; L+=1;
                }
                ip+=seg;
                IPTool(k+1,n,s,p+i,ip,ans);
                ip.erase(Lip,L);
            }
            if(s[p]=='0')break;
        }
    }
    vector<string> restoreIpAddresses(string s) {
        vector<string>ans;
        string ip;
        IPTool(0,4,s,0,ip,ans);
        return ans;
    }
