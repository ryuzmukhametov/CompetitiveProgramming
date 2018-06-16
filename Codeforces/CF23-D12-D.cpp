/*
	Use points reflection.
	http://codeforces.com/blog/entry/530
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
#define sz(x) ((x).size())
#define out(x)  cout<<#x<<"="<<(x)<<"\n"
#define LL "%lld" //%I64d 
typedef long double ld;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii > vpii;
typedef vector<string > vs;
typedef pair<double,double> pdd;

struct Point {
	Point() {}
	Point(ld x, ld y) : x(x), y(y) {}
	ld x, y;
};
const ld EPS = 1e-10;
inline ld Abs(ld a) { return a > 0 ? a : -a; }
inline bool Eq(ld a, ld b) {return Abs(a - b) <= EPS; }
inline int Sgn(ld a) { return Eq(a, 0) ? 0 : (a > 0 ? 1 : -1); }
inline Point operator +(const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
inline Point operator -(const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
inline Point operator *(const Point &a, ld b) { return Point(a.x * b, a.y * b); }
inline Point Normal(Point p) { return Point(p.y, -p.x); }
inline ld Vect(Point a, Point b) { return a.x * b.y - a.y * b.x; }
inline int SVect(Point a, Point b) { return Sgn(Vect(a, b)); }
inline ld Dist(Point a) { return sqrt(a.x * a.x + a.y * a.y); }

inline Point Reflect(Point p1, Point p2) {
	return p1 + (p2 - p1) * 2;
}

Point ReadPoint() {
	int x, y;
	scanf("%d %d", &x, &y);
	return Point(x, y);
}

bool Convex(Point p[], int n) {
	int c1 = 0, c2 = 0;
	rep (i, 0, n - 1) {
		int j = (i + 1) % n;
		int k = (j + 1) % n;
		int s = SVect(p[j] - p[i], p[k] - p[i]);
		if (s == 0) return false;
		if (s > 0) c1++;
		else c2++;
		if (c1 && c2) return false;
	}
	return true;
}

bool Middle(Point a, Point b, Point c) {
	Point p = (a + b) * 0.5;
	return Eq(p.x, c.x) && Eq(p.y, c.y);
}

bool CrossLines(Point p1, Point p2, Point p3, Point p4, Point &p) {
	ld t1 = Vect(p3 - p1, p4 - p1);
	ld t2 = Vect(p2 - p1, p4 - p3);
	if (Eq(t2, 0)) return false;
	ld t = t1 / t2;
	p = p1 + (p2 - p1) * t;
	return true;
}

bool Center(Point p1, Point p2, Point p3, Point &p) {
	Point p12 = (p1 + p2) * 0.5;
	Point p13 = (p1 + p3) * 0.5;
	Point q12 = p12 + Normal(p2 - p1);
	Point q13 = p13 + Normal(p3 - p1);
	if (!CrossLines(p12, q12, p13, q13, p)) return false;
	return true;
}

bool Check(Point b, Point c, Point m[3]) {
	Point a = Reflect(b, m[0]);
	Point d = Reflect(c, m[2]);
	Point p[4];
	p[0] = a; p[1] = b; p[2] = c; p[3] = d;
	if (!Convex(p, 4)) return false;
	ld ab = Dist(a - b);
	ld bc = Dist(b - c);
	ld cd = Dist(c - d);
	if (!Eq(ab, bc)) return false;
	if (!Eq(bc, cd)) return false;
	if (!Middle(a, b, m[0])) return false;
	if (!Middle(b, c, m[1])) return false;
	if (!Middle(c, d, m[2])) return false;
	puts("YES");
	rep (i, 0, 3) {
		double x = p[i].x, y = p[i].y;
		printf("%0.12lf %0.12lf ", x, y);
	}
	printf("\n");
	return true;
}

void Solve() {
	Point q[3];
	int pe[3];
	rep (i,0,2) {
		q[i] = ReadPoint();
		pe[i] = i;
	} 
	do {
		Point m[3];
		rep (i,0,2) {
			m[i] = q[pe[i]];
		}
		Point b, c;
		Point q1 = Reflect(m[2], m[1]);
		if (!Center(q1, m[0], m[1], b)) continue;		
		Point q2 = Reflect(m[0], m[1]);
		if (!Center(q2, m[2], m[1], c)) continue;
		if (Check(b, c, m)) {
			return;
		}
	} while (next_permutation(pe, pe + 3));
	puts("NO\n");
}


int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	//freopen("out1", "w", stdout);
#endif		
	int n;
	cin >> n;
	while (n--) Solve();
	return 0;
}
