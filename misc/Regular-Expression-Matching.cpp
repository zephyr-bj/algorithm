#include "stdlib.h"

bool isMatch(const char *s, const char *p){
	if(s==NULL || p==NULL)return false;
	if(p[0]==0)return s[0]==0;
	if(p[1]=='*'){
		int j=0;
		while(p[0]==s[j] || (s[j]!=0 && p[0]=='.')){
			if(isMatch(s+j+1,p+2))return true;
			j++;
		}
		return isMatch(s,p+2);
	}
	else{
		if(p[0]==s[0] || (s[0]!=0 && p[0]=='.')){
			return isMatch(s+1,p+1);
		}
		else return false;
	}
}
