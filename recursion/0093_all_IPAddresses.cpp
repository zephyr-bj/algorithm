class Solution {
private:
    void getIP(string s, int p, vector<string>&jar, string & candy){
        if(p==s.size() && s.size()+3 == candy.size()){
            jar.push_back(candy);return;
        }
        int l = candy.size();
        for(int i=0; i<3 && p+i<s.size(); i++){
            string sub = s.substr(p,i+1);
            int x = stoi(sub);
            if(i==0 || i==1 && x>9 && x<100 || i==2 && x>99 && x<256){
                if(!candy.empty())candy+=".";
                candy+=sub;
                getIP(s,p+i+1,jar,candy);
                candy.erase(l);
            }
        }
    }
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string>jar;
        if(s.size()>12)return jar;
        string candy;
        getIP(s,0,jar,candy);
        return jar;
    }
};
