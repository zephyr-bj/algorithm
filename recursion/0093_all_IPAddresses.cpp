    void ipTool(vector<string>&ans, string&ip, int n, int p){
        if(ip.size()==n+4){
            string s=ip.substr(0,ip.size()-1);
            ans.push_back(s);return;
        }
        for(int i=0; i<3&&p+i<ip.size(); i++){
            if(ip.size()==n+3&&p+i<n+2)continue;//if already inserted tree points
            int num = atoi(ip.substr(p,i+1).c_str());
            if((i==0)||(i==1&&num>9&&num<100)||(i==2&&num>99&&num<256)){
                ip.insert(p+i+1,".");
                ipTool(ans,ip,n,p+i+2);
                ip.erase(p+i+1,1);
            }
        }
    }
    vector<string> restoreIpAddresses(string s) {
        vector<string>ans;
        ipTool(ans,s,s.size(),0);
        return ans;
    }
