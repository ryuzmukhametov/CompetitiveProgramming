/*
	Use standard Bellman-Ford algo over WxH grid. 
	Should not relax from finish vertex.
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

struct Item {
	int x1, y1, x2, y2, t;
	Item(int x1, int y1, int x2, int y2, int t) : x1(x1), y1(y1), x2(x2), y2(y2), t(t) {}
};
const ll INF = 1LL << 60;	
int W, H;
ll D[100][100];
int G[100][100];
int Mark[100][100];
vector<Item> E;
int NG, NE;

bool Relax(int x1, int y1, int x2, int y2, int t, bool h) {
	if (x1 < 0 || x1 >= W) return false;
	if (x2 < 0 || x2 >= W) return false;
	if (y1 < 0 || y1 >= H) return false;
	if (y2 < 0 || y2 >= H) return false;
	if (D[x1][y1] == INF) return false;
	if (x1 == W - 1 && y1 == H - 1) return false;
	if (G[x1][y1]) return false;
	if (G[x2][y2]) return false;
	if (!h && Mark[x1][y1]) return false;
	if (D[x2][y2] > D[x1][y1] + t) {
		D[x2][y2] = D[x1][y1] + t;
		return true;
	} else {
		return false;
	}
}

const int DI[] = {-1, 0, 1, 0};
const int DJ[] = {0, -1, 0, 1};

bool Solve() {
	scanf("%d %d", &W, &H);
	if (!W && !H) return false;
	rep (i, 0, W - 1) {
		rep (j, 0, H - 1) {
			D[i][j] = INF;
			G[i][j] = 0;
			Mark[i][j] = 0;
		}
	}
	scanf("%d", &NG);
	rep (i, 1, NG) {
		int x, y;
		scanf("%d %d", &x, &y);
		G[x][y] = 1;
	}
	scanf("%d", &NE);
	E.clear();
	rep (i, 1, NE) {
		int x1, y1, x2, y2, t;
		scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &t);
		E.pb(Item(x1, y1, x2, y2, t));
		Mark[x1][y1] = 1;
	}
	D[0][0] = 0;
	int cnt = W * H;
	bool last = false;
	while (cnt--) {
		bool relaxed = false;
		rep (i, 0, W - 1) {
			rep (j, 0, H - 1) {
				rep (k, 0, 3) {
					int ni = i + DI[k];
					int nj = j + DJ[k];
					relaxed |= Relax(i, j, ni, nj, 1, false);
				}
				
			}
		}
		for (Item it : E) {
			relaxed |= Relax(it.x1, it.y1, it.x2, it.y2, it.t, true);
		}
		last = relaxed;
		if (!relaxed) break;
	}
	if (last) {
		puts("Never");
		return true;
	}
	if (D[W - 1][H - 1] == INF) {
		puts("Impossible");
		return true;		
	}
	cout << D[W - 1][H - 1] << endl;
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
