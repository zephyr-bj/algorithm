int numTrees(int n){
	if(n==0 || n==1)return 1;
	int sum = 0;
	for(int i=1; i<=n; i++){
		int left=1;
		if(i>=2)left = numTrees(i-1);
		int right = 1;
		if(n-i>=2)right = numTrees(n-i);
		sum += left*right;
	}
	return sum;
}
