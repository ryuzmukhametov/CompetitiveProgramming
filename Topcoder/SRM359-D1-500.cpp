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
int K;
int A[100], P[100];
double Total;
const ld EPS = 1e-11;

struct Point {
	ld x, y;
	Point(ld x = 0, ld y = 0) : x(x), y(y) {}
};

inline ld Abs(ld a) { return a > 0 ? a : -a; }
inline bool Eq(ld a, ld b) { return Abs(a - b) <= EPS; }
Point operator +(const Point &p1, const Point &p2) { return Point(p1.x + p2.x, p1.y + p2.y); }
Point operator -(const Point &p1, const Point &p2) { return Point(p1.x - p2.x, p1.y - p2.y); }
Point operator *(const Point &p1, ld v) { return Point(p1.x * v, p1.y * v); }
inline ld Vect(Point p1, Point p2) { return p1.x * p2.y - p1.y * p2.x; }
inline ld Dist(Point p) { return sqrt(p.x * p.x + p.y * p.y); }

Point Normal(Point p) {
	return Point(p.y, -p.x);
}

bool Cross(Point p1, Point p2, Point p3, Point p4, Point &p) {
	ld v2 = Vect(p2 - p1, p4 - p3);
	if (Eq(v2, 0)) return false;
	ld v1 = Vect(p3 - p1, p4 - p1);
	p =  p1 + (p2 - p1) * (v1 / v2);
	return true;
}

bool Center(Point p1, Point p2, Point p3, Point &p) {
	Point p12 = (p1 + p2) * 0.5;
	Point p13 = (p1 + p3) * 0.5;
	Point q12 = p12 + Normal(p2 - p1);
	Point q13 = p13 + Normal(p3 - p1);
	return Cross(p12, q12, p13, q13, p);	
}


bool Contains(vector<pair<Point, ld> > &v, Point p, ld r) {
	int n = sz(v);
	rep (i, 0, n - 1) {
		pair<Point, ld> cur = v[i];
		Point q = cur.first;
		if (Eq(q.x, p.x) && Eq(q.y, p.y) && Eq(cur.second, r)) {
			return true;
		}
	}
	return false;
}

struct Item {
	ld x, y, z;
};

bool operator <(const Item &a, const Item &b) {
	if (!Eq(a.x, b.x)) return a.x < b.x;
	if (!Eq(a.y, b.y)) return a.y < b.y;
	if (!Eq(a.z, b.z)) return a.z < b.z;
	return false;
}

int Calc(int x[], int y[], int n) {
	set<Item> s;
	rep (i, 0, n - 1) {
		rep (j, i + 1, n - 1) {
			rep (k, j + 1, n - 1) {
				Point p1(x[i], y[i]);
				Point p2(x[j], y[j]);
				Point p3(x[k], y[k]);
				Point p;
				if (Center(p1, p2, p3, p)) {					
					ld r = Dist(p - p1);
					Item val;
					val.x = p.x;
					val.y = p.y;
					val.z = r;
					s.insert(val);					
				}
			}
		}
	}
	return sz(s);
}

char S[1000];
int X[100], Y[100], N, Ans;
bool ReadLine() {
	if (scanf("%s", S) == EOF) {
		return false;
	}

	for (int i = 0; S[i]; ++i) {
		if (S[i] == ',') {
			S[i] = ' ';
		}
	}

	string s(S);
	stringstream sin(S);
	int t;
	vi v;
	while (sin >> t) {
		v.pb(t);		
	}
	int n = sz(v) / 2;
	rep (i, 0, n - 1) {
		X[i] = v[i];
		Y[i] = v[i + n];
	}
	N = n;
	Ans = v.back();
	return true;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
#endif	
	while (1) {
		bool eof = !ReadLine();
		if (eof) break;
		int res = Calc(X, Y, N);
		if (Ans == res) cout << "passed" << endl;
		else cout << "wrong" << endl;
	}	

	return 0;
}
