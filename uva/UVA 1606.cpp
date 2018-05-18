/*
	Geometry problem with sorting by angle technique and rotating divider line.
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

const ld PI = acos(-1);
const ld EPS = 1e-10;

ld Abs(ld a) { return a > 0 ? a : - a; }
bool Eq(ld a, ld b) { return Abs(a - b) <= EPS; }
bool Le(ld a, ld b) { return Eq(a, b) || a <= b; }
bool Lt(ld a, ld b) { return !Eq(a, b) && a < b; }
int Sgn(ld a) { return Eq(a, 0) ? 0 : (a > 0 ? 1 : -1); }

struct Point {
	ld x, y;
	ld a, d;	
	int c0, c1;
	int s0, s1;
	Point(ld x = 0, ld y = 0) : x(x), y(y) {}
};
typedef vector<Point> vp;

inline Point operator +(const Point &p1, const Point &p2) { return Point(p1.x + p2.x, p1.y + p2.y); }
inline Point operator -(const Point &p1, const Point &p2) { return Point(p1.x - p2.x, p1.y - p2.y); }
inline ld Vect(Point p1, Point p2) { return p1.x * p2.y - p1.y * p2.x; }
inline int SVect(Point p1, Point p2) { return Sgn(Vect(p1, p2)); }
inline ld Dist(Point p) { return sqrt(p.x * p.x + p.y * p.y); }

inline ld Angle(Point p) {
	ld a = atan2(p.y, p.x);
	if (Eq(a, 0)) a = 0;
	if (a < 0) a += 2 * PI;
	return a;
}

bool operator <(const Point &p1, const Point &p2) {
	if (Eq(p1.a, p2.a)) {
		return p1.d < p2.d;
	}
	return p1.a < p2.a;
}

int Get0(vp &v, int i, int k) {
	if (i <= k) {
		return v[k].s0 - (i - 1 >= 0 ? v[i - 1].s0 : 0);
	} else {
		int nv = sz(v);
		return v[k].s0 + v[nv - 1].s0 - (i - 1 >= 0 ? v[i - 1].s0 : 0);
	}
}
int Get1(vp &v, int i, int k) {
	if (i <= k) {
		return v[k].s1 - (i - 1 >= 0 ? v[i - 1].s1 : 0);
	} else {
		int nv = sz(v);
		return v[k].s1 + v[nv - 1].s1 - (i - 1 >= 0 ? v[i - 1].s1 : 0);
	}
}

Point Q[2000];
int N;

vp BuildV() {
	vp v;
	int i = 2;
	while (i <= N) {
		int j = i;
		int c0 = 0, c1 = 0;
		while (j <= N && Eq(Q[i].a, Q[j].a)) {
			c0 += Q[j].c0;
			c1 += Q[j].c1;
			++j;
		}
		Point p = Q[i];
		p.c0 = c0;
		p.c1 = c1;
		v.pb(Point(p));
		i = j;
	}
	return v;
}

Point P[2000];
int Calc(int p) {
	rep (i, 1, N) {
		Q[i] = P[i];
	}
	swap(Q[p], Q[1]);
	Point O = Q[1];
	rep (i, 2, N) {
		Q[i].a = Angle(Q[i] - O);
		Q[i].d = Dist(Q[i] - O);
	}	
	sort(Q + 2, Q + N + 1);
	vector<Point> v = BuildV();		
	int nv = sz(v);
	v[0].s0 = v[0].c0;
	v[0].s1 = v[0].c1;
	rep (i, 1, nv - 1) {
		v[i].s0 = v[i - 1].s0 + v[i].c0;
		v[i].s1 = v[i - 1].s1 + v[i].c1;
	}
	int s0 = v[nv - 1].s0;
	int s1 = v[nv - 1].s1;
	int j = 1;
	int mx = 0;
	rep (i, 0, nv - 1) {
		while (i != j) {
			int s = SVect(v[i] - O, v[j] - O);
			if (s < 0) {
				break;
			}
			j = (j + 1) % nv;
		}
		int k = (j - 1 + nv) % nv;
		int x0 = Get0(v, i, k);
		int x1 = Get1(v, i, k);
		int y0 = s0 - x0;
		int y1 = s1 - x1;
		int c0 = v[i].c0;
		int c1 = v[i].c1;
		if (i != k && SVect(v[i] - O, v[k] - O) == 0) {
			c0 += v[k].c0;
			c1 += v[k].c1;
		} 
		x0 -= c0;
		x1 -= c1;
		int val1 = x0 + y1 + c0 + c1;
		int val2 = x1 + y0 + c0 + c1;
		mx = max(mx, val1);
		mx = max(mx, val2);
	}
	return mx + 1;
}

bool Solve() {
	scanf("%d", &N);
	if (!N) return false;
	rep (i, 1, N) {
		int t;
		cin >> P[i].x >> P[i].y >> t;
		if (t) {
			P[i].c0 = 0;
			P[i].c1 = 1;
		} else {
			P[i].c0 = 1;
			P[i].c1 = 0;
		}
	}
	
	int ans = 0;
	if (N <= 3) {
		ans = N;
	} else {
		rep (i, 1,N) {
			int cur = Calc(i);
			ans = max(ans, cur);
		}		
	}
	cout << ans << endl;
	return true;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
#endif	
	while (Solve());
	return 0;
}
