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
 
#define MAX_N 1000
#define MAX_N 1000

using namespace std;
int N, M;
bool adj[MAX_N][MAX_M];
vector<int> aMatch, bMatch;
vector<bool> visited;

bool dfs(int a) {
        if(visited[a]) return false;
        visited[a] = true;
        for(int b=0; b<M; ++b) {
                if(adj[a][b]) {
                        if(bMatch[b] == -1 || dfs(bMatch[b])) {
                                aMatch[a] = b;
                                bMatch[b] = a;
                                return true;
                        }
                }
        }
        return false;
}

int bipartiteMatch(void) {
        aMatch = vector<int>(N, -1);
        bMatch = vector<int>(M, -1);
        int size = 0;
        for(int i=0; i<N; i++) {
                visited = vector<bool>(N, false);
                if(dfs(i)) ++size;
        }
        return size;
        
}

int main(void) {
        ios_base::sync_with_stdio(0);
        cin.tie(0);
        cin >> N >> M;

        for(int i=0; i<N; i++) {
                int c;
                cin >> c;
                for(int j=0; j<c; j++) {
                        int work;
                        cin >> work;
                        adj[i][work-1] = true;
                }
        }
        cout << bipartiteMatch() << endl;
        return 0;
}

