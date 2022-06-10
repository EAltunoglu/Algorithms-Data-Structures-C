#include<bits/stdc++.h>
#define pb push_back
using namespace std;
typedef pair<int,int> ii;

const int maxn = 1e5 + 10;
int N,M,X;
vector <ii> edge[maxn];

struct node{
	int minpos,minval,updval,isout;
	//node(){}
	node(int _minpos=-1, int _minval=INT_MAX, int _updval=-1, int _isout=1){
		minpos = _minpos; minval = _minval; updval = _updval; isout = _isout;
	}
	friend node merge(const node &a, const node &b){
		if(a.isout and b.isout)
			return node();
		if(a.minval < b.minval and a.isout){
			printf("ASDDSAASDDAS %d %d %d %d\n",a.minval,b.minval,a.isout,b.isout);
		}
		if(a.minval < b.minval) return a;
		return b;
	}
}seg[maxn<<2];

void random_input(){
	N = rand() % maxn + 1;
	M = rand() % (maxn * (maxn-1) / 2);
}

void get_input(){
	scanf("%d%d%d",&N,&M,&X);
	for(int i = 0,a,b,c; i < M; i++){
		scanf("%d%d%d",&a,&b,&c);
		edge[a].pb(ii(b,c));
		edge[b].pb(ii(a,c));
	}
}

void push(int k, int l, int r){
	if(seg[k].isout) return;
	
	if(seg[k].updval != -1){
		seg[k].minval = min(seg[k].minval, seg[k].updval);
	//	if(l == r) puts("QQQQQQQQQQQQQQQQQQQQQQQ");
		if(seg[k+k].updval == -1)	seg[k+k].updval = seg[k].updval;
		else 						seg[k+k].updval = min(seg[k+k].updval , seg[k].updval);
		
		if(seg[k+k+1].updval == -1)	seg[k+k+1].updval = seg[k].updval;
		else 						seg[k+k+1].updval = min(seg[k+k+1].updval , seg[k].updval);
	
		seg[k].updval = -1;
	}
	if(l != r)	seg[k].isout = seg[k+k].isout & seg[k+k+1].isout;
}

node seg_upd(int k, int l, int r, int x, int y, int val){
	push(k, l, r);
	if(l > y or r < x) return seg[k];
	if(l >= x and r <= y){
		seg[k].updval = val;
		push(k, l, r);
		return seg[k];
	}
	int m = (l + r) >> 1;
	return seg[k] = merge(seg_upd(k+k, l, m, x, y, val), seg_upd(k+k+1, m+1, r, x, y, val));
}

node seg_out(int k, int l, int r, int x){
	push(k, l, r);
	if(l > x or r < x) return seg[k];
	if(l == x and r == x)
		return seg[k] = node();
	int m = (l + r) >> 1;
	return seg[k] = merge(seg_out(k+k, l, m, x), seg_out(k+k+1, m+1, r, x));
}

void init(int k, int l, int r){
	seg[k].minval = INT_MAX;
	seg[k].isout = 0;
	seg[k].minpos = l;
	seg[k].updval = -1;
	if(l == 1) seg[k].minval = 0;
	if(l == r){
		return;
	}
	int m = (l + r) >> 1;
	init(k+k, l, m);
	init(k+k+1, m+1, r);
}

void debugg(int cur, int x, int y, int val){
	printf("+++ %d %d %d %d\n",cur,x,y,val);
}

int solve1(){
	for(int i = 1; i <= N; i++){
		edge[i].pb(ii(i, 1e9));
		sort(edge[i].begin(), edge[i].end());
	}
	
	init(1, 1, N);

	for(int i = 0, cur, we; i < N; i++){
		cur = seg[1].minpos;
		we = seg[1].minval;
		printf("--- %d %d %d\n",i,cur,we);
		if(cur == N) return seg[1].minval;
		
		int b = 1;
		for(int j = 0; j < (int)edge[cur].size() ; j++){
			int go = edge[cur][j].first;
			if(b < go)	debugg(cur,b,go-1,we+X),seg_upd(1, 1, N, b, go-1, we + X);
			debugg(cur,go,go,we+edge[cur][j].second),seg_upd(1, 1, N, go, go, we + edge[cur][j].second);
			b = go + 1;
		}
		
		if(edge[cur].back().first < N)
			debugg(cur,edge[cur].back().first,N,we+X),seg_upd(1, 1, N, edge[cur].back().first+1, N, we + X);
		
		seg_out(1, 1, N, cur);
	}
	puts("WFWFWFWFW");
	return -1;
}

int solve2(){
	return -1;
}

int main(){
	get_input();
	int ans1 = solve1();
	int ans2 = solve2();
	printf("%d %d\n",ans1,ans2);
	return 0;
}/*
6 8 3
1 3 1
1 4 2
1 5 3
1 6 10
3 6 5
4 6 6
5 6 3
2 6 2
*/
