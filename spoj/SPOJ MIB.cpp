/*
 * It uses algorithm of getting permutation number with long arithmetic.
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

const ll BASE = 1000*1000*1000;
const int MAXL = 300;
typedef ll Long[MAXL];

void Add(Long u, Long v) {
	ll carry = 0;
	rep (i, 0, MAXL - 1) {
		carry += u[i] + v[i];
		u[i] = carry % BASE;
		carry /= BASE;
	}
}

void Mul(Long u, ll x) {
	ll carry = 0;
	rep (i, 0, MAXL - 1) {
		carry += u[i] * x;
		u[i] = carry % BASE;
		carry /= BASE;
	}	
}

void Print(Long u) {
	int p = MAXL - 1;
	while (p > 0 && !u[p]) --p;
	cout << u[p];
	rev (i, p - 1, 0) {
		int x = u[i];
		printf("%09d", x);
	}
	printf("\n");
}

void Set(Long u, Long v) {
	rep (i, 0, MAXL - 1) {
		u[i] = v[i];
	}
}

Long FL[1001];

void Init() {
	FL[0][0] = 1;	
	rep (i, 1, 1000) {
		Set(FL[i], FL[i - 1]);
		Mul(FL[i], i);
	}
}

Long res, tmp;

void Calc(vi P, int N) {
	vi v;
	rep (i, 0, MAXL - 1) { 
		res[i] = 0;
	}
	rep (i, 1, N) {
		v.pb(i);
	}

	rep (i, 1, N) {
		ll x = P[i];
		int pos = find(v.begin(), v.end(), x) - v.begin();
		Set(tmp, FL[N - i]);
		Mul(tmp, pos);
		Add(res, tmp);
		v.erase(v.begin() + pos);
	}
	Add(res, FL[0]);
}

char Buf[2000];

void Solve() {
	int n;
	scanf("%d", &n);
	map<string, int> m;
	vs v;
	rep (i, 1, n) {
		scanf("%s", Buf);
		string s(Buf);
		m[s] = 1;
		v.pb(s);
	}
	int cnt = 0;
	for (auto x : m) {
		m[x.first] = ++cnt;
	}
	
	vi p;
	p.pb(0);
	for (string x : v) {
		int pos = m[x];
		p.pb(pos);
	}
	Calc(p, n);
	Print(res);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
#endif	
	Init();
	int tst;
	cin >> tst;
	while (tst--) {
		Solve();
	}
	return 0;
}
