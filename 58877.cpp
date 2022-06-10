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
map< int, int > H11, H12, H13;
map< pii, int > H21, H22, H23;
map< pair< pii , int >, int > H3;
int x, y, z, n;
ll ans = 0;
int main() {
	freopen("onlyone.gir", "r", stdin);
	freopen("onlyone.cik", "w", stdout);
	scanf("%d", &n);
	FOR(i, 1, n) {
		scanf("%d %d %d", &x, &y, &z);
		ans += 3 * H3[mp(mp(x, y), z)]++;
		ans -= 2 * H21[mp(x, y)]++;
		ans -= 2 * H22[mp(y, z)]++;
		ans -= 2 * H23[mp(x, z)]++;
		ans += H11[x]++;
		ans += H12[y]++;
		ans += H13[z]++;
	}
	cout << ans << endl;
}
