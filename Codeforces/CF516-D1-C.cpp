/*
	http://codeforces.com/blog/entry/16468
*/
#include <bits/stdc++.h>
using namespace std;
#define rep(i,lo,hi) for(ll i=(lo);i<=(ll)(hi);++i)
#define rev(i,hi,lo) for(ll i=(hi);i>=(ll)(lo);--i)
#define pb push_back
#define mp make_pair
#define sz(x) ((x).size())
#define out(x)  cout<<#x<<"="<<(x)<<"\n"
#define pout(p)  cout<<#p<<"=("<<(p.first)<<","<<p.second<<")\n"
#define vout(x) cout<<#x<<"={";for(auto v:x)cout<<v<<",";cout<<"}\n";
#define aout(x,lo,hi) cout<<#x<<"={";rep(i,lo,hi)cout<<x[i]<<",";cout<<"}\n";
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
typedef pair<ll, int> plli;

const ll INF = 1LL << 60;
const int MAXN = 100 * 1000 + 1;
int N, M, D[MAXN], H[MAXN];
const int MAXQ = 1 << 20;
plli Q1[MAXQ * 2];
plli Q2[MAXQ * 2];

inline plli Max(plli a, plli b) {
	if (a.first > b.first) return a;
	if (a.first < b.first) return b;
	return a.second > b.second ? a : b;
}

void Set(plli Q[], int p, plli val) {
	for (p += MAXQ; p; p >>= 1) {
		Q[p] = Max(Q[p], val);
	}
}

plli Get(plli Q[], int lo, int hi) {
	plli res = mp(-INF, -1);
	for (lo += MAXQ, hi += MAXQ; lo <= hi; ++lo >>= 1, --hi >>= 1) {
		if ((lo & 1) == 1) res = Max(res, Q[lo]);
		if ((hi & 1) == 0) res = Max(res, Q[hi]);
	}
	return res;
}

void Init() {
	rep (i, 0, MAXQ * 2 - 1) {
		Q1[i] = Q2[i] = mp(-INF, -1);
	}
}

pair<ll, int> GetMaxSum1(int lo, int hi) {
	return Get(Q1, lo, hi);
}

pair<ll, int> GetMaxSum2(int lo, int hi) {
	return Get(Q2, lo, hi);
}

void Process(int a, int b) {
	int l, r;
	if (a <= b) {
		l = b + 1;			
		r = a - 1 + N;
	} else { // [a..N] [1..b]
		l = b + 1; 
		r = a - 1;  
	}	
	pair<ll, int> pr1 = GetMaxSum1(l, r);
	pair<ll, int> pr2 = GetMaxSum2(l, pr1.second - 1);
	pair<ll, int> pr4 = GetMaxSum2(l, r);
	pair<ll, int> pr3 = GetMaxSum1(-pr4.second + 1, r);		
	ll ans = max(pr1.first + pr2.first, pr3.first + pr4.first);
	cout << ans << endl;
}

void ReadData() {
	scanf("%d %d", &N, &M);	
	rep (i, 1, N) {
		scanf("%d", &D[i]);
	}
	rep (i, 1, N) {
		scanf("%d", &H[i]);
	}	
}

void Preprocess() {
	ll s = 0;
	int pos = 0;
	rep (i, 1, N*2) {
		int j = i > N ? i - N : i;
		ll h2 = H[j] * 2;
		ll cur = D[pos];
		++pos; if (pos > N) pos = 1;
		ll s1 = h2 + cur + s;
		ll s2 = h2 - cur - s;
		s += cur;	
		Set(Q1, i, mp(s1, i));
		Set(Q2, i, mp(s2, -i));
	}
}

void Solve() {
	ReadData();
	Preprocess();
	while (M--) {
		int l, r;
		scanf("%d %d", &l, &r);
		Process(l, r);
	}
}


int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	//freopen("out1", "w", stdout);
#endif		
	Init();
	Solve();
	return 0;
}
