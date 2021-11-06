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
int map[50][50];
bool visited[50][50];
int ans;
int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, 1, 0, -1 };

bool invalidRange(int r, int c)
{
	return r < 0 || r >= N || c < 0 || c >= M;
}

void solve(int r, int c, int d)
{
	int i;
	if(!visited[r][c]) {
		visited[r][c] = true;
		ans++;
	}

	for (i = 0; i < 4; i++) {
		int left = (d + 4 - 1) % 4;
		int newR = r + dr[left];
		int newC = c + dc[left];
		d = left;
		if (!invalidRange(newR, newC) && !map[newR][newC] && !visited[newR][newC]) {
			solve(newR, newC, d);
			break;
		}
	}
	if (i == 4) {
		int back = (d + 4 - 2) % 4;
		int newR = r + dr[back];
		int newC = c + dc[back];
		if (!invalidRange(newR, newC) && !map[newR][newC]) {
			solve(newR, newC, d);
		}
	}
}

int main()
{
	int r, c, d;
	cin >> N >> M;
	cin >> r >> c >> d;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
	solve(r,c,d);
	cout << ans << endl;
}