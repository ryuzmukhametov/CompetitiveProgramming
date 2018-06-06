/*
	To solve the problem need to implement algorithm of checking intersection of two segments.
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

const ld EPS = 1e-10;
ld Abs(ld a) { return a > 0 ? a : -a; }
bool Eq(ld a, ld b) { return Abs(a - b) <= EPS; }

struct Point {
	ld x, y;
	Point() {}
	Point(ld x, ld y) : x(x), y(y) {}
};

Point operator +(const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator -(const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator *(const Point &a, ld x) { return Point(a.x * x, a.y * x); }
ld Vect(Point a, Point b) {return a.x * b.y - a.y * b.x; }
int Sgn(ld a) { return Eq(a, 0) ? 0 : (a > 0 ? 1 : -1); }
ld SVect(Point a, Point b) { return Sgn(Vect(a, b)); }
Point Normal(Point p) { return Point(p.y, -p.x); }

struct Item {
	vector<Point> p;
	char ch;
};

bool Cross(ld x1, ld x2, ld x3, ld x4) {
	if (x1 > x2) swap(x1, x2);
	if (x3 > x4) swap(x3, x4);
	return (x1 <= x4 && x3 <= x2);
}

bool CrossSegments(Point p1, Point p2, Point p3, Point p4) {
	return
		SVect(p2 - p1, p3 - p1) * SVect(p2 - p1, p4 - p1) <= 0 &&
		SVect(p4 - p3, p1 - p3) * SVect(p4 - p3, p2 - p3) <= 0 &&		
		Cross(p1.x, p2.x, p3.x, p4.x) &&
		Cross(p1.y, p2.y, p3.y, p4.y);
}

bool Check(Item &a, Item &b) {
	vector<Point> pa = a.p, pb = b.p;
	int na = sz(pa), nb = sz(pb);
	rep (i, 0, na - 1) {
		int ni = (i + 1) % na;
		rep (j, 0, nb - 1) {
			int nj = (j + 1) % nb;
			if (CrossSegments(pa[i], pa[ni], pb[j], pb[nj])) {
				return true;
			}
		}
	}
	return false;
}

Point ReadPoint() {
	int x, y;
	char s[30];
	scanf("%s", s);
	int p = 0;
	while (s[p]) {if (s[p]=='('||s[p]==')'||s[p]==',') s[p]=' '; p++;}
	sscanf(s, "%d %d", &x, &y);
	return Point(x, y);
}

void ReadSquare(vector<Point> &p) {
	Point p1 = ReadPoint();	
	Point p3 = ReadPoint();
	Point o = (p1 + p3) * 0.5;
	Point n = Normal(p1 - p3);
	Point p2 = o + n * 0.5;
	Point p4 = o - n * 0.5;
	p.pb(p1); p.pb(p2); p.pb(p3); p.pb(p4);
}

void ReadRect(vector<Point> &p) {
	Point p1 = ReadPoint();
	Point p2 = ReadPoint();
	Point p3 = ReadPoint();
	Point o = (p1 + p3) * 0.5;
	Point p4 = p2 + (o - p2) * 2;
	p.pb(p1); p.pb(p2); p.pb(p3); p.pb(p4);
}

void ReadLine(vector<Point> &p) {
	Point p1 = ReadPoint();
	Point p2 = ReadPoint();
	p.pb(p1); p.pb(p2);
}

void ReadTriangle(vector<Point> &p) {
	Point p1 = ReadPoint();
	Point p2 = ReadPoint();
	Point p3 = ReadPoint();
	p.pb(p1); p.pb(p2);	p.pb(p3);	
}

void ReadPolygon(vector<Point> &p) {
	int n;
	scanf("%d", &n);
	while (n--) {
		Point p1 = ReadPoint();	
		p.pb(p1);
	}
}

bool Solve() {
	char ch;
	cin >> ch;
	if (ch == '.') return false;
	char s[100];
	Item it;
	vector<Item> v;
	while (true) {
		if (ch == '-') break;
		scanf("%s", s);
		vector<Point> p;
		if (s[0] == 's') {
			ReadSquare(p);
		}
		if (s[0] == 'r') {
			ReadRect(p);	
		}
		if (s[0] == 'l') {
			ReadLine(p);	
		}
		if (s[0] == 't') {
			ReadTriangle(p);
		}
		if (s[0] == 'p') {
			ReadPolygon(p);	
		}
		it.ch = ch;
		it.p = p;
		v.pb(it);
		cin >> ch;
	}
	int nv = sz(v);
	map<char, vector<char> > ans;
	rep (i, 0, nv - 1) {
		char cv = v[i].ch;
		vector<char> u;
		rep (j, 0, nv - 1) {
			if (i == j) continue;
			if (Check(v[i], v[j])) {
				u.pb(v[j].ch);
			}
		}		
		sort(u.begin(), u.end());
		ans[cv] = u;
	}

	for (map<char, vector<char> >::iterator it = ans.begin(); it != ans.end(); ++it) {
		char cv = it->first;
		vector<char> u = it->second;
		int nu = sz(u);
		if (nu == 0) {
			printf("%c has no intersections", cv);
		} else if (nu == 1) {
			printf("%c intersects with %c", cv, u[0]);
		} else if (nu == 2) {
			printf("%c intersects with %c and %c", cv, u[0], u[1]);
		} else {
			printf("%c intersects with ", cv);
			rep (k, 0, nu - 1) {
				char cu = u[k];
				//A, B, . . ., and Z", cv);
				if (k < nu - 1) printf("%c, ", cu);
				else printf("and %c", cu);
			}			
		}
		printf("\n");
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
