    int minCut(string s) {
        int n=s.size();
        if(n<2)return 0;
        vector<vector<bool>>plindr(n,vector<bool>(n,0));
        vector<int>bin(1,-1);//element before 0, -1
        int ans=n-1;
        for(int i=0; i<n; i++){
            int cut=i;
             for(int j=0; j<=i; j++){
                if(j==i||(s[j]==s[i]&&(j+1==i||plindr[j+1][i-1]))){
                    plindr[j][i]=1;
                    if(cut>bin[j]+1)cut=bin[j]+1;
                }
            }
            bin.push_back(cut);
        }
        return bin.back();
    }
    /*
    at first, I use a two step method as below, but actually we can do it within shot, use two vairables
        int minCut(string s) {
        int n=s.size();
        if(n<2)return 0;
        vector<bool>tmp(n,0);
        vector<vector<bool>>plindr(n,tmp);
        for(int i=0; i<n; i++)plindr[i][i]=1;
        for(int i=0; i<n-1; i++)plindr[i][i+1]=(s[i]==s[i+1]);
        for(int L=3; L<=n; L++){
            for(int i=0; i+L<=n; i++){
                plindr[i][i+L-1]=(plindr[i+1][i+L-2])&&(s[i]==s[i+L-1]);
            }
        }
        vector<int>bin(1,-1);//element before 0, -1
        bin.push_back(0);    //with only one element, 0 cut
        int ans=n-1;
        for(int i=1; i<n; i++){
            int cut=i;
            for(int j=0; j<=i; j++){
                if(plindr[j][i]){
                    if(cut>bin[j]+1)cut=bin[j]+1;
                }
            }
            bin.push_back(cut);
        }
        return bin.back();
    }
    */
