#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cstring>
#include <map>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>
#include <math.h>
#include <utility>
#define N_TABLE	4
#define SHARK 100
#define pii pair<int, int>
#define mp make_pair 

using namespace std;
pii find_seq(int seq, pii arr[][N_TABLE]) {
	//find seq in arr
	for (int y = 0; y < N_TABLE; y++) {
		for (int x = 0; x < N_TABLE; x++) {
			if (arr[y][x].first == seq)
				return mp(x, y);
		}
	}
	return mp(-1, -1);
} // return x,y
pii change_dir(int dir) {
	switch (dir) {
		case 1: return mp(0, -1);
		case 2: return mp(-1, -1);
		case 3: return mp(-1, 0);
		case 4: return mp(-1, 1);
		case 5: return mp(0, 1);
		case 6: return mp(1, 1);
		case 7: return mp(1, 0);
		case 8: case 0: return mp(1, -1);
	}
} // return x,y

int func(pii arr[][N_TABLE], pii pos) { //pos x,y
	int ret = 0;
	pii arr_b[N_TABLE][N_TABLE];
	memcpy(arr_b, arr, sizeof(pair<int, int>)* N_TABLE* N_TABLE );
	for (int i = 0; i < (N_TABLE * N_TABLE); i++) {
		pii seq = find_seq(i + 1, arr_b);
		if(seq.first != -1 && seq.second != -1){
			pii shift;
			bool found = false;
			for (int j = 0; j < 8; j++) {
				int dir = arr_b[seq.second][seq.first].second;
				shift = change_dir((dir+j) % 8);
					if (arr_b[seq.second + shift.second][seq.first + shift.first].first != SHARK &&
						(seq.second + shift.second) >= 0 && (seq.second + shift.second) <= 3 &&
						(seq.first + shift.first) >= 0 && (seq.first + shift.first) <= 3) {
						found = true;
						arr_b[seq.second][seq.first].second = (dir + j) % 8;
						break;
					}
			}
			if(found)
				swap(arr_b[seq.second][seq.first], arr_b[seq.second+shift.second][seq.first+shift.first]);
		}
	}
	//shark working
	pii shift = change_dir(arr_b[pos.second][pos.first].second);
	for (int i = 1; i < N_TABLE - 1; i++) {
		int next_y = pos.second + i * shift.second;
		int next_x = pos.first + i * shift.first;
		int val = 0;
		if (arr_b[next_y][next_x].first == 0) continue; //skip
		if (next_y < 0 || next_y > 3 || next_x < 0 || next_x > 3) break; //overflow
		pii tmp[N_TABLE][N_TABLE];
		memcpy(tmp, arr_b, sizeof(pair<int, int>) * N_TABLE * N_TABLE);
		tmp[pos.second][pos.first].first = tmp[pos.second][pos.first].second = 0; //delete first
		val = tmp[next_y][next_x].first;
		tmp[next_y][next_x].first = SHARK;
		ret = max(ret, val + func(tmp, mp(next_x, next_y)));
	}
	return ret;

}
int main(void) {
	int initial = 0;
	pii arr[N_TABLE][N_TABLE];
	for (int y = 0; y < N_TABLE; y++) {
		for(int x=0; x< N_TABLE; x++) {
			int a, b;
			cin >> a >> b;
			arr[y][x] = mp(a, b);
		}
	}
	initial = arr[0][0].first;
	arr[0][0].first = SHARK;
	cout << initial + func(arr, mp(0,0)) << endl;
	return 0;
}
