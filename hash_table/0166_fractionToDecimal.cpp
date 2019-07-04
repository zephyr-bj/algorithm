    // calculator
    // 
    string fractionToDecimal(int numerator, int denominator) {
        if(numerator==0)return "0";
        string ans = numerator>0 ^ denominator>0 ? "-":"";
        long numerator1 = abs(long(numerator)); long denominator1 = abs(long(denominator));
        ans += to_string(numerator1/denominator1);
        long x = numerator1%denominator1;
        if(x==0)return ans;
        ans+=".";
        unordered_map<long,int>bin;
        bin[x]=0; 
        int repeat=-1;
        string fract;
        x*=10;bin[x]=0;
        while(x!=0){
            if(x<denominator1){
                fract+="0";
            }else{
                fract+=to_string(x/denominator1);
                x = x%denominator1;
                if(bin.find(x)!=bin.end()){
                    repeat=bin[x];break;
                }
            }
            bin[x] =fract.size();
            x*=10;
        }
        if(repeat!=-1){
            fract.insert(repeat,"(");
            fract.insert(fract.size(),")");
        }
        ans+=fract;
        return ans;
    }
