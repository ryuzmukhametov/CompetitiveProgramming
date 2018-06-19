/*
	Firstly we can calculate answers for small N, K values using backtracking.
	Then using https://oeis.org/A033282 we can find formula.
	General tehcnique to get final answer from the formula:
	https://www.hackerrank.com/challenges/polygons/editorial	
*/
#include <vector>
#include <map>
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
const ll MOD = 1000*1000 + 3;
ll Factorial[MOD + 1];

void Init() {
	Factorial[0] = 1;
	for (ll i = 1; i <= MOD; ++i) {
		Factorial[i] = Factorial[i - 1] * i % MOD;
	}
}

ll Pow(ll a, int n) {
	if (n <= 0) return 1;
	if (n & 1) return Pow(a, n - 1) * a % MOD;
	ll t = Pow(a, n / 2);
	return t * t % MOD;
}

ll Inv(ll a) {
	return Pow(a % MOD, MOD - 2);
}

// n! = p^x*a
void FactorizeFactorial(int n, ll &x, ll &a) {
	ll p = MOD;
	ll q = n / p;
	ll r = n % p;
	x = q;
	a = Pow(p - 1, q);
	a *= Factorial[r]; a %= MOD;
	a *= Factorial[q]; a %= MOD;
}

// n!/k!/(n-k)! = p^x*(a/b)
void Comb(int n, int k, ll &x, ll &a, ll &b) {
	ll p = MOD;
	ll l = n - k;
	ll xn, xk, xl;
	ll an, ak, al;
	FactorizeFactorial(n, xn, an);
	FactorizeFactorial(k, xk, ak);
	FactorizeFactorial(l, xl, al);
	x = xn - xk - xl;
	a = an;
	b = ak * al % MOD;
}


ll Calc(ll n, ll k) {
	if (k > n - 3) return 0;
	ll a1, b1, x1;
	ll a2, b2, x2;
	Comb(n + k - 1, k, x1, a1, b1);
	Comb(n - 3, k, x2, a2, b2);	
	ll a = a1 * a2 % MOD;
	ll b = b1 * b2 % MOD;
	ll x = x1 + x2;
	ll t = k + 1;
	while (t % MOD == 0) {
		t /= MOD;
		--x;
	}
	if (x > 0) return 0;
	b *= t;
	b %= MOD;
	ll res = a * Inv(b) % MOD;
	return res;
}


int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("out1", "w", stdout);
#endif		
	Init();
	int tst;
	cin >> tst;
	while (tst--) {
		int n, k;
		scanf("%d %d", &n, &k);
		cout << Calc(n, k) << endl;
	}
	return 0;
}
