#include <bits/stdc++.h>
using namespace std;
#define rep(i,lo,hi) for(ll i=(lo);i<=(ll)(hi);++i)
#define rev(i,hi,lo) for(ll i=(hi);i>=(ll)(lo);--i)
#define pb push_back
#define mp make_pair
#define sz(x) ((x).size())
#define out(x)  cout<<#x<<"="<<(x)<<"\n"
#define vout(x) cout<<#x<<"={";for(auto v:x)cout<<v<<",";cout<<"}\n";
#define aout(x,lo,hi) cout<<#x<<"={";rep(i,lo,hi)cout<<x[i]<<",";cout<<"}\n";
#define pout(x) cout<<#x<<"={"<<x.first<<","<<x.second<<"}\n";
#define mout(x) cout<<#x<<"={";for(auto v:x)cout<<v.first<<":"<<v.second<<","; cout<<"}\n";
#define LL "%lld" //%I64d 
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii > vpii;
typedef vector<ll > vll;
typedef pair<ll,ll> pll;
inline ll Abs(ll x) { return x > 0 ? x : -x; }
const int MAXN = 1 << 21;
const int MAXQ = 1 << 21;
vi G[MAXN];
int N, Pos;
int E[MAXN], L[MAXN], A[MAXN];
int Q1[MAXQ * 2], Q2[MAXQ * 2];
int T[MAXN], U[MAXN], S[MAXN], NT;

void Set(int *q, int p, int val) {
	for (p += MAXQ; p; p >>= 1) {
		q[p] = val;
	}
}

int GetRange(int *q, int lo, int hi) {
	int res = 0;
	for (lo += MAXQ, hi += MAXQ; lo <= hi; ++lo >>= 1, --hi >>= 1) {
		if ((lo & 1) == 1) res = max(res, q[lo]);
		if ((hi & 1) == 0) res = max(res, q[hi]);
	}
	return res;
}

void DFS(int u, int prev) {
	A[++Pos] = u;
	E[u] = Pos;
	int ng = sz(G[u]);
	rep (i, 0, ng - 1) {
		int v = G[u][i];
		if (v != prev) {
			DFS(v, u);
		}
	}
	A[++Pos] = u;
	L[u] = Pos;
}

void Read() {
	scanf("%d", &N);
	rep(i, 1, N - 1) {
		int u, v;
		scanf("%d %d", &u, &v);
		G[u].pb(v);
		G[v].pb(u);
	}	
	scanf("%d", &NT);
	rep(i, 1, NT) {
		scanf("%d %d", &T[i], &U[i]);
	}
}

void Preprocess() {
	set<pii> s;
	rev(step, NT, 1) {
		int type = T[step];
		int u = U[step];
		int e = E[u];
		int l = L[u];

		if (type == 3) {
			s.insert(mp(e, step));			
		}
		if (type == 1) {
			auto it = s.lower_bound(mp(e, 0));
			vpii w;
			while (it != s.end()) {
				if (it->first > l) break;
				S[it->second] = step;
				w.pb(*it);
				++it;
			}
			for (auto x : w) {
				s.erase(x);
			}

		}

	}
}

void Solve() {
	DFS(1, 0);
	Preprocess();                                                   
	int q;
	rep(step, 1, NT) {
		int type = T[step], u = U[step];
		int e = E[u], l = L[u];
		if (type == 1) {
			// skip
		}
		if (type == 2) {
			Set(Q2, e, step);	
		}
		if (type == 3) {
			int v1 = S[step];
			int v2 = GetRange(Q2, e, l);
			int v = v1 > v2 ? 1 : 0;
			printf("%d\n", v);
		}
	}
}


int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
#endif
	Read();
	Solve();
	return 0;
}