/*
	To find optimal solution we can iterate over all posible subsets of subnetworks and 
	then find minimum spanning tree with fact that between all vertexes from one subnetwork
	the distance is zero. So we should get minimum among all values for different subsets.
	Here we use a Prim algorithm to find MST.	
*/
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
#define rep(i,lo,hi) for(int i=(lo);i<=(hi);++i)
#define rev(i,hi,lo) for(int i=(hi);i>=(lo);--i)
#define pb push_back
#define mp make_pair
#define sz(x) ((int)((x).size()))
#define out(x)  cout<<#x<<"="<<(x)<<"\n"
#define LL "%lld" //%I64d 
typedef long long ll;
typedef vector<int> vi;
const ll INF = 1LL << 60;
struct Sub {
	set<int> v;
	int w;
};
const int MAXN = 2000;
int N, Q;
Sub S[100];
ll X[MAXN], Y[MAXN];
ll D[MAXN];
ll Dist[MAXN][MAXN];
bool Use[MAXN];
inline bool TestBit(int use, int p) { return (use >> p) & 1; }

ll Weight(int u, int v, int use) {
	// check if u and v in same Sub
	rep (i, 1, Q) {
		if (!TestBit(use, i - 1)) {
			continue;
		}
		set<int> &a = S[i].v;
		if (a.count(u) && a.count(v)) {
			return 0;
		}
	}
	return Dist[u][v];
}

// Use Prim's algo to find MST
ll MST(int use, ll cur, ll ans) {	
	rep (i, 1, N) {
		D[i] = INF;
		Use[i] = false;
	}
	D[1] = 0;
	ll res = cur;
	rep (step, 1, N) {
		// find smallest not used
		int ix = -1;
		rep (i, 1, N) {
			if (!Use[i] && (ix == -1 || D[i] < D[ix])) {
				ix = i;
			}
		}
		Use[ix] = true;
		res += D[ix];
		if (res >= ans) {
			return res;
		}
		// relax 
		rep (v, 1, N) {
			if (Use[v]) continue;
			ll w = Weight(ix, v, use);
			if (D[v] > w) {
				D[v] = w;
			}
		}
	}
	return res;
}

void Solve() {
	scanf("%d %d", &N, &Q);
	rep (i, 1, Q) {
		set<int> v;
		int n, w;
		Sub sub;
		scanf("%d %d", &n, &w);
		rep (i, 1, n) {
			int x;
			scanf("%d", &x);
			v.insert(x);
		}
		sub.v = v;
		sub.w = w;
		S[i] = sub;
	}
	rep (i, 1, N) {
		int x, y;
		scanf("%d %d", &x, &y);
		X[i] = x;
		Y[i] = y;
	}
	rep (i, 1, N) {
		rep (j, 1, N) {
			ll dx = X[i] - X[j];
			ll dy = Y[i] - Y[j];
			Dist[i][j] = dx * dx + dy * dy;
		}
	}
	ll ans = INF;
	for (int use = 0; use < (1 << Q); ++use) {
		ll cur = 0;
		rep (i, 1, Q) {
			if (TestBit(use, i - 1)) {
				cur += S[i].w;
			}
		}
		if (cur >= ans) continue;
		cur = MST(use, cur, ans);
		ans = min(cur, ans);
	}
	cout << ans << endl;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
//	freopen("out1", "w", stdout);
#endif		
	int tst;
	cin >> tst;
	bool first = true;
	while (tst--) {
		if (first) first = false;
		else printf("\n");
		Solve();
	}
	return 0;
}
