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
int R, C, M;
struct shark {
	int s, d, z;
};
shark A[100][100];
shark backup[100][100];

void move() {
	memset(backup, 0, sizeof(A));
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (A[i][j].z) {
				int new_d, new_r, new_c;
				int x, reminder, share;
				switch (A[i][j].d) {
				case 0:
					if (A[i][j].s <= i) {
						new_d = A[i][j].d;
						new_r = i - A[i][j].s;
					}
					else {
						x = A[i][j].s - i;
						reminder = x % (R - 1);
						reminder = (reminder == 0) ? (R - 1) : reminder;
						share = (x - 1) / (R - 1);
						new_d = (share % 2 == 0) ? 1 : 0;
						new_r = (new_d == 1) ? reminder : (R - 1) - reminder;
					}
					new_c = j;
					break;
				case 1:
					if (A[i][j].s + i <= (R - 1)) {
						new_d = A[i][j].d;
						new_r = i + A[i][j].s;
					}
					else {
						x = A[i][j].s + i;
						reminder = x % (R - 1);
						reminder = (reminder == 0) ? (R - 1) : reminder;
						share = (x - 1) / (R - 1);
						new_d = (share % 2 == 0) ? 1 : 0;
						new_r = (new_d == 1) ? reminder : (R - 1) - reminder;
					}
					new_c = j;
					break;
				case 2:
					if (A[i][j].s + j <= (C - 1)) {
						new_d = A[i][j].d;
						new_c = j + A[i][j].s;
					}
					else {
						x = A[i][j].s + j;
						reminder = x % (C - 1);
						reminder = (reminder == 0) ? (C - 1) : reminder;
						share = (x - 1) / (C - 1);
						new_d = (share % 2 == 0) ? 2 : 3;
						new_c = (new_d == 2) ? reminder : (C - 1) - reminder;
					}
					new_r = i;
					break;
				case 3:
					if (A[i][j].s <= j) {
						new_d = A[i][j].d;
						new_c = j - A[i][j].s;
					}
					else {
						x = A[i][j].s - j;
						reminder = x % (C - 1);
						reminder = (reminder == 0) ? (C - 1) : reminder;
						share = (x - 1) / (C - 1);
						new_d = (share % 2 == 0) ? 2 : 3;
						new_c = (new_d == 2) ? reminder : (C - 1) - reminder;
					}
					new_r = i;
					break;
				}
				if (A[i][j].z > backup[new_r][new_c].z) {
					backup[new_r][new_c].d = new_d;
					backup[new_r][new_c].s = A[i][j].s;
					backup[new_r][new_c].z = A[i][j].z;
				}
			}
		}
	}
	memcpy(A, backup, sizeof(A));
}

int solve() {
	int cnt = 0;
	for (int i = 0; i < C; i++) {
		for (int j = 0; j < R; j++) {
			if (A[j][i].z) {
				cnt = cnt + A[j][i].z;
				A[j][i].z = 0;
				break;
			}
		}
		move();
	}
	return cnt;
}

int main()
{
	cin >> R >> C >> M;
	for (int i = 0; i < M; i++) {
		int r, c, s, d, z;
		cin >> r >> c >> s >> d >> z;
		r--;
		c--;
		d--;
		A[r][c] = { s,d,z };
	}
	cout << solve() << endl;
}