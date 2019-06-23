vector<vector<int> > threeSum(vector<int> &num){
	  sort(num.begin(), num.end());
	  vector<vector<int>>ans;
	  int target = 0;
	  int n = num.size();
	  for(int i=0; i<n; i++){
		    int t2 = target-num[i];
		    int x = i+1; int y = n-1;
		    while(x<y){
			      if(num[x]+num[y]<t2){
				        x++;
			      }else if(num[x]+num[y]>t2){
			          y--;
			      }else{
			          vector<int>cmb(3,num[i]);
				        cmb[1]=num[x]; cmb[2]=num[y];
				        ans.push_back(cmb);
				        while (x < y && num[x] == cmb[1]) x++;
				        while (x < y && num[y] == cmb[2]) y--;
			      }
		    }
		    while (i + 1 < num.size() && num[i+1] == num[i]) i++;
	  }
	  return ans;
}
