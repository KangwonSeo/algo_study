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

int N, M;
int arr[8][8];
int c_cnt;
typedef struct camera_info {
	int type;
	int r;
	int c;
} camera_info;
camera_info c_info[8];

//up, right, down, left
int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, 1, 0, -1 };

int camera_type_info[5][4] = {
	{0, 1, 0, 0},
	{0, 1, 0, 1},
	{1, 1, 0, 0},
	{1, 1, 0, 1},
	{1, 1, 1, 1},
};

#define WALL_NUM 6
#define MON 7
void watch(int r, int c, int dir) {
	int nr = r;
	int nc = c;
	while (1) {
		nr += dr[dir];
		nc += dc[dir];
		if (nr < 0 || nr >= N || nc < 0 || nc >= M) return;
		if (arr[nr][nc] == WALL_NUM) return;
		if (arr[nr][nc] == 0) arr[nr][nc] = MON;
	}
}

int arr_result(void) {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (arr[i][j] == 0) ret++;
		}
	}
	return ret;
}

int func(int idx) {
	if (idx >= c_cnt) {
		return arr_result();
	}
	int ret = INF;
	int backup[8][8] = { 0, };
	memcpy(backup, arr, sizeof(arr));
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (camera_type_info[c_info[idx].type][j])
				watch(c_info[idx].r, c_info[idx].c, (j+i)%4);
		}
		ret = min(ret, func(idx + 1));
		memcpy(arr, backup, sizeof(arr));
	}
	return ret;
}

int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> arr[i][j];
			if (arr[i][j] >= 1 && arr[i][j] <= 5) {
				c_info[c_cnt].type = arr[i][j]-1;
				c_info[c_cnt].r = i;
				c_info[c_cnt].c = j;
				c_cnt++;
			}
		}
	}
	cout << func(0) << endl;
}