    string getHint(string secret, string guess) {
        vector<int>bin1(10,0);
        vector<int>bin2(10,0);
        int bull=0;
        int n = secret.size();
        for(int i=0; i<n; i++){
            bin1[secret[i]-'0']++;
            bin2[guess[i]-'0']++;
            if(secret[i]==guess[i])bull++;
        }
        int cow=0;
        for(int j=0; j<10; j++){
            cow+=min(bin1[j], bin2[j]);
        }
        cow-=bull;
        string ans=to_string(bull);
        ans+="A";
        ans+=to_string(cow);
        ans+="B";
        return ans;
    }
