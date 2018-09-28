// http://apps.topcoder.com/wiki/display/tc/SRM+577
#include <set>
#include <string.h>
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long lint;
typedef vector<int> vi;
typedef vector<string> vs;
const lint MOD = 1000*1000*1000+7;

struct Point {
	int x, y;
};
vector<Point> P;

inline int Abs(int x) {
	return x > 0 ? x : -x;
}

inline bool inside(int x1, int x2, int y1, int y2, Point p) {
	return x1 <= p.x && p.x <= x2 && y1 <= p.y && p.y <= y2;
}

inline int dist(int x1, int x2, int y1, int y2, Point p) {
	return max(max(Abs(x1 - p.x), Abs(x2 - p.x)), max(Abs(y1 - p.y), Abs(y2 - p.y)));
}

int dp[15][15][15][15];

int rec(int x1, int x2, int y1, int y2) {
	if (dp[x1][x2][y1][y2] != -1) return dp[x1][x2][y1][y2];
	int res = 1 << 30;
	for (int k = 0; k < P.size(); ++k) {
		if (inside(x1, x2, y1, y2, P[k])) {
			continue;
		}
		int x = P[k].x;
		int y = P[k].y;
		int nx1 = min(x1, x);
		int nx2 = max(x2, x);
		int ny1 = min(y1, y);
		int ny2 = max(y2, y);
		int cur = rec(nx1, nx2, ny1, ny2);
		for (int l = 0; l < P.size(); ++l) {
			if (inside(x1, x2, y1, y2, P[l])) {
				continue;
			}
			if (inside(nx1, nx2, ny1, ny2, P[l])) {
				cur += dist(nx1, nx2, ny1, ny2, P[l]);
			}	
		}
		res = min(res, cur);
	}
	return dp[x1][x2][y1][y2] = (res == 1 << 30 ? 0 : res);
}

int minCost(vs b) {	
	memset(dp, -1, sizeof(dp));
	P.clear();
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (b[i][j] == '#') {
				int x = i - j + 7;
				int y = i + j;
				Point p;
				p.x = x;
				p.y = y;
				P.push_back(p);				
			}
		}
	}
	int ans = 1 << 30;
	for (int k = 0; k < P.size(); ++k) {
		int x = P[k].x;
		int y = P[k].y;
		int cur = rec(x, x, y, y);	
		ans = min(ans, cur);
	}		
	return ans == 1 << 30 ? 0 : ans;
}

class EllysChessboard {
public:
	int minCost(vector <string> board) {
		return ::minCost(board);
	}
};

