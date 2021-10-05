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

int map[20][20];
int cmd[1000];
int N, M;
int r, c;
int K;
int dice[4][4];
int dc[4] = { 1, -1, 0, 0 };
int dr[4] = { 0, 0, -1, 1 };

int& up = dice[1][1];
int& down = dice[3][1];
int& down2 = dice[1][3];
void play_dice(int dir)
{
	int start_r = dir >= 2 ? 0 : 1;
	int start_c = dir >= 2 ? 1 : 0;
	down2 = down;
	int tmp = dice[start_r][start_c];
	int i = 4;
	while (i--) {
		start_r = (4 + start_r + dr[dir]) % 4;
		start_c = (4 + start_c + dc[dir]) % 4;
		int backup = dice[start_r][start_c];
		dice[start_r][start_c] = tmp;
		tmp = backup;
	}
	if (dir < 2) down = down2;
}
void copy_dice() {
	if (map[r][c]) {
		down = map[r][c];
		map[r][c] = 0;
	}
	else {
		map[r][c] = down;
	}
}

void solve()
{
	for (int i = 0; i < K; i++) {
		if ((c + dc[cmd[i]] >= M || c + dc[cmd[i]] < 0) ||
			(r + dr[cmd[i]] >= N || r + dr[cmd[i]] < 0)) continue;
		c += dc[cmd[i]];
		r += dr[cmd[i]];
		play_dice(cmd[i]);
		copy_dice();
		cout << up << endl;
	}
}

int main()
{
	cin >> N >> M >> r >> c >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < K; i++) {
		cin >> cmd[i];
		cmd[i]--;
	}
	
	solve();
}