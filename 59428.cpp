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
const int N = 1e6 + 5;

int ok[N], h[N], ans[N], n, m, x, y, z, sum[N], depth[N], t;
vector< int > v[N], que[N], upd[N];
vector< pair< pii , int > > look;

int prep(int node, int root = 0) {
	sum[node] = 1;
	foreach(it, v[node])
		if(*it != root && !h[*it])
			sum[node] += prep(*it, node);
	return sum[node];
}

int find(int node, int root, int S) {
	foreach(it, v[node])
		if(!h[*it] && *it != root && sum[node] > S)
			return find(*it, node, S);
	return node;
}

void dfs(int node, int root, int d) {
	depth[node] = d;
	foreach(it, upd[node]) look.pb(mp(mp(*it, node), 0));
	foreach(it, que[node]) look.pb(mp(mp(*it, node), 1));
	foreach(it, v[node])
		if(*it != root && !h[*it])
			dfs(*it, node, d + 1);
}

void solve(int node) {
	prep(node);
	node = find(node, 0, sum[node] / 2);
	h[node] = 1;
	look.clear();
	depth[node] = 0;
	foreach(it, upd[node]) look.pb(mp(mp(*it, node), 0));
	foreach(it, que[node]) look.pb(mp(mp(*it, node), 1));
	foreach(it, v[node])
		if(!h[*it])
			dfs(*it, node, 1);
	sort(look.begin(), look.end());
	set< pii > S;
	foreach(it, look) {
		if(it->nd == 0) {
			if(S.find(mp(depth[it->st.nd], it->st.nd)) != S.end())
				S.erase(S.find(mp(depth[it->st.nd], it->st.nd)));
			else 
				S.insert(mp(depth[it->st.nd], it->st.nd));
		}
		else {
			if(S.size()) ans[it->st.st] = min(ans[it->st.st], (S.begin()->st) + depth[it->st.nd]);
		}
	}
	foreach(it, v[node])
		if(!h[*it])
			solve(*it);
}

int main() {

	freopen("qtree5.gir", "r", stdin);
	freopen("qtree5.cik", "w", stdout);
	
	scanf("%d %d", &n, &m);

	FOR(i, 2, n) {
		scanf("%d %d", &x, &y);
		v[x].pb(y); v[y].pb(x);
	}

	FOR(i, 1, m) {
		ans[i] = inf;
		scanf("%d %d", &x, &y);
		if(x == 0) {
			upd[y].pb(i);
		}
		else {
			ok[i] = 1;
			que[y].pb(i);	
		}
	}
	
	solve(1);

	FOR(i, 1, m)
		if(ok[i]) {
			if(ans[i] == inf) ans[i] = -1;
			//assert(ans[i] != inf);
			printf("%d\n", ans[i]);
		}
	return 0;
}
