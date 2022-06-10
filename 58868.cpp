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
const int N = 2e3 + 5;

int n, m, x, y, z, t, a[N];
vector< int > sum[N];

class fenwick {
	public:
	vector< int > pre, suff;
	fenwick() { suff.resize(N, inf); pre.resize(N, inf); }
	void preupd(int x, int y) {
		for(; x < N; x += x & -x)
			pre[x] = min(pre[x], y);
	}
	void suffupd(int x, int y) {
		for(; x > 0; x -= x & -x)
			suff[x] = min(suff[x], y);
	}
	int preque(int x) {
		int ans = inf;
		for(; x > 0; x -= x & -x)
			ans = min(pre[x], ans);
		return ans;
	}
	int suffque(int x) {
		int ans = inf;
		for(; x < N; x += x & -x)
			ans = min(suff[x], ans);
		return ans;
	}
} dp[N];

int main() {
	freopen("est.gir", "r", stdin);
	freopen("est.cik", "w", stdout);
	scanf("%d %d", &m, &n); ++m;
	FOR(i, 1, n) {
		scanf("%d", &a[i]);
		a[i]++;
	}
	FOR(i, 1, n) {
		int sum = 0;
		FOR(j, 0, n) {
			if(j >= i) sum += a[j];
			::sum[i].pb(sum);
		}
	}
	int res = inf;
	ROF(i, n, 1) {
		int cur = 0;
		FOR(j, i, n) {
			cur += a[j];
			if(cur > m) break;
			int ans = 0;
			if(j == n) ;
			else {
				int ind = lower_bound(sum[j+1].begin(), sum[j+1].end(), cur) - sum[j+1].begin();
				ans = min(dp[j+1].preque(ind-1) + cur, dp[j+1].suffque(ind) - cur);
			}
			if(i == 1) res = min(res, ans);
			dp[i].preupd(j, ans - cur);
			dp[i].suffupd(j, ans + cur);
		}
	}
	cout << res << endl;
}
