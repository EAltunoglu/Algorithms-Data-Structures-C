#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cmath>
#include <climits>
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <cassert>
#include <vector>
#define all(x) x.begin() , x.end()
#define fi first
#define se second
#define pb push_back
#define umax( x , y ) x = max( x , (y) )
#define umin( x , y ) x = min( x , (y) )
#define For( i , a ) for(int i=1;i<=a;i++)
#define ort (b+s)/2
#define y2 asrwjaelkf
#define y1 asseopirwjaelkf
#define set multiset

using namespace std;

inline int read() {
	int res = 0 ;int neg ;
	while(true){char ch = getchar();if(ch>='0' && ch<='9' || ch=='-'){if(ch=='-') neg = -1;else neg = 1 , res = ch-'0';break;} }
	while(true){char ch = getchar();if(ch>='0' && ch<='9') res*=10 , res+=ch-'0';else break;}
	return res*neg;
}


typedef long long Lint;
typedef double db;
typedef pair<int,int> ii;
typedef pair<db,db> dd;
typedef pair<ii,int> iii;
typedef pair<ii,ii> i4;

const int maxn = 100020;
const int maxm = 1000020;
const int MOd = 1e9 + 7;
const int K = 320;

int a, q;
int dad[maxn][20], der[maxn];
Lint ar[maxn];
vector<ii> w[maxn];

int lca( int x, int y ) {
	if( der[x] < der[y] ) swap( x, y );
	for(int k=17;k>=0;k--)
		if( (1<<k) <= der[x] && der[dad[x][k]] > der[y] ) x = dad[x][k];
	if( der[x] != der[y] ) x = dad[x][0];
	for(int k=17;k>=0;k--)
		if( (1<<k) <= der[x] && dad[x][k] != dad[y][k] ) x = dad[x][k], y = dad[y][k];
	if( x != y ) x = dad[x][0];
	return x;
}

void dfs( int n, int back, int s, Lint s2 ) {
	ar[n] = s2;
	der[n] = s;
	dad[n][0] = back;
	for(int i=1;(1<<i)<=s;i++)
		dad[n][i] = dad[dad[n][i-1]][i-1];
	for(int i=0;i<w[n].size();i++)
		if( w[n][i].fi != back ) dfs( w[n][i].fi, n, s + 1, s2 + w[n][i].se );
	
}

int f( int x, int s ) {
	for(int i=0;(1<<i)<=s;i++)
		if( (1<<i)&s ) x = dad[x][i];
	return x;
}

int main() {
	
	freopen("qtree2.gir","r",stdin);
	freopen("qtree2.cik","w",stdout);
	
	scanf("%d %d",&a,&q);
	
	for(int i=1,j,k,t;i<a;i++) {
		scanf("%d %d %d",&j,&k,&t);
		w[j].pb( ii( k, t ) );
		w[k].pb( ii( j, t ) );
	}
	
	dfs( 1, 0, 0, 0 );
	
	while( q-- ) {
		char ch[10];
		int x, y, k;
		scanf(" %s %d %d",ch,&x,&y);
		int h = lca( x, y );
		int d = der[x]+der[y]-2*der[h];
		if( ch[0] == 'D' ) printf("%lld\n",ar[x]+ar[y]-2*ar[h]);
		else {
			scanf("%d",&k); k--;
			if( k > d ) { assert(0); continue; }
			int ans = 0;
			if( der[x] - der[h] >= k ) {
				ans = f( x, k );
			} else ans = f( y, d-k );
			printf("%d\n",ans);
		}
		
	}
	
	return 0;
}
