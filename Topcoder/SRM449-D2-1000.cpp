/*
	It uses dp by profile aproach. So we starts from middle line and count number of arrangements to
	both directions. On each steps it keeps bitmask for already used cells.
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
const ll MOD = 2000000011LL;
int N, M, D[100];
vi X, Y;
ll dp[16][1<<15][2];
vi V;
vpii U;
inline int Abs(int x) { return x > 0 ? x : -x; }
inline bool TestBit(int val, int p) { return (val >> p) & 1; }
inline int Get(int y) { return D[y + 50]; }
inline void Set(int y, int p) { D[y + 50] |= (1 << p); }

void GetX(int len, bool neg, int &x1, int &x2) {
	if (!neg) {
		x2 = N - 1; 	
		x1 = x2 - len + 1;
	} else {
		x1 = -(N - 1); 
		x2 = x1 + len - 1;
	}
}

void Prerprocess() {
	memset(D, 0, sizeof(D));
	rep (i, 0, M - 1) {
		int x = X[i];
		int y = Y[i];
		bool neg = y < 0;
		int len = 2 * N - Abs(y) - 1;
		int x1, x2;
		GetX(len, neg, x1, x2);
		int shift = x - x1;
		Set(y, shift);
	}
}

void Count(int i, int len, int use, int nuse) {
	if (i == len) {
		if (use == ((1 << len) - 1)) {
			V.pb(nuse);
		}
		return;
	}
	if (TestBit(use, i)) {
		Count(i + 1, len, use, nuse);
	} else {
		int nlen = len - 1;
		// Left
		if (i - 1 >= 0 && !TestBit(nuse, i - 1)) {
			Count(i + 1, len, use | (1 << i), nuse | (1 << (i - 1)));
		}
		// Right
		if (i < nlen && !TestBit(nuse, i)) {
			Count(i + 1, len, use | (1 << i), nuse | (1 << i));
		}
		// Horizontal
		if (i + 1 < len && !TestBit(use, i + 1)) {
			Count(i + 2, len, use | (1 << i) | (1 << (i + 1)), nuse);
		}
	}
}

void CountMiddle(int i, int len, int use, int use1, int use2) {
	if (i == len) {
		if (use == ((1 << len) - 1)) {
			U.pb(mp(use1, use2));
		}
		return;
	}
	if (TestBit(use, i)) {
		CountMiddle(i + 1, len, use, use1, use2);
	} else {
		int nlen = len - 1;

		// Left Up
		if (i - 1 >= 0 && !TestBit(use1, i - 1)) {
			CountMiddle(i + 1, len, use | (1 << i), use1 | (1 << (i - 1)), use2);
		}
		// Right Up
		if (i < nlen && !TestBit(use1, i)) {
			CountMiddle(i + 1, len, use | (1 << i), use1 | (1 << i), use2);
		}

		// Left Down
		if (i - 1 >= 0 && !TestBit(use2, i - 1)) {
			CountMiddle(i + 1, len, use | (1 << i), use1, use2 | (1 << (i - 1)));
		}
		// Right Down
		if (i < nlen && !TestBit(use2, i)) {
			CountMiddle(i + 1, len, use | (1 << i), use1, use2 | (1 << i));
		}
		// Horizontal
		if (i + 1 < len && !TestBit(use, i + 1)) {
			CountMiddle(i + 2, len, use | (1 << i) | (1 << (i + 1)), use1, use2);
		}
	}
}

vi GetCount(int len, int use) {
	V.clear();
	Count(0, len, use, 0);
	return V;
}

ll Rec(int k, int use, bool neg) {
	if (k == N) {		
		return use == 0;
	}	
	int y = neg ? -k : k;
	int duse = Get(y);
	if (use & duse) return 0;
	ll &dr = dp[k][use][neg];
	if (dr != -1) return dr;

	use |= duse;
	int len = 2 * N - Abs(y) - 1;
	int x1, x2;
	GetX(len, neg, x1, x2);
	ll res = 0;
	vi v = GetCount(len, use);

	for (auto nuse : v) {
		ll cur = Rec(k + 1, nuse, neg);
		res += cur;
		res %= MOD;
	}
	return dr = res;
}

ll Calc(vi X, vi Y, int N) {
	memset(dp, -1, sizeof(dp));
	::X = X; 
	::Y = Y;
	::N = N;
	::M = sz(X);
	Prerprocess();
	int len = 2 * N - 1;
	ll ans = 0;
	int duse = Get(0);
	U.clear();
	CountMiddle(0, len, duse, 0, 0);
	for (auto pr : U) {
		int use1 = pr.first;
		int use2 = pr.second;
		ll cur1 = Rec(1, use1, 1);
		ll cur2 = Rec(1, use2, 0);
		ans += cur1 * cur2;
		ans %= MOD;
	}
	return ans;
}

class HexagonalBattlefieldEasy {
public:
	int countArrangements(vector <int> X, vector <int> Y, int N) {
		return Calc(X, Y, N);
	}
};

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
#endif	
    
	// 0 ans=10
	//int N = 3; int x[] = {-2,0,1,1,0}; int y[] = {-2,0,1,0,2};

	// 1 ans=2
	//int N = 2; int x[] = {0}; int y[] = {0};

	// 1 ans=104
	//int N = 3; int x[] = {0}; int y[] = {0};

	// 3 ans=6
	//int N = 3; int x[] = {-1,0,0,1,2}; int y[] = {0,0,1,0,0};

	// 4 ans=1
	//int N = 2; int x[] = {0,1,0,0,1,-1,-1}; int y[] = {0,0,-1,1,1,0,-1};

	// custom 4:78408 5:683342244
	int N = 4; int x[] = {0}; int y[] = {0};


	int m = sizeof(x) / sizeof(int);
	vi X; vi Y;
	rep (i,0,m-1) { X.pb(x[i]); Y.pb(y[i]); }
	
	cout << Calc(X, Y, N) << endl;

	return 0;
}
