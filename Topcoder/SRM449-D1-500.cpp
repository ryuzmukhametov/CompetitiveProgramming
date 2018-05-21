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
ll ans = 0;

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

void Count(int i, int len, int use, int nuse, vector<short> &v) {
	if (i == len) {
		v.pb(nuse);
		return;
	}
	if (TestBit(use, i)) {
		Count(i + 1, len, use, nuse, v);
	} else {
		int nlen = len - 1;
		// Left
		if (i - 1 >= 0 && !TestBit(nuse, i - 1)) {
			Count(i + 1, len, use | (1 << i), nuse | (1 << (i - 1)), v);
		}
		// Right
		if (i < nlen && !TestBit(nuse, i)) {
			Count(i + 1, len, use | (1 << i), nuse | (1 << i), v);
		}
		// Horizontal
		if (i + 1 < len && !TestBit(use, i + 1)) {
			Count(i + 2, len, use | (1 << i) | (1 << (i + 1)), nuse, v);
		}
	}
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
	vector<short> v;
	Count(0, len, use, 0, v);

	for (auto nuse : v) {
		ll cur = Rec(k + 1, nuse, neg);
		res += cur;
		res %= MOD;
	}
	return dr = res;
}

int L, DUSE;
void CountMiddle(int i, int use1, int use2) {
	if (i == L) {
		ll cur1 = Rec(1, use1, 1);
		ll cur2 = Rec(1, use2, 0);
		ans += cur1 * cur2;
		ans %= MOD;
		return;
	}
	if (TestBit(DUSE, i)) {
		CountMiddle(i + 1, use1, use2);
	} else {
		int nlen = L - 1;

		// Left Up
		if (i - 1 >= 0 && !TestBit(use1, i - 1)) {
			CountMiddle(i + 1, use1 | (1 << (i - 1)), use2);
		}
		// Right Up
		if (i < nlen && !TestBit(use1, i)) {
			CountMiddle(i + 1, use1 | (1 << i), use2);
		}

		// Left Down
		if (i - 1 >= 0 && !TestBit(use2, i - 1)) {
			CountMiddle(i + 1, use1, use2 | (1 << (i - 1)));
		}
		// Right Down
		if (i < nlen && !TestBit(use2, i)) {
			CountMiddle(i + 1, use1, use2 | (1 << i));
		}
		// Horizontal
		if (i + 1 < L && !TestBit(DUSE, i + 1)) {
			CountMiddle(i + 2, use1, use2);
		}
	}
}

ll Calc(vi X, vi Y, int N) {
	memset(dp, -1, sizeof(dp));
	::X = X; 
	::Y = Y;
	::N = N;
	::M = sz(X);
	Prerprocess();
	L = 2 * N - 1;	
	int duse = Get(0);
	DUSE = duse;
	CountMiddle(0, 0, 0);
	return ans;
}

class HexagonalBattlefield {
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
	// int len = 14; // max=14 2^14 * 2^12 
	// int hi = (1 << len) - 1;
	// rep (use, 0, hi) {

		
	// }
	// GetCount(len, 0);	 	
	// out(NV);
	// out((1<<len));
	// return 0;
    
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
	int N = 8; int x[] = {1}; int y[] = {1};


	int m = sizeof(x) / sizeof(int);
	vi X; vi Y;
	rep (i,0,m-1) { X.pb(x[i]); Y.pb(y[i]); }
	
	cout << Calc(X, Y, N) << endl;

	return 0;
}
