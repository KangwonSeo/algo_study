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
}
pii change_dir(int dir) {
	switch (dir) {
		case 1: return mp(0, -1);
		case 2: return mp(-1, -1);
		case 3: return mp(-1, 0);
		case 4: return mp(-1, 1);
		case 5: return mp(0, 1);
		case 6: return mp(1, 1);
		case 7: return mp(1, 0);
		case 8: return mp(1, -1);
	}
}

int func(pii arr[][N_TABLE]) {
	pii arr_b[N_TABLE][N_TABLE];
	memcpy(&arr_b, arr, sizeof(pair<int, int>)* N_TABLE* N_TABLE );
	for (int i = 0; i < (N_TABLE * N_TABLE); i++) {
		pii seq = find_seq(i + 1, arr_b);
		if(seq.first != -1 && seq.second != -1){
			pii shift = change_dir(arr_b[seq.second][seq.first].second);
			if( arr_b[seq.second + shift.second][seq.first + shift.first].first != SHARK &&
				(seq.second + shift.second) >= 0 && (seq.second + shift.second) <= 3 &&
				(seq.first + shift.first) >= 0 && (seq.first + shift.first) <= 3 )
				swap(arr_b[seq.second][seq.first], arr_b[seq.second+shift.second][seq.first+shift.first]);
		}
	}

	//iterate
	//deal with fish
	//deal with shark and return	
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
	cout << func(arr) << endl;
	return 0;
}
