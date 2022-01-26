#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <math.h>
#define pii pair< int, int>
#define INF 987654321

using namespace std;
int N, M, H;
int arr[30][10];
vector<pii> v;

bool check(void)
{
	for (int i = 0; i < N; i++) {
		int start = i;
		for (int j = 0; j < H; j++) {
			int d = 0;
			if (start < N - 1 && arr[j][start]) d += 1;
			if (start > 0 && arr[j][start - 1]) d -= 1;
			start += d;
		}
		if (start != i) return false;
	}
	return true;
}
bool possible(int r, int c)
{
	if ((c == 0 || !arr[r][c - 1]) &&
		(c == N - 2 || !arr[r][c + 1])) return true;
	else false;
}

int solve(int start, int cnt)
{
//	if (cnt > 3 || start == v.size()) return INF;
//	if (check()) return cnt;
	if (cnt == 3 || start == v.size()) {
		if (check()) return cnt;
		return INF;
	}
	int ret = INF;
	int r = v[start].first;
	int c = v[start].second;

	if (possible(r, c)) {
		arr[r][c] = 1;
		ret = solve(start + 1, cnt + 1);
	}
	arr[r][c] = 0;
	ret = min(ret, solve(start + 1, cnt));
	return ret;
}

int main()
{
	int res = 0;
	cin >> N >> M >> H;
	for (int i = 0; i < M; i++) {
		int r, c;
		cin >> r >> c;
		arr[r - 1][c - 1] = 1;
	}
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < N - 1; j++) {
			if (!arr[i][j]) v.push_back(make_pair(i, j));
		}
	}
	res = solve(0, 0);
	if (res == INF) cout << -1 << endl;
	else cout << res << endl;

}