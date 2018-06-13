/*
	https://www.hackerrank.com/challenges/meeting-point/editorial
*/
#include <vector>
#include <map>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
#define rep(i,lo,hi) for(ll i=(lo);i<=(ll)(hi);++i)
#define rev(i,hi,lo) for(ll i=(hi);i>=(ll)(lo);--i)
#define pb push_back
#define mp make_pair
#define sz(x) ((x).size())
#define out(x)  cout<<#x<<"="<<(x)<<"\n"
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

ll Abs(ll x) { return x > 0 ? x : -x; }

struct Point {
	ll x, y;
	ll d[2];
	ll s[2];
};

int N, I;
Point P[1 << 17];

bool operator <(const Point &a, const Point &b) {
	return a.d[I] < b.d[I];
}

void Calc(int p) {
	ll s = 0;
	rep (i, 2, N) {
		s += Abs(P[i].d[p] - P[1].d[p]);
	}
	P[1].s[p] = s;
	rep (i, 2, N) {
		ll t = P[i].d[p] - P[i - 1].d[p];
		s += t * (i - 1);
		s -= t * (N - i + 1);
		P[i].s[p] = s;
	}
}

void Solve() {
	scanf("%d", &N);
	rep (i, 1, N) {
		int x, y;
		scanf("%d %d", &x, &y);
		P[i].x = x;
		P[i].y = y;
		P[i].d[0] = x + y;
		P[i].d[1] = x - y;
	}
	for (I = 0; I < 2; ++I) {
		sort(P + 1, P + N + 1);
		Calc(I);	
	}
	ll ans = 1LL << 60;
	rep (i, 1, N) {
		ll t = P[i].s[0] + P[i].s[1];
		t /= 2;
		ans = min(ans, t);
	}
	cout << ans << endl;	
}


int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	//freopen("out1", "w", stdout);
#endif		
	Solve();
	return 0;
}
