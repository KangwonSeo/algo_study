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

int findMaxValue(vector<vector<int> >& v)
{
	int maxVal = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			maxVal = max(maxVal, v[i][j]);
		}
	}
	return maxVal;
}

void move(vector<vector<int> >& t)
{
	for (int i = 0; i < N; i++) {
		vector<int> tmp(N,0);
		int cnt = -1;
		int flag = 0;
		for (int j = 0; j < N; j++) {
			if (t[i][j]) {
				if (cnt >= 0 && tmp[cnt] == t[i][j] && flag == 0) {
					tmp[cnt] = tmp[cnt] * 2;
					flag = 1;
				}
				else {
					tmp[++cnt] = t[i][j];
					flag = 0;
				}				
			}
		}
		t[i] = tmp;
	}
}

void rotate(vector<vector<int> >& v)
{
	vector<vector<int> > t = v;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			t[j][N-1-i] = v[i][j];
		}
	}
	v = t;
}

int solve(vector<vector<int> >& v, int cnt)
{
	int ret = 0;
	if (cnt >= 5) {
		return findMaxValue(v);
	}

	for (int i = 0; i < 4; i++) {
		vector<vector<int> > t = v;
		move(t);
		ret = max(ret, solve(t, cnt+1));
		rotate(v);
	}
	return ret;
}

int main()
{
	cin >> N;
	vector<vector<int> > v;
	v.resize(N, vector<int>(N, 0));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> v[i][j];
		}
	}
	cout << solve(v,0) << endl;
}