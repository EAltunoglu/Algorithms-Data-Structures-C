#include <bits/stdc++.h>

using namespace std;

#define F first
#define S second

#define endl '\n'

#define mp make_pair
#define pb push_back

#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define ROF(i, a, b) for(int i = a; i >= b; i--)

#define type(x) __typeof((x).begin())
#define foreach(i, x) for(type(x) i = (x).begin(); i != (x).end(); i++)

#define sol (root + root)
#define sag (root + root + 1)
#define orta ((bas + son) >> 1)

#define bit __builtin_pop_bcount

#ifndef D
    #define dbg(x) 0
    #define dbgs(x) 0
#else
    #define dbg(x) cerr << (#x) << " --> " << (x) << endl
    #define dbgs(x) cerr << (#x) << " --> " << (x) << ' '
#endif

typedef long long ll;
typedef pair < int, int > pii;

const int inf = 1e9 + 5;
const ll linf = 1e18 + 5;

#define y1 something_stupid

const int N = 30000 + 5;

class node{

    public:

    int mn, k, add;

};

class tree{

    public:

    node x;

    int l, r;

}t[N * 50];

int n, x1, y1, x2, y2, tick;
vector < pair < pii, pii > > xs;

int make(int x, int y) {
    int p = ++tick;
    t[p].l = t[p].r = 0;
    t[p].x.mn = 0;
    t[p].x.k = y - x + 1;
    t[p].x.add = 0;
    return p;
}

void merge(node &ans, node x, node y) {

    ans.mn = min(x.mn, y.mn);

    ans.k = 0;

    ans.k += (x.mn == ans.mn) * x.k;
    ans.k += (y.mn == ans.mn) * y.k;

    ans.mn += ans.add;

}

void merge2(node &ans, node x, int k) {

    ans.mn = ans.add;

    ans.k = k + x.k * !x.mn;

}

void update(int root, int bas, int son, int x, int y, int val) {

    if(son < x or y < bas)
        return;

    if(x <= bas and son <= y)
    {
        t[root].x.mn += val;
        t[root].x.add += val;

        return;
    }

    if(x <= orta)
    {
        if(!t[root].l)
            t[root].l = make(bas, orta);

        update(t[root].l, bas, orta, x, y, val);
    }

    if(y > orta)
    {
        if(!t[root].r)
            t[root].r = make(orta + 1, son);

        update(t[root].r, orta + 1, son, x, y, val);
    }

    if(!t[root].l)
        merge2(t[root].x, t[t[root].r].x, orta - bas + 1);
    else if(!t[root].r)
        merge2(t[root].x, t[t[root].l].x, son - (orta + 1) + 1);
    else
        merge(t[root].x, t[t[root].l].x, t[t[root].r].x);

}

int main() {

#ifndef D
    freopen("ru.gir", "r", stdin);
    freopen("ru.cik", "w", stdout);
#endif

    int tt;

    cin >> tt;

    FOR(test, 1, tt)
    {
        xs.clear();

        ll ans = 0;

        int root = make(1, inf);

        cin >> n;

        FOR(i, 1, n)
        {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

            x1++;
            x2++;

            y1++;

            xs.pb(mp(mp(x1, 0), mp(y1, y2)));
            xs.pb(mp(mp(x2, 1), mp(y1, y2)));
        }

        sort(xs.begin(), xs.end());

        FOR(i, 0, (int) xs.size() - 1)
        {
            int next;

            if(i < xs.size() - 1)
                next = xs[i + 1].F.F;
            else
                next = xs[i].F.F + 1;

            if(!xs[i].F.S)
                update(root, 1, inf, xs[i].S.F, xs[i].S.S, 1);
            else
                update(root, 1, inf, xs[i].S.F, xs[i].S.S, -1);

            ans += (ll) (inf - t[root].x.k) * (next - xs[i].F.F);
        }

        cout << "Case " << test << ": " << ans << endl;

        memset(t, 0, sizeof(t));

        tick = 0;
    }

    return 0;

}
