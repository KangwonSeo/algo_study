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

#define VIRUS 2
#define WALL 1
#define EMPTY 0

using namespace std;
typedef int mapType[8][8];

int N, M;

int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };

queue<pii> virusQ;
vector<pii> emptyVector;

bool invalidRange(int y, int x)
{
	return (y < 0 || y >= N || x < 0 || x >= M);
}
int countEmpty(mapType map)
{
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == EMPTY) cnt++;
		}
	}
	return cnt;
}

int bfs(mapType map_org)
{
	mapType map;
	memcpy(map, map_org, sizeof(map));
	queue<pii> q = virusQ;
	while (!q.empty()) {
		pii virus = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int newY = virus.first + dy[i];
			int newX = virus.second + dx[i];
			if (invalidRange(newY, newX)) continue;
			if (map[newY][newX] == EMPTY) {
				map[newY][newX] = VIRUS;
				q.push(make_pair(newY, newX));
			}
		}
	}
	return countEmpty(map);
}

int makeWall(mapType map, int start, int cnt)
{
	int ret;
	if (cnt == 3) {
		return bfs(map);
	}
	if (start >= emptyVector.size()) return 0;

	map[emptyVector[start].first][emptyVector[start].second] = WALL;
	ret = makeWall(map, start + 1, cnt + 1);
	map[emptyVector[start].first][emptyVector[start].second] = EMPTY;
	return max(ret, makeWall(map, start + 1, cnt));
}

int main()
{
	mapType map;
	memset(map, 0, sizeof(map));
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == EMPTY)
				emptyVector.push_back(make_pair(i, j));
			if (map[i][j] == VIRUS)
				virusQ.push(make_pair(i, j));
		}
	}
	cout << makeWall(map, 0, 0) << endl;
}