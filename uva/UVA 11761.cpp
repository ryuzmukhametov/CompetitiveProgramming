/*
	S = abc/(4R)
	x = 4SR = abc
	Factorize x and then using backtracking generate all 
	possible a,b,c values and pick optimal values among them.
	Correctness is checked using triangle square formula by sides.
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

struct Factor {
	ll p, q, pw[60];
	Factor() {}
	Factor(ll p, ll q) : p(p), q(q) {
		pw[0] = 1;
		for (int i = 1; i <= q; ++i) {
			pw[i] = pw[i - 1] * p;
		}
	}	
};
const ll INF = 1LL << 60;
const ll MAX = 700000000LL * 500000LL;
const ll MAX2 = 18708286 + 10;  // sqrt(MAX)
const int MAXP = 1193609; // number of primes <= MAX2
bool Mark[MAX2]; // sieve
int P[MAXP+1], NP; // prime numbers
Factor F[100];
int NF;
ll A, B, C; // current optimal solution
ll S, R; // radius and squad

bool CheckSquad(ll a, ll b, ll c, ll s) {
	ll p = (a + b + c);
	if (p & 1) return false;
	p >>= 1;
	ll s2 = p * (p - a) * (p - b) * (p - c);
	return s * s == s2;
}	


void GeneratePrimes() {
	for (int i = 2; i * i <= MAX2; ++i) {
		if (Mark[i]) continue;
		for (int j = i * i; j <= MAX2; j += i) {
			Mark[j] = true;
		}
	}
	for (int i = 2; i <= MAX2; ++i) {
		if (!Mark[i]) {
			P[NP++] = i;
		}
	}
}

void Factorize(ll x) {
	NF = 0;
	for (int i = 0; i < NP; ++i) {
		ll p = P[i];
		if (p * p > x) break;
		int c = 0;
		while (x % p == 0) {
			x /= p;
			++c;
		}
		if (c) {
			F[NF++] = Factor(p, c);
		}
	}
	if (x > 1) {
		F[NF++] = Factor(x, 1);
	}
}

void Check(ll a, ll b, ll c) {
	if (a > b) swap(a, b);
	if (b > c) swap(b, c);
	if (a > b) swap(a, b);
	if (c < a + b && CheckSquad(a, b, c, S)) {		
		if (a < A || (a == A && b < B) || (a == A && b == B && c < C)) {
			A = a;
			B = b;
			C = c;			
		}
	}
}

void Rec(int k, ll a, ll b, ll c) {
	if (a >= 40001 || b >= 40001 || c >= 40001) return;
	if (k == NF) {
		Check(a, b, c);		
	} else {
		int q = F[k].q;
		ll p = F[k].p;
		for (int i = 0; i <= q; ++i) {
			for (int j = 0; j <= q - i; ++j) {
				int l = q - i - j;
				Rec(k + 1, a * F[k].pw[i], b * F[k].pw[j], c * F[k].pw[l]);
			}
		}
	}
}

void Calc(ll x) {
	A = B = C = INF;
	NF = 0;
	Factorize(x);
	Rec(0, 1, 1, 1);
	if (A == INF) {
		puts("-1 -1 -1");
	} else {
		cout << A << " " << B << " " << C << endl;
	}
}

bool Solve() {
	cin >> R >> S;
	if (!R && !S) return false;
	Calc(R * S * 4);
	return true;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
//	freopen("out1", "w", stdout);
#endif		
	GeneratePrimes();
	while (Solve());
	return 0;
}
