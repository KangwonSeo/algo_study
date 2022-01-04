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
int wheel[4][8];
int k;
int n[100];
int dir[100];
int ans;

void rotate_one(int idx, int d)
{
	int tmp[8];
	memcpy(&tmp[d > 0 ? 1 : 0], &wheel[idx][d > 0 ? 0 : 1], sizeof(int) * 7);
	memcpy(&tmp[d > 0 ? 0 : 7], &wheel[idx][d > 0 ? 7 : 0], sizeof(int));
	memcpy(wheel[idx], tmp, sizeof(wheel[0]));
}

#define IDX_RIGHT 2
#define IDX_LEFT 6
void rotate(int seq)
{
	int start = n[seq];
	int start_dir = dir[seq];
	int d = start_dir;
	int backup[8];
	int tmp[8];
	memcpy(backup, &wheel[start], sizeof(backup));
	memcpy(tmp, &wheel[start], sizeof(tmp));
	rotate_one(start, start_dir);
	for (int i = start + 1; i < 4; i++) {
		if (backup[IDX_RIGHT] == wheel[i][IDX_LEFT]) break;
		memcpy(backup, &wheel[i], sizeof(backup));
		rotate_one(i, d = d * (-1) );
	}
	d = start_dir;
	memcpy(backup, tmp, sizeof(tmp));
	for (int i = start - 1; i >= 0; i--) {
		if (backup[IDX_LEFT] == wheel[i][IDX_RIGHT]) break;
		memcpy(backup, &wheel[i], sizeof(backup));
		rotate_one(i, d = d * (-1) );
	}
}

void solve(void)
{
	for (int i = 0; i < 4; i++) {
		if(wheel[i][0])
			ans+=pow(2,i);
	}
}

int main()
{
	for (int i = 0; i < 4; i++) {
		string str;
		cin >> str;
		for (int j = 0; j < str.length(); j++) {
			wheel[i][j] = str[j]-'0';
		}
	}
	cin >> k;
	for (int i = 0; i < k; i++) {
		cin >> n[i] >> dir[i];
		n[i]--;
		rotate(i);
	}
	solve();
	cout << ans << endl;
}