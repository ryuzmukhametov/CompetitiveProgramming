/*
	On each step we pick such an ant and an apple point that on each side of line connected
	these point we have same number of ants and colonies. Apply such approach recursively.
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

struct Point {
	Point() {}
	Point(ll x, ll y) : x(x), y(y) {}
	ll x, y;
	int p;	
};
typedef vector<Point> vp;

inline Point operator -(const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }

inline ll Vect(Point &a, Point &b) {
	return a.x * b.y - a.y * b.x;
}

inline bool Check(Point p, Point q) {
	return Vect(p, q) > 0;
}

int O[500];

void Link(int p1, int p2) {
	O[p1] = p2;
}

void Divide(vp &v1, vp &v2) {
	int nv = sz(v1);
	rep (i, 0, nv - 1) {
		rep (j, 0, nv - 1) {
			int c1 = 0, c2 = 0;
			Point p = v2[j] - v1[i];
			Point o = v1[i];
			rep (k, 0, nv - 1) {
				if (k != i && Check(p, v1[k]-o)) ++c1;
				if (k != j && Check(p, v2[k]-o)) ++c2;
			}
			if (c1 == c2) {
				Link(v1[i].p, v2[j].p);
				vp u1, u2; // checked
				vp w1, w2; // !checked
				rep (k, 0, nv - 1) {
					if (i != k) {
						if (Check(p, v1[k]-o)) {
							u1.pb(v1[k]);
						} else {
							w1.pb(v1[k]);
						}				
					}
					
					if (j != k)	{
						if (Check(p, v2[k]-o)) {
							u2.pb(v2[k]);
						} else {
							w2.pb(v2[k]);
						}						
					}
				}
				Divide(u1, u2);
				Divide(w1, w2);
				return;
			}
		}
	}
}

void Read(int n, vp &v) {
	rep (i, 0, n - 1) {
		int x, y;
		scanf("%d %d", &x, &y);
		Point p(x, y);
		p.p = i;
		v.pb(p);
	}
}


bool Solve() {
	int n;
	if (scanf("%d", &n) == EOF) return false;	
	vp v1, v2;
	Read(n, v1);
	Read(n, v2);
	Divide(v1, v2);
	for (int i = 0; i < n; ++i) {
		printf("%d\n", O[i] + 1);
	}
	printf("\n");
	return true;
}


int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	//freopen("out1", "w", stdout);
#endif		
	while (Solve());
	return 0;
}
