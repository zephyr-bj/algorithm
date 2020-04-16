    // calculate hash value manually
    
    // (unordered_set) Container elements may not be modified (even by non const iterators) 
    // since modification could change an element's hash and corrupt the container.
    // - they can be inserted and removed, though.
    
    // use (bin[h]==2) to check repeated sequence, and avoid push same sequence. 
    
    vector<string> findRepeatedDnaSequences(string s) {
        unordered_map<int, int>bin;
        int n = s.size();
        int mask = (1 << 27)-1;
        int h=0;
        for(int i=0; i<9; i++){
            h = ((h&mask)<<3) | (s[i]&7); 
        }
        vector<string>ans;
        for(int i=9; i<n; i++){
            h = ((h&mask)<<3) | (s[i]&7);
            if(bin.find(h)!=bin.end())bin[h]+=1;
            else bin[h]=1;
            if(bin[h]==2)ans.push_back(s.substr(i-9,10));
        }
        return ans;
    }

    vector<string> findRepeatedDnaSequences(string s) {
        int n = s.size();
        unordered_map<string, int>bin;
        vector<string>ans;
        for(int i=0; i<n-9; i++){
            string x = s.substr(i,10);
            if(bin.find(x)==bin.end()){
                bin[x]=1;
            }else{
                bin[x]+=1;
            }
            if(bin[x]==2)ans.push_back(x);
        }
        return ans;
    }
