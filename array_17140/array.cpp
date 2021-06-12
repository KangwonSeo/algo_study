#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cstring>
#include <map>
#include <vector>
#include <queue>
#include <list>
#include <algorithm>
#include <utility>
#include <numeric>
#include <math.h>
#define pii pair<int, int>

using namespace std;
int A[100][100];
int r, c, k;
int row, col;
int cnt;

void operation(int dir) {
	int max_val = 0;
	for (int i = 0; i < (dir ? col : row); i++) {
		int calA[101] = { 0, };
		vector<pii> sorted;
		for (int j = 0; j < (dir ? row : col); j++) {
			if (dir) calA[A[j][i]]++;
			else {
				calA[A[i][j]]++;
			}
		}
		for (int j = 1; j < 101; j++) {
			if (calA[j]) {
				sorted.emplace_back(make_pair(calA[j], j));
			}
		}
		sort(sorted.begin(), sorted.end());
		int tmp = 0;
		for (auto s : sorted) {
			if (tmp < 100) {
				if (dir) {
					A[tmp][i] = s.second;
					A[tmp + 1][i] = s.first;
				}
				else {
					A[i][tmp] = s.second;
					A[i][tmp + 1] = s.first;
				}
				tmp = tmp + 2;
			}
			else break;
		}
		if (tmp < 100) {
			for (int j = tmp; j < 100; j++)
				if (dir) A[j][i] = 0;
				else A[i][j] = 0;
		}
		max_val = max(max_val, tmp);
	}
	dir? (row = max_val) : (col = max_val);
}

void rop() {
	operation(0);
}

void cop() {
	operation(1);
}

int solve() {
	if (A[r][c] == k) {
		return cnt;
	}
	if (cnt >= 100) return -1;
	if (row >= col)
		rop();
	else cop();
	cnt++;
	return solve();
}

int main()
{
	cin >> r >> c >> k;
	r--; c--;
	row = col = 3;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cin >> A[i][j];
		}
	}
	cout << solve() << endl;
}