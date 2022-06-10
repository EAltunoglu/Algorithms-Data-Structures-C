#include<bits/stdc++.h>

const int maxn = (1 << 17) + 20;

int n,m,ar[maxn],seg[maxn*4],range;

void init(int k, int l, int r, int depth){
	if(l == r){
		seg[k] = ar[l];
		return;
	}
	int m = (l + r) >> 1;
	init(k+k, l, m, depth - 1);
	init(k+k+1, m+1, r, depth - 1);
	
	if(depth & 1)	seg[k] = seg[k+k] | seg[k+k+1];
	else 			seg[k] = seg[k+k] ^ seg[k+k+1];

//	printf("%d %d %d %d %d\n",k,l,r,depth,seg[k]);
}

void update(int k, int l, int r, int x, int y, int depth){
	if(l > x or r < x) return;
	if(l == x and r == x){
		seg[k] = y;
		return;
	}
	
	int m = (l + r) >> 1;
	update(k+k, l, m, x, y, depth - 1);
	update(k+k+1, m+1, r, x, y, depth - 1);
	
	if(depth & 1)	seg[k] = seg[k+k] | seg[k+k+1];
	else 			seg[k] = seg[k+k] ^ seg[k+k+1];
}

int main(){
	
	scanf("%d%d",&n,&m);
	range = n;
	n = 1 << n;
	
	for(int i = 1; i <= n; i++)
		scanf("%d",&ar[i]);
	
	init(1, 1, n, range);
	
	for(int i = 0, x, y; i < m; i++){
		scanf("%d%d",&x,&y);
		update(1, 1, n, x, y, range);
		printf("%d\n",seg[1]);
	}
	
	return 0;
}
