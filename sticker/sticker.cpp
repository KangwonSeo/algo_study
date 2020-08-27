#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cstring>
#include <map>
#include <vector>
#include <list>
#include <algorithm>
#include <utility>
#include <numeric>
#include <math.h>
#define pii pair<int, int>
#define mp make_pair
using namespace std;

#define ATTACHED 1
#define DIR_NUM 4
int calc(vector<vector<int> >& v) {
	int ret = 0;
	for (unsigned int i = 0; i < v.size(); i++) {
		ret += accumulate(v[i].begin(), v[i].end(), 0);
	}
	return ret;
}
bool attach(pii offset, vector<vector<int> > &monitor, vector<vector<int> > &stiker) { //offset(y,x)
	for (unsigned int i = 0; i < stiker.size(); i++) {
		for (unsigned int j = 0; j < stiker[0].size(); j++) {
			if (stiker[i][j] == ATTACHED && monitor[offset.first + i][offset.second + j] == ATTACHED) {
				return false;
			}
		}
	}
	for (unsigned int i = 0; i < stiker.size(); i++) {
		for (unsigned int j = 0; j < stiker[0].size(); j++) {
			if (stiker[i][j] == ATTACHED) monitor[offset.first + i][offset.second + j] = ATTACHED;
		}
	}
	return true;
}

vector<vector<int> > rotate(vector<vector<int> >& sticker, int dir) {
	vector<vector<int> > s;
	switch (dir) {
		case 0:
			s = sticker;
			break;
		case 1:
			s.resize(sticker[0].size(), vector<int>(sticker.size(), 0));
			for (unsigned int i = 0; i < s.size(); i++) {
				for (unsigned int j = 0; j < s[0].size(); j++) {					
					s[i][j] = sticker[(s[0].size() - 1) - j][i];
				}
			}
			break;
		case 2:
			s.resize(sticker.size(), vector<int>(sticker[0].size(), 0));
			for (unsigned int i = 0; i < s.size(); i++) {
				for (unsigned int j = 0; j < s[0].size(); j++) {
					s[i][j] = sticker[s.size()-1-i][(s[0].size()-1)-j];
				}
			}
			break;
		case 3:
			s.resize(sticker[0].size(), vector<int>(sticker.size(), 0));
			for (unsigned int i = 0; i < s.size(); i++) {
				for (unsigned int j = 0; j < s[0].size(); j++) {				
					s[i][j] = sticker[j][s.size() - 1 - i];
				}
			}
			break;
	}
	return s;
}

void tryAttach(vector<vector<int> > &monitor, vector<vector<int> > &stiker) {
	for (int i = 0; i < DIR_NUM; i++) {
		vector<vector<int> > s = rotate(stiker, i);
		if (s.size() > monitor.size() || s[0].size() > monitor[0].size()) continue;
		for (unsigned int j = 0; j<= monitor.size() - s.size(); j++) {
			for(unsigned int k=0; k<= monitor[0].size() - s[0].size(); k++) {
				if (attach(mp(j, k), monitor, s)) {
					return;
				}
			}
		}
	}
}
void print(vector<vector<int> >& m) {
	for (unsigned int i = 0; i < m.size(); i++) {
		for (unsigned int j = 0; j < m[0].size(); j++) {
			cout << m[i][j] << ' ';
		}
		cout << endl;
	}
}
int main(void) {
	vector<vector<int> > monitor;
	vector<vector<int> > stiker[100];
	int N, M, K;
	cin >> N >> M >> K;
	monitor.resize(N, vector<int>(M, 0));
	for (int i = 0; i < K; i++) {
		int R, C;
		cin >> R >> C;
		stiker[i].resize(R, vector<int>(C, 0));
		for (int j = 0; j < R; j++) {
			for (int k = 0; k < C; k++) {
				cin >> stiker[i][j][k];
			}
		}
		tryAttach(monitor, stiker[i]);
	}
	cout << calc(monitor) << endl;

	return 0;
}
