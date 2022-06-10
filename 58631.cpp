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

int n, m, x, y, z, a[N];
char arr[123][321];
int h[123][321];
ll SP[53][53];
pii t[N];

int main() {
	freopen("kayak2.gir", "r", stdin);
	freopen("kayak2.cik", "w", stdout);
	scanf("%d", &n);
	FOR(i, 1, n) { scanf("%d", &a[i]); t[i] = mp(a[i], i); }
	sort(t + 1, t + n + 1);
	FOR(i, 1, n)
		FOR(j, 1, n)
			scanf(" %c", &arr[i][j]);
	priority_queue< pair< ll, pii >, vector< pair< ll , pii > >,  greater< pair< ll, pii > > > q;
	FOR(i, 1, n) q.push(mp(abs(a[1] - a[i]), mp(1, i)));
	FOR(i, 1, n) FOR(j, 1, n) SP[i][j] = linf;
	while(!q.empty()) {
		int node = q.top().nd.st;
		int wh = q.top().nd.nd;
		ll cost = q.top().st;
		q.pop();
		if(h[node][wh]) continue;
		h[node][wh] = 1;
		SP[node][wh] = cost;
		if(node == n) {
			cout << cost << endl;
			return 0;
		}
		FOR(i, 1, n)
			if(arr[node][i] == 'Y') {
				if(a[i] > a[wh]) {
					if(SP[i][wh] > cost + abs(a[wh] - a[i])) {
						SP[i][wh] = cost + abs(a[wh] - a[i]);
						q.push(mp(SP[i][wh], mp(i, wh)));
					}
				}
				else {
					ll t1 = lower_bound(t + 1, t + n + 1, mp(a[i], 0)) - t;
					FOR(j, t1, n)
						if(t[j].st <= a[wh]) {
							ll tt = cost + abs(t[j].st - a[i]), ta = t[j].nd;
							if(SP[i][ta] > tt) {
								SP[i][ta] = tt;
								q.push(mp(SP[i][ta], mp(i, ta)));
							}
						}
						else break;
				}
			}
	}
	cout << -1 << endl;
}
