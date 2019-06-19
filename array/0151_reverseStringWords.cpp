    string reverseWords(string s) {
        int n = s.size();
        int i=0; 
        int l = n; 
        for(int j=0; j<n; j++){
            s[i]=s[j];
            if(s[j]==' '&&(j==0||s[j-1]==' '))l--;
            else i++;
        }
        if(s[l-1]==' ')l--;
        s.erase(l);
        
        int x=0; int y=l-1;
        while(x<y){
            swap(s[x],s[y]);
            x++;y--;
        }
        
        i=0;
        for(int j=0; j<=l; j++){
            if(s[j]==' '||j==l){
                int x = i; int y=j-1;
                while(x<y){
                    swap(s[x],s[y]);
                    x++;y--;
                }
                i=j+1;
            }
        }
        return s;
    }
