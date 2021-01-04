#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cstring>
#include <map>
#include <vector>
#include <queue>
#include <list>
#include <algorithm>
#include <utility>
#include <numeric>
#include <math.h>
#include <cstdint>
#define INF 987654321
#define MAX_N 10000
using namespace std;
int N;
vector<int> CACHE;
vector<int> adj[MAX_N];

int printResult(void) {
        int ret = 0;
        for(int i=0; i<N; i++) {
                int cache=0;
                for(int j=0; j<adj[i].size(); j++) {
                        cache = max(cache, CACHE[adj[i][j]]);
                }
                CACHE[i] = CACHE[i] + cache; 
        }
        
        for(int i=0; i<N; i++) {
                ret = max(ret, CACHE[i]);
        }
        
        return ret;
}

int main(void) {
        ios_base::sync_with_stdio(0);
        cin.tie(0);
        cin >> N;
        CACHE.resize(N, 0);
        for(int i=0; i<N; i++) {
                int time, num;
                cin >> time >> num;
                CACHE[i] = time;
                if(num) {
                        int work;
                        for(int j=0; j<num; j++) {
                                cin >> work;
                                adj[i].push_back(work-1);
                        }
                }
        }
        cout << printResult() << endl;
        return 0;
}
