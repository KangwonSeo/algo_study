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

int R, C, T;
int up;
int A[50][50];
int B[50][50];
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};
int sum() {
	int cnt = 0;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (A[i][j] != -1) cnt += A[i][j];
		}
	}
	return cnt;
}

void initB(void) {
	memset(B, 0, sizeof(B));
	B[up][0] = -1;
	B[up + 1][0] = -1;
}
void expand(void) {
	initB();
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if ( (i == up || i==up+1) && j == 0) continue;
			int newR, newC;
			int cnt = 0;
			int share = A[i][j] / 5;
			for (int d = 0; d < 4; d++) {
				newR = i + dr[d];
				newC = j + dc[d];
				if (newR < 0 || newR >= R
					|| newC < 0 || newC >= C) continue;
				if (A[newR][newC] == -1) continue;
				B[newR][newC] = B[newR][newC] + share;
				cnt++;
			}
			B[i][j] = B[i][j] + (A[i][j] - (cnt * share));
		}
	}
	memcpy(A, B, sizeof(B));
}

void cycle(void) {
	initB();
	for (int i = 1; i < C - 1; i++) {
		B[up][i + 1] = A[up][i];
	}
	for (int i = up; i > 0; i--) {
		B[i-1][C-1] = A[i][C-1];
	}
	for (int i = C-1; i > 0; i--) {
		B[0][i-1] = A[0][i];
	}
	for (int i = 0; i < up-1; i++) {
		B[i+1][0] = A[i][0];
	}
	for (int i = 1; i < C - 1; i++) {
		B[up+1][i + 1] = A[up+1][i];
	}
	for (int i = up+1; i < R-1; i++) {
		B[i + 1][C - 1] = A[i][C - 1];
	}
	for (int i = C - 1; i > 0; i--) {
		B[R-1][i - 1] = A[R-1][i];
	}
	for (int i = R - 1; i  > up+2; i--) {
		B[i -1][0] = A[i][0];
	}
	for (int i = 1; i < up; i++) {
		for (int j = 1; j < C - 1; j++) {
			B[i][j] = A[i][j];
		}
	}
	for (int i = up+2; i < R-1; i++) {
		for (int j = 1; j < C - 1; j++) {
			B[i][j] = A[i][j];
		}
	}
	memcpy(A, B, sizeof(B));
}

int solve() {
	while (T--) {
		expand();
		cycle();		
	}
	return sum();
}

int main()
{
	cin >> R >> C >> T;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> A[i][j];
			if (A[i][j] == -1 && up == 0) up = i;
		}
	}
	cout << solve() << endl;
}