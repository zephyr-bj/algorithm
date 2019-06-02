
/*DFS*/
class Solution {
public:
    bool tool(vector<string>& ans, unordered_map<string,map<string,int>>&bin, string src, int n){
        if(n==0)return true;
        unordered_map<string,map<string,int>>::iterator it = bin.find(src);
        if(it!=bin.end()){
            for(map<string,int>::iterator iit = it->second.begin(); iit!=it->second.end(); iit++){
                if(iit->second>0){
                    ans.push_back(iit->first);
                    iit->second-=1;
                    if(tool(ans,bin,iit->first,n-1))return true;
                    ans.pop_back();
                    iit->second+=1;
                }
            }
        }
        return false;
    }
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        unordered_map<string, map<string,int>>bin;
        int n = tickets.size();
        for(int i=0; i<n; i++){
            if(bin.find(tickets[i][0])==bin.end()){
                map<string,int>dst;
                dst[tickets[i][1]]=1;
                bin[tickets[i][0]]=dst;
            }else{
                if(bin[tickets[i][0]].find(tickets[i][1])==bin[tickets[i][0]].end()){
                    bin[tickets[i][0]][tickets[i][1]]=1;
                }else{
                    bin[tickets[i][0]][tickets[i][1]]+=1;
                }
            }
        }
        vector<string>ans(1,"JFK");
        tool(ans, bin, "JFK", n);
        return ans;
    }
};
