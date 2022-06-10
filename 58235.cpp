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

int root[N], n, x, y, need[N], bas, son, Q[N];
vector< int > v[N];

bool ctr(int x) {
	ROF(i, n, 1) {
		int node = Q[i];
		int t = v[node].size() - (node != 1);
		need[node] = t - x;
		foreach(it, v[node]) {
			if(*it == root[node]) continue;
			need[node] += max(0, need[*it]);
		}
	}	
	return need[1] <= 0;
}

int main() {
	freopen("luk.gir", "r", stdin);
	freopen("luk.cik", "w", stdout);
	scanf("%d", &n);
	FOR(i, 2, n) {
		scanf("%d %d", &x, &y);
		v[x].pb(y);
		v[y].pb(x);
	}
	bas = 1, son = 0;
	Q[++son] = 1;
	while(bas <= son) {
		int node = Q[bas++];
		foreach(it, v[node])
			if(root[node] != *it) {
				root[*it] = node;
				Q[++son] = *it;
			}
	}
	int bas = 0, son = n;
	while(bas < son) {
		if(ctr(orta)) son = orta;
		else bas = orta + 1;
	}
	cout << bas << endl;
}
