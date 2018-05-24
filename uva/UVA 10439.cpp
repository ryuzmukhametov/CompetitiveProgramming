/*
	Firstly find center of circle over three given point (cross point of middle perpendiculars).
	Then find angles between OP1, OP2, OP3, where O is found center and P1, P2, P3 are given points.
	The next step is iteration over possible number of vertexes. Then we just check dividing of angles.
*/
#include <bits/stdc++.h>
using namespace std;
#define rep(i,lo,hi) for(ll i=(lo);i<=(ll)(hi);++i)
#define rev(i,hi,lo) for(ll i=(hi);i>=(ll)(lo);--i)
#define pb push_back
#define mp make_pair
#define sz(x) ((x).size())
#define out(x)  cout<<#x<<"="<<(x)<<"\n"
#define pout(p)  cout<<#p<<"=("<<(p.x)<<","<<p.y<<")\n"
#define vout(x) cout<<#x<<"={";for(auto v:x)cout<<v<<",";cout<<"}\n";
#define aout(x,lo,hi) cout<<#x<<"={";rep(i,lo,hi)cout<<x[i]<<",";cout<<"}\n";
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

const ld EPS = 1e-4;
const ld PI = acos(-1);
ld Abs(ld a) { return a > 0 ? a : -a; }
bool Eq(ld a, ld b) { return Abs(a - b) <= EPS; }
void Assert(bool x) { if (!x)puts("hmm"); }

struct Point {
	ld x, y;
	Point(){x=y=0;}
	Point(ld x, ld y) : x(x), y(y) {}
};

Point operator +(const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator -(const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator *(const Point &a, ld x) { return Point(a.x * x, a.y * x); }
Point Normal(Point p) { return Point(p.y, -p.x); }
ld Vect(Point a, Point b) { return a.x * b.y - a.y * b.x; }
ld Scal(Point a, Point b) { return a.x * b.x + a.y * b.y; }
ld Dist(Point a) { return sqrt(a.x * a.x + a.y * a.y); }

ld Angle(Point a, Point b) {
	ld s = Scal(a, b);
	ld v = Vect(a, b);
	return atan2(v, s);
}

Point CrossLines(Point p1, Point p2, Point p3, Point p4) {
	ld t1 = Vect(p3 - p1, p4 - p1);
	ld t2 = Vect(p2 - p1, p4 - p3);
	Assert(!Eq(t2, 0));
	ld t = t1 / t2;
	return p1 + (p2 - p1) * t;
}

Point Center(Point p1, Point p2, Point p3) {
	Point p12 = (p1 + p2) * 0.5;
	Point p13 = (p1 + p3) * 0.5;
	Point q12 = p12 + Normal(p2 - p1);
	Point q13 = p13 + Normal(p3 - p1);
	Point p = CrossLines(p12, q12, p13, q13);
	Assert(Eq(Dist(p-p1), Dist(p - p2)));
	Assert(Eq(Dist(p-p1), Dist(p - p3)));
	return p;
}

Point ReadPoint() {
	Point p;
	cin >> p.x >> p.y;
	return p;
}

bool Divide(ld a, ld b) {
	a = Abs(a); b = Abs(b);	
	ld t = fmod(a, b);
	bool res= Eq(t, 0) || Eq(t, b);
	return res;
}

void Solve() {
	Point p1, p2, p3;
	p1 = ReadPoint();
	p2 = ReadPoint();
	p3 = ReadPoint();
	Point p = Center(p1, p2, p3);
	ld a12 = Angle(p1 - p, p2 - p);
	ld a23 = Angle(p2 - p, p3 - p);
	ld a31 = Angle(p3 - p, p1 - p);
	for (int k = 3; k <= 200; ++k) {
		ld z = 2 * PI / k;
		if (Divide(a12, z) && Divide(a23, z) && Divide(a31, z)) {
			cout << k << endl;
			return;
		}
	}
	Assert(false);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
#endif	
	int tst;
	cin >> tst;
	while (tst--) {
		Solve();
	}
	return 0;
}
