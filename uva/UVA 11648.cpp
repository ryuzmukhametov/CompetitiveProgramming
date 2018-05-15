/*
	The solutions uses binary search and formula of trapezium by four sides.	
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

const ld EPS = 1e-11;
inline ld Sqr(ld x) { return x * x; }
inline ld Squad(ld a, ld b, ld c, ld d) {
	ld t1 = c*c - Sqr(   (Sqr(b-a)+c*c-d*d) / (2*(a-b)) );
	ld t2 = (a + b) / 2;
	return sqrt(t1) * t2; 
}

void Calc(int tst, ld a, ld b, ld c, ld d) {
	ld lo = 0, hi = 1;
	ld sq = Squad(a, b, c, d);
	ld ab2 = (a + b) / 2;
	ld h = sq / ab2;
	
	rep (i, 0, 10000) {
		ld alpha = (lo + hi) / 2.;
		ld h1 = h * alpha;
		ld ab = b + (a - b) * alpha;
		ld s1 = (b + ab) * h1 / 2;
		ld s = sq;
		if (2 * s1 <= s) {
			lo = alpha;
		} else {
			hi = alpha;
		}
	}
	double x = (1 - lo) * c;
	double y = (1 - lo) * d;
	printf("Land #%d: %0.12lf %0.12lf\n", tst, x, y);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif
	int tst;
	cin >> tst;
	rep (i, 1, tst) {
		ld a, b, c, d;
		cin >> a >> b >> c >> d;
		Calc(i, a, b, c, d);
	}
	return 0;
}