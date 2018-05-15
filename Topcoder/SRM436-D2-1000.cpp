/*
	To make multipclation of numbers bigger we should make them same as possible.
	The solution also assumes usage of big integers implementation.
	Problem: https://community.topcoder.com/stat?c=problem_statement&pm=10342&rd=13698
	Tutorial: https://apps.topcoder.com/wiki/display/tc/SRM+436
	
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
int K;
int A[100], P[100];
double Total;
const ld EPS = 1e-11;

void Mul(int u[], int v[], int w[], int n) {
	for (int i = 0; i < n; ++i) {
		int carry = 0;
		for (int j = 0; j < n; ++j) {
			carry += u[i] * v[j] + w[i + j];
			w[i + j] = carry % 10;
			carry /= 10;
		}
	}
}

void Convert(string x, int u[]) {	
	int n = sz(x);
	rep (i, 0, n - 1) {
		u[i] = x[n - i - 1] - '0';
	}
}

string Mul(string x, string y) {
	int u[100], v[100], w[200];
	memset(u, 0, sizeof(u));
	memset(v, 0, sizeof(v));
	memset(w, 0, sizeof(w));
	Convert(x, u);
	Convert(y, v);
	Mul(u, v, w, 100);
	int p = 199;
	while (p > 0 && !w[p]) --p;
	string res;
	rep (i, 0, p) {
		char ch = '0' + w[i];
		res = ch + res;
	}
	return res;
}

struct Item {
	string s;
	int p;
	Item(string s, int p) : s(s), p(p) {}
};

bool operator <(const Item &a, const Item &b) {
	if (sz(a.s) != sz(b.s)) return sz(a.s) < sz(b.s);
	if (a.s != b.s) return a.s < b.s;
	return a.p < b.p;
}

string Calc(string x, string y, int swaps, bool need) {
	int n = sz(x);	
	int p = 0;
	while (p < n && x[p] == y[p]) ++p;
	if (p == n || !swaps) {
		return Mul(x, y);
	}
	if (need) {
		--swaps;
		swap(x[p], y[p]);
	}
	if (x[p] < y[p]) {
		swap(x, y);
	}
	
	for (int i = p + 1; swaps && i < n; ++i) {
		if (x[i] > y[i]) {
			--swaps;
			swap(x[i], y[i]);
		}
	}
	if (swaps & 1) {
		bool fnd = false;
		for (int j = 0; j < n; ++j) {
			if (x[j] == y[j]) {
				fnd = true;
			}
		}
		if (!fnd) {
			swap(x[n - 1], y[n - 1]);
		}
	}

	string cur = Mul(x, y);
	return cur;
}


string Calc(string x, string y, int swaps) {
	string s1 = Calc(x, y, swaps, false);
	string s2 = Calc(x, y, swaps, true);
	return Item(s1, 0) < Item(s2, 0) ? s2 : s1;
}


class DigitsSwap {
public:
	string maximalProduct(string x, string y, int swaps) {
		return Calc(x, y, swaps);
	}
};

