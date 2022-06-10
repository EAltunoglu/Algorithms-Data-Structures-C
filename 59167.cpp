#include "bits/stdc++.h"

using namespace std;

#define type(x) __typeof((x).begin())
#define foreach(it, x) for(type(x) it = (x).begin(); it != (x).end(); it++)

typedef long long ll;
typedef pair < int, int > ii;

const int N = 1e6 + 5;

int n;
int a[N], b[N], id[N], w[N], fen[N];

void up(int x, int k) {
    for(; x < N; x += x & -x)
        fen[x] = min(fen[x], k);
}

int get(int x) {
    int res = 1e9;
    for(; x; x -= x & -x)
        res = min(res, fen[x]);
    return res;
}

int main () {

    memset(fen, 63, sizeof(fen));

#ifndef D
    freopen("race.gir", "r", stdin);
    freopen("race.cik", "w", stdout);
#endif

    scanf("%d", &n);

    for(int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        id[x] = i;
    }

    for(int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        a[i] = id[a[i]];
    }

    for(int i = 1; i <= n; i++) {
        scanf("%d", b + i);
        b[i] = id[b[i]];
        w[b[i]] = i;
    }

    int ans = n;

    for(int i = 1; i <= n; i++) {
        if(get(w[a[i]]) < a[i])
            ans--;
        up(w[a[i]], a[i]);
    }

    printf("%d\n", ans);

    return 0;

}
