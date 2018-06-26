/*
	http://codeforces.com/blog/entry/46786?locale=ru
	According to link the answer is number of odd divisors of n!.
	To find it factorize n! by prime numbers. To speed up split that 
	process on two parts: before sqrt(n) and after after sqrt(n).
*/
#include <vector>
#include <map>
#include <set>
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
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
const ll INF = 1LL << 60;
const int MAX = 1000*1000*100;
bool Use[MAX+1];
int P[6000000], NP;

void Sieve() {
	int hi = MAX;
	for (int i = 2; i * i <= hi; ++i) {
		if (Use[i]) continue;
		for (int j = i * i; j <= hi; j += i) {
			Use[j] = true;
		}
	}
	for (int i = 3; i <= hi; ++i) {
		if (!Use[i]) P[NP++] = i;
	}
}

ll PowFactorial(ll n, ll p) {
	ll r = 0;
	ll c = p;
	while (n / c > 0) {
		r += n / c;
		c *= p;
	}
	return r;
}

ll PosOfLastPrime(int n) {	
	ll lo = 0, hi = NP;
	P[hi] = 1 << 30;
	while (lo < hi) {
		ll mid = (lo + hi) >> 1;
		if (P[mid] > n) hi = mid;
		else lo = mid + 1;
	}
	return lo - 1;
}

ll Pow(ll a, ll n, ll	 m) {
	if (!n) return 1;
	if (n & 1) return Pow(a, n - 1, m) * a % m;
	ll x = Pow(a, n >> 1, m);
	return x * x % m;
}

ll Count(int lo, int hi) {
	int r = PosOfLastPrime(hi);
	int l = PosOfLastPrime(lo - 1);
	return r - l;
}

ll DivCount(int n, int m) {
	ll r = 1;
	ll t = n;
	for (ll c = 1; true; ++c) {		
		ll lo = n / (c + 1) + 1, hi = n / c;		
		if (lo * lo <= n || lo > hi) {
			break;
		}
		ll cnt = Count(lo, hi);
		t = lo - 1;
		r *= Pow(c+1, cnt, m);
		r %= m;	
		if (lo == 1) {
			return r;
		}		
	}

	for (int i = 0; i < NP; ++i) {
		ll p = P[i];
		if (p > t) {
			break;
		}		
		ll c = PowFactorial(n, p);		
		r *= (c + 1);
		r %= m;			
	} 
	return r;
}

void Solve(int n, int m) {
	ll d = DivCount(n, m);
	//out(d);
	int ans = (d - 1 + m) % m;
	//printf("n=%d %d %d\n", n, ans, brute(n));
	printf("%d\n", ans);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	//freopen("out2", "w", stdout);
#endif		
	Sieve();
	int tst;
	scanf("%d", &tst);
	while (tst--) {
		int n = 1000*1000*100, m = 10000;
		//n = 100000000;
		scanf("%d %d", &n, &m);
		Solve(n, m);
	}
	return 0;
}
