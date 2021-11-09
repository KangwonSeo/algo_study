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
#define MAX (1000000000)
#define MIN (-1000000000)

using namespace std;

int N;
int arr[11];
int op[4];

int minVal = MAX;
int maxVal = MIN;

void solve(int pos, int result)
{
	if (pos >= N - 1) {
		maxVal = max(maxVal, result);
		minVal = min(minVal, result);
	}
	for (int i = 0; i < 4; i++) {
		if (op[i]) {
			op[i] -= 1;
			switch (i) {
				case 0:
					solve(pos + 1, result + arr[pos + 1]);
					break;
				case 1:
					solve(pos + 1, result - arr[pos + 1]);
					break;
				case 2:
					solve(pos + 1, result * arr[pos + 1]);
					break;
				case 3:
					solve(pos + 1, result / arr[pos + 1]);
					break;
			}
			op[i] += 1;
		}
	}

}

int main()
{
	cin >> N; 
	for (int i = 0; i < N; i++)
		cin >> arr[i];
	for (int i = 0; i < 4; i++)
		cin >> op[i];

	solve(0, arr[0]);
	cout << maxVal << endl;
	cout << minVal << endl;
}