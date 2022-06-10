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
const int logN = 17;
const int inf = 1e9;
const int N = 2e5 + 5;

int root[N], sum[N], wh[N], T, start[N], n, m, x, y, z, t, lca[N][logN + 1], ST[N << 2], up[N], depth[N];
vector< pii > v[N];
char c[11], s[11];
pii e[N];

int query(int k, int bas, int son, int x, int y) {
	if(bas > y || son < x) return 0;
	if(x <= bas && son <= y) return  ST[k];
	return query(sol, bas, orta, x, y) + query(sag, orta + 1, son, x, y);
}

int update(int k, int bas, int son, int x, int y) {
	if(bas > x || son < x) return ST[k];
	if(bas == son) return ST[k] = y;
	return ST[k] = update(sol, bas, orta, x, y) + update(sag, orta + 1, son, x, y);
}

int LCA(int x, int y) {
	if(depth[x] < depth[y]) swap(x, y);
	int diff = depth[x] - depth[y];
	FOR(i, 0, logN)
		if((1 << i) & diff)
			x = lca[x][i];
	if(x == y) return x;
	ROF(i, logN, 0)
		if(lca[x][i] != lca[y][i])
			x = lca[x][i],
			y = lca[y][i];
	return lca[x][0];
}

int dfs(int node, int root = 0) {
	lca[node][0] = root;
	foreach(it, v[node])
		if(root != it->st)
			sum[node] += dfs(it->st, node);
	return ++sum[node];
}

void doit(int node, int root, int head, int w = 0) {
	::root[node] = root;
	depth[node] = depth[root] + 1;
	int t = 0, ww = 0;
	start[node] = ++T;
	wh[T] = node;
	up[node] = head;
	update(1, 1, n, start[node], w);
	foreach(it, v[node])
		if(it->st != root && sum[it->st] >= sum[t])
			t = it->st, ww = it->nd;
	if(t) doit(t, node, head, ww);
	foreach(it, v[node]) if(it->st != root && it->st != t) doit(it->st, node, it->st, it->nd);
}

int get(int x, int y) {
	int ans = 0;
	while(depth[x] > depth[y]) {
		int go = min(depth[x] - depth[y] - 1, depth[x] - depth[up[x]]);
		ans  += query(1, 1, n, start[x] - go, start[x]);
		x = root[wh[start[x] - go]];
	} return ans;
}

int take(int x, int y) {
	if(x == y) return 0;
	int l = LCA(x, y);
	return get(x, l) + get(y, l);
}

int go(int x, int y) {
	FOR(i, 0, logN)
		if((1 << i) & y)
			x = lca[x][i];
	return x;
} 

int main() {

	freopen("qtree2.gir", "r", stdin);
	freopen("qtree2.cik", "w", stdout);

	int q;
	scanf("%d %d", &n, &q);
	
	FOR(i, 1, n) v[i].clear();
	T = 0;

	FOR(i, 2, n) {
		scanf("%d %d %d", &x, &y, &z);
		v[x].pb(mp(y, z));
		v[y].pb(mp(x, z));
		e[i-1] = mp(x, y);
	} dfs(1, 0);
	doit(1, 0, 1);
	FOR(i, 1, logN)
		FOR(j, 1, n)
			lca[j][i] = lca[lca[j][i-1]][i-1];
	int k;
	FOR(i, 1, q) {
		scanf(" %s %d %d", c, &x, &y);
		if(c[0] == 'D') { printf("%d\n", take(x, y)); }
		else {
			scanf("%d", &k);
			int l = LCA(x, y); k--;
			if(depth[x] - depth[l] >= k) printf("%d\n", go(x, k));
			else if(depth[x] - depth[l] == k) printf("%d\n", l);
			else  {
				int t = go(y, (depth[y] - depth[l] - 1) - (k - (depth[x] - depth[l] + 1)));
				if(depth[t] < depth[l]) {
					cout << -1 << endl;
				}
				else cout << t << endl;
			}
		}
	}
}
