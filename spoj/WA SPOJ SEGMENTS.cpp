/* 	The solution gets WA vertdict.
	Tutorial: http://codeforces.com/blog/entry/58621
 */
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstdio>
using namespace std;
typedef long long lint;
const lint INF = 1LL << 60;
lint D[10000];
int N, Hi;
lint X1[500], X2[500];
struct Edge {
	int u, v;
	lint w;
	Edge(int u = 0, int v = 0, lint w = 0) : u(u), v(v), w(w) {}
};
Edge E[400 * 1000];
int NE;

void Assert(bool condition) {
	if (!condition) { 
		int *p = NULL;
		*p = 3;	
	}
}

inline bool TestBit(int use, int p) { return (use >> p) & 1; }

/*
const int M = 19;
int Brute() {
	// 0 1 2 .. 20
	// 1 3 5 .. 41
	// 0,2,4,42
	int n = M;
	int res = 1 << 30;
	for (int use = 0; use < (1 << n); ++use) {
		int cur = 0;
		for (int i = 1; i <= N; ++i) {
			int c = 0;
			for (int j = 0; j < n; ++j) {
				int x = j * 2 + 1;
				if (TestBit(use, j) && X1[i] <= x && x <= X2[i]) {
					c++;
				}
			}
			if (!c) {cur=-1;break;}
			cur = max(cur, c);
		}
		if (cur==-1) continue;
		res = min(res, cur);
	}
	return res;
}*/


void Read() {
	cin >> N;
	Assert(1 <= N && N <= 400);
	for (int i = 1; i <= N; ++i) {
		int h;
		cin >> X1[i] >> X2[i] >> h;
		Assert(X1[i] < X2[i]);
		//X1[i] = rand() % M * 2;
		//X2[i] = rand() % M * 2;
		//if (X1[i] > X2[i]) swap(X1[i], X2[i]);
		//if (X1[i] == X2[i]) X2[i] += 2;
	}
}

void Compact() {
	set<lint> s;	
	for (int i = 1; i <= N; ++i) {
		s.insert(X1[i]);
		s.insert(X2[i]);
	}
	Hi = 0;
	map<lint, int> m;
	for (set<lint>::iterator it = s.begin(); it != s.end(); ++it) {
		m[*it] = ++Hi;
	}
	for (int i = 1; i <= N; ++i) {
		X1[i] = m[X1[i]];
		X2[i] = m[X2[i]];
		Assert(X1[i] < X2[i]);
	}
}


void AddEdge(int u, int v, lint w) {
	E[NE++] = Edge(u, v, w);
}


bool HasCycle() {
	for (int i = 1; i <= Hi; ++i) {
		D[i] = INF;
	}
	D[0] = 0;
	bool was = false;
	for (int i = 0; i <= Hi + 4; ++i) {
	    was = false;
		for (int j = 0; j < NE; ++j) {
			int u = E[j].u;
			int v = E[j].v;
			lint w = E[j].w;
			if (D[u] == INF) continue;
			if (D[v] > D[u] + w) {
				D[v] = D[u] + w;
				was = true;
			}
			Assert(D[v] > -30720000000LL);
		}
		if (!was) break;
	}

	return was;
}

// x2 - x1 <= w
void AddInequality(int x1, int x2, lint w) {
	AddEdge(x1, x2, w);
}

bool Check(int t) {
	NE = 0;
	for (int i = 1; i <= Hi; ++i) {
		AddEdge(0, i, 0);
	}
	for (int i = 2; i <= Hi; ++i) {
		AddInequality(i, i - 1, 0);
	}
	// x2 - (x1 - 1) <= t
	for (int i = 1; i <= N; ++i) {
		AddInequality(X1[i], X2[i], t);
		AddInequality(X2[i], X1[i], -1);
	}		
	return !HasCycle();
}

void Solve() {	
	Read();
	//cout << Brute() << " "; 
	//int ans1 = Brute();

	Compact();	
	int ans = 0;
	for (int i = 1; i <= N; ++i) {
		 if (Check(i)) {
		 	ans = i;
		 	break;
		 } 
	}
	cout << ans << endl;
}


int main() {	
	freopen("input.txt", "r", stdin);
	Solve();
	return 0;
}