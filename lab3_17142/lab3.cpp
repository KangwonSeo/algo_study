#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>

#define INF 987654321

using namespace std;
int N, M;
int A[50][50];
int vCnt;
struct Point {
	int x, y, z;
};
Point v[10];

int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};

int maskCount(int mask) {
	int cnt=0;
	while (mask) {
		if (mask & 1) cnt++;
		mask = mask >> 1;
	}
	return cnt;
}

int solve() {
	int ret = INF;
	for (int mask = 0; mask < (1 << vCnt); mask++) {
		if (maskCount(mask) == M) {
			int dist = 0;
			bool visited[50][50] = { false };
			queue<Point> myQ;
			for (int i = 0; i < vCnt; i++) {
				if (mask & (1 << i)) {
					visited[v[i].y][v[i].x] = true;
					myQ.push(v[i]);
				}
			}
			while (!myQ.empty()) {
				Point parent = myQ.front();
				myQ.pop();
				if (A[parent.y][parent.x] != 2)
					dist = max(dist, parent.z );
				for (int i = 0; i < 4; i++) {
					int y = parent.y + dy[i];
					int x = parent.x + dx[i];
					if (y < 0 || x < 0 || y > N - 1 || x > N - 1)
						continue;
					if ((A[y][x] == 1) || visited[y][x])
						continue;
					visited[y][x] = true;
					myQ.push({ x, y, parent.z + 1 });

				}
			}
			bool flag = true;
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++) {
					if (A[i][j] == 0 && visited[i][j] == false) {
						flag = false;
					}
				}
			if (flag)
				ret = min(ret, dist);
		}
	}
	if (ret == INF) return -1;

	return ret;
}

int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> A[i][j];
			if (A[i][j] == 2)
				v[vCnt++] = { j, i  };
		}
	}
	cout << solve() << endl;
}