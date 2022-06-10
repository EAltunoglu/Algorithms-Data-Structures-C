#include <bits/stdc++.h>

using namespace std;

#define dbgs(x) cerr << (#x) << " --> " << (x) << ' '
#define dbg(x) cerr << (#x) << " --> " << (x) << endl

#define foreach(i,x) for(type(x)i=x.begin();i!=x.end();i++)
#define FOR(ii,aa,bb) for(int ii=aa;ii<=bb;ii++)
#define ROF(ii,aa,bb) for(int ii=aa;ii>=bb;ii--)

#define type(x) __typeof(x.begin())

#define orta (bas + son >> 1)
#define sag (k + k + 1)
#define sol (k + k)

#define pb push_back
#define mp make_pair

#define nd second
#define st first

#define endl '\n'

typedef pair < int ,int > pii;

typedef long long ll;

const long long linf = 1e18+5;
int mod = (int) 1e9 + 7;
const int logN = 18;
const int inf = 1e9;
const int N = 1e2 + 5;

int a[N], n, m, x, y, z;
ll dp[N][N], bef[N], LP;
vector< int > v[N], g[N];

void doit(int node, int root) {
	v[root].pb(node);
	foreach(it, g[node])
		if(*it != root)
			doit(*it, node);
}

void f(int node) {
	FOR(i, 0, LP) dp[node][i] = 0;
	if(v[node].size() == 0) {
		dp[node][0] = 1;
		return ;
	}
	dp[node][0] = 1;
	foreach(it, v[node]) {
		f(*it);
		FOR(i, 0, LP) { bef[i] = dp[node][i]; dp[node][i] = 0; }
		FOR(i, 0, LP) 
			FOR(j, 0, LP - i) {
				if(i + j + 1 <= LP) dp[node][max(i, j + 1)] += bef[i] * dp[*it][j];
				if(i + j + 2 <= LP) dp[node][max(i, j + 2)] += bef[i] * dp[*it][j];
			}
	}
}

int main() {
	freopen("diameterofrandomtree.gir", "r", stdin);
	freopen("diameterofrandomtree.cik", "w", stdout);
	scanf("%d", &n);
	FOR(i, 2, n) {
		scanf("%d", &a[i]);
	} 
	FOR(i, 2, n) {
		scanf("%d", &x);
		x++; y = ++a[i];
		g[y].pb(x);
		g[x].pb(y);
	}
	doit(1, 0);
	ll last = -1;
	double ans = 0;
	ROF(i, n + n, 0) {
		LP = i;
		f(1); 
		ll t = 0;
		FOR(j, 0, i) t += dp[1][j];
		if(last == -1) last = t;
		else { ans += ((last - t) * (i + 1)); last = t;}
		if(t == 0) break;
	}
	FOR(i, 2, n) ans /= 2.0;
	printf("%.12lf\n", ans);
}
