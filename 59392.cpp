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
typedef pair<int,ii> iii;
typedef pair<ii,ii> i4;

const int maxn = 3520;
const int maxm = 1000020;
//~ const int MOd = 1e9 + 7;

int a, dad[maxn], MOd;
int dn[maxn][maxn];

int mul( int a, int b ) {
	 return (Lint)a * b % MOd;
}

int add( int a, int b ) {
	return a+b>=MOd? a+b-MOd:a+b;
}

int main() {
	
	freopen("pattern.gir","r",stdin);
	freopen("pattern.cik","w",stdout);
	
	scanf("%d %d",&a,&MOd);
	
	dn[0][0] = 1;
	for(int i=1;i<=a;i++) {
		int t = 0;
		for(int j=0;j<=a;j++) {
			dn[j][i] = t;
			t = add( t, t );
			t = add( t, mul( (j + 1), dn[j][i-1] ) );
		}
	}
	
	int ans = 0;
	for(int i=1;i<=a;i++) {
		ans = add( ans, mul( 2, mul( dn[a][i], dn[a][i] ) ) );
		if( i < a ) ans = add( ans, mul( 2, mul( dn[a][i], dn[a][i+1] ) ) );
	}
	cout << ans << endl;
	return 0;
}
