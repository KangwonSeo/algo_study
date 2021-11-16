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

int N;
int ans = INF;
int arr[20][20];

int calc(unsigned int pick) {
	int sum1 = 0;
	int sum2 = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (pick & (1 << i) &&
				pick & (1 << j))
				sum1 += arr[i][j];
			if (!(pick & (1 << i)) &&
				!(pick & (1 << j)))
				sum2 += arr[i][j];
		}
	}
	return abs(sum1 - sum2);
}

void solve(unsigned int pick, int picked, int pos) {
	if (pos >= N) return;
	if (picked == N / 2) {
		ans = min(ans, calc(pick));
		return;
	}
	solve(pick, picked, pos + 1);
	pick |= 1 << pos;
	solve(pick, picked + 1, pos + 1);
}

int main()
{
	cin >> N;
	unsigned int pick = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
		}
	}
	solve(pick, 0, 0);
	cout << ans << endl;
}