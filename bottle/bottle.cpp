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
#include <cstdint>

using namespace std;

int N, K;
int countBinary(int Binary)
{
	int cnt = 0;
	while ( Binary > 0 ) {
		if (Binary & 1) cnt++;
		Binary = Binary >> 1;
	}
	return cnt;
}

int main(void) {
	int cnt = 0;
	cin >> N >> K;
	while (true) {
		if (countBinary(N) <= K) break;
		N++;
		cnt++;
	}
	cout << cnt << endl;
	return 0;
}
