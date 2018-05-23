/*
	To solve problem need to run Bellman-Ford algorithm. Special case is "ENDLESS PROFIT".
	It has such case when there is infinite cycle which can be reached from source (by direct edges) and from dest (by inverse edges). 
	To detect such cycle it uses DFS and shortes path graph from BF algo.
*/
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
typedef long double ld;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii > vpii;
typedef vector<string > vs;
typedef vector<ll > vll;
typedef pair<ll,ll> pll;
typedef pair<double,double> pdd;

const int INF = 1 << 30;

struct Edge {
	int u, v, w;
};

vector<Edge> BuildEdges(vs s) {
	vector<Edge> r;
	for (auto str : s) {
		stringstream sin(str);
		int u, v, w;
		sin >> u >> v >> w;
		Edge e;
		e.u = u;
		e.v = v;
		e.w = w;
		r.pb(e);
	}
	return r;
}

string ToStr(int x) {
	stringstream sout;
	sout << x;
	return sout.str();
}

vector<Edge> E;

bool Relax(Edge &e, vi &d, vi &pf, vi &p) {
	int u = e.u;
	int v = e.v;
	int w = e.w;
	if (d[u] != -INF && d[v] < d[u] - w + pf[v]) {
		d[v] = d[u] - w + pf[v];
		p[v] = u;
		return true;
	}
	return false;
}


vi G[100], IG[100];

void DFS(vi G[], int u, vi &use) {
	use[u] = true;
	for (int i = 0; i < sz(G[u]); ++i) {
		int v = G[u][i];
		if (use[v]) continue;
		DFS(G, v, use);
	}
}

bool Check(vi &cycle, int n, int source, int dest) {
	vi use1(n, 0);
	vi use2(n, 0);
	DFS(G, source, use1);
	DFS(IG, dest, use2);
	for (int u : cycle) {
		if (use1[u] && use2[u]) {
			return true;
		}
	}
	return false;
}

void BuildGraphs() {
	for (auto e : E) {
		int u = e.u;
		int v = e.v;
		G[u].pb(v);
		IG[v].pb(u);
	}
}

bool CheckEndless(vi &p, int source, int dest) {
	int n = sz(p);
	for (int u = 0; u < n; ++u) {
		vi cycle;
		int v = u;
		cycle.pb(u);
		int c = n;
		while (c--) {
			v = p[v];
			if (v == -1) break;
			int pos = find(cycle.begin(), cycle.end(), v) - cycle.begin();
			if (pos < sz(cycle)) {
				cycle.erase(cycle.begin(), cycle.begin() + pos);
				if (Check(cycle, n, source, dest)) {
					return true;
				}
				break;	
			}
			cycle.pb(v);
		}
	}
	return false;
}

string BestRoute(int n, int source, int dest, vs travelCosts, vi pf) {
	E = BuildEdges(travelCosts);
	BuildGraphs();
	vi d(n, -INF);
	vi p(n, -1);
	d[source] = pf[source];

	int cnt = n * 2;

	rep (i, 1, cnt) {
		for (auto e : E) {
			Relax(e, d, pf, p);
		}
	}

	if (d[dest] == -INF) {
		return "IMPOSSIBLE";
	}

	if (CheckEndless(p, source, dest)) {			
		return "ENDLESS PROFIT";
	}

	return "BEST PROFIT: " + ToStr(d[dest]);
}


class SalesmansDilemma {
public:
	string bestRoute(int towns, int origin, int destination, vector<string> travelCosts, vector<int> profits) {
		return BestRoute(towns, origin, destination, travelCosts, profits);
	}
};

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
#endif	

	int towns = 5, origin = 0, destination = 4;
	string s[] = {"0 1 13", "1 2 17", "2 4 20", "0 3 22", "1 3 4747", "2 0 10", "3 4 10"};
	int v[] = {0, 0, 0, 0, 0};
		
	int ns = sizeof(s) / sizeof(string);    	
	int nv = sizeof(v) / sizeof(int);

	vi v1(v, v + nv);
	vs s1(s, s + ns);

	SalesmansDilemma o;
	cout << o.bestRoute(towns, origin, destination, s1, v1) << endl;
	return 0;
}
