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
int N, L;
int arr[100][100];
int bak[100][100];
int ans;

int helper(int i, int start, int &mark_idx, bool op)
{
	int k = 0;
	int ret = -1;
	int end = op ? start - L : start + L;
	for (k = start;
		(op ? k > end:k < end) && (op ? k >= 0 : k < N);
		(op ? k-- : k++)) {
		if(k == mark_idx ||
			arr[i][k] != arr[i][start]) break;
	}
	if (k == end) {
		mark_idx = op ? end + 1 : end - 1;
		ret = 0;
	}

	return ret;

}
void calc() 
{
	int i = 0, j=0, k=0;
	int start = 0, end = 0;

	for (i = 0; i < N; i++) {
		int mark_idx = -1;
		for (j = 1; j < N; j++) {
			if (arr[i][j - 1] == arr[i][j]) continue;
			else if (arr[i][j - 1] + 1 == arr[i][j]) {
				if (helper(i, j - 1, mark_idx, true)) break;
			}
			else if (arr[i][j - 1] == arr[i][j] + 1) {
				if (helper(i, j, mark_idx, false)) break;
			}
			else {
				break;
			}
		}
		if (j == N) {
			ans++;
		}
	}
}

void rotate()
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			bak[j][(N-1)-i] = arr[i][j];
		}
	}
	memcpy(arr, bak, sizeof(arr));
}

void solve() 
{
	calc();
	rotate();
	calc();
}

int main()
{
	cin >> N >> L;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
		}
	}
	solve();
	cout << ans << endl;
}