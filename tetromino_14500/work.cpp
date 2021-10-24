#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>

#define pii pair< int, int>
#define INF 987654321

using namespace std;

int N, M;
int map[500][500];
bool visited[500][500];

int maxValue;
#define numOfDir 4
#define numOfCnt 4

int dy[numOfDir] = { -1, 1, 0, 0 };
int dx[numOfDir] = { 0, 0, -1, 1 };

bool checkRange(int y, int x) {
	return (y < 0 || y >= N || x < 0 || x >= M);
}

void dfs(int y, int x, int sum, int cnt)
{
	int newY, newX;
	if (cnt == numOfCnt) {
		maxValue = max(maxValue, sum);
		return;
	}

	for (int i = 0; i < numOfDir; i++) {
		newY = y + dy[i];
		newX = x + dx[i];
		if (checkRange(newY, newX) || visited[newY][newX]) continue;
		visited[newY][newX] = true;
		dfs(newY, newX, sum + map[newY][newX], cnt + 1);
		visited[newY][newX] = false;
	}
}

void additionalFunc(int y, int x)
{
	int sum = map[y][x];
	int minValue = INF;
	int newY, newX;
	int cnt = 0;
	for (int i = 0; i < numOfDir; i++) {
		newY = y + dy[i];
		newX = x + dx[i];
		if (checkRange(newY, newX)) continue;
		cnt++;
		sum += map[newY][newX];
		minValue = min(minValue, map[newY][newX]);
	}
	if (cnt == 3) {
		maxValue = max(maxValue, sum);
	}
	else if (cnt == 4) {
		maxValue = max(maxValue, sum - minValue);
	}
}

void solve()
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			visited[i][j] = true;
			dfs(i, j, map[i][j], 1);
			visited[i][j] = false;
			additionalFunc(i, j);
		}
	}

}

int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	solve();
	cout << maxValue << endl;
}