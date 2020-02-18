// gready    
    string removeDuplicateLetters(string s) {
        vector<int> alphabetCount( 26, 0 );
        int index, pos = 0; 

        for( index = 0; index < s.length( ); index++ ){
            alphabetCount[ s[ index ] - 'a' ]++; 
        }
        for( index = 0; index < s.length( ); index++ ){
            if( s[ index ] < s[ pos ] )pos = index; 
            alphabetCount[ s[ index ] - 'a' ]--; 
            if( alphabetCount[ s[ index ] - 'a' ] == 0 )break;
        }
        
        if( s.empty( ) ){
            return "";
        }else{
            string buffer = s.substr( pos + 1 );
            buffer.erase( remove( buffer.begin( ), buffer.end( ), s[ pos ] ), buffer.end( ) );
            
            return s[ pos ] + removeDuplicateLetters( buffer );
        }
    }
// stack solution    
    string removeDuplicateLetters(string s) {
        vector<int> cand(256, 0);
        vector<bool> visited(256, false);
        for (char c : s)
            cand[c]++;
        string result = "0";
        for (char c : s) {
            cand[c]--;
            if (visited[c]) continue;
            while (c < result.back() && cand[result.back()]) {
                visited[result.back()] = false;
                result.pop_back();
            }
            result += c;
            visited[c] = true;
        }
        return result.substr(1);
    }
