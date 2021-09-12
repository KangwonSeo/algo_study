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
#define APPLE 987654321

using namespace std;

int N, K, L;
int arr[100][100];
enum {RIGHT, DOWN, LEFT, UP};

int current = RIGHT;

char dir[10001];
int dy[4] = {0,1,0,-1};
int dx[4] = {1,0,-1,0};

int solve(void)
{
	int cnt = 1;
	int dec = 0;
	pii pos = make_pair(0, 0); //x,y
	pii start = make_pair(0, 0);
	arr[pos.second][pos.first] = cnt;
	while (1) {
		cnt++;
		pos.first = pos.first + dx[current];
		pos.second = pos.second + dy[current];

		if (pos.first < 0 || pos.first >= N
			|| pos.second < 0 || pos.second >= N ||
			(arr[pos.second][pos.first] != 0 && arr[pos.second][pos.first] != APPLE) ) break;

		if (arr[pos.second][pos.first] != APPLE) dec = 1;
		else dec = 0;

		arr[pos.second][pos.first] = cnt;
		if (dec) {
			int tmp = arr[start.second][start.first];
			arr[start.second][start.first] = 0;
			// find tmp+1
			for (int i = 0; i < 4; i++) {
				int ny, nx;
				ny = start.second + dy[i];
				nx = start.first + dx[i];
				if (ny < 0 || ny >= N || nx < 0 || nx >= N) continue;
				if (arr[ny][nx] == tmp + 1) {
					start.first = nx;
					start.second = ny;
					break;
				}
			}
		}
		

		if (dir[cnt - 1]) {
			if (dir[cnt - 1] == 'D') current = (current + 1)%4;
			else current = (4+current-1)%4;
		}
	}
	return cnt - 1;
}

int main()
{
	cin >> N;
	cin >> K;
	for (int i = 0; i < K; i++) {
		int x, y;
		cin >> y >> x;
		arr[y - 1][x - 1] = APPLE;
	}
	cin >> L;
	for (int i = 0; i < L; i++) {
		int s;
		char d;
		cin >> s >> d;
		dir[s] = d;
	}
	cout << solve() << endl;
}