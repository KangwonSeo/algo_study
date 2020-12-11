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
#define WHITE 1
#define BLUE 2

using namespace std;
int numWhite=0;
int numBlue=0;
vector<int> memWhite, memBlue;

int n;
vector<int> discovered;
vector<vector<int> > adj;
void bfs(int start) {
        queue<int> q;
        discovered[start] = WHITE;
        q.push(start);
        while(!q.empty()) {
                int here = q.front();
                q.pop();
                for(int i=0; i<adj[here].size(); ++i) {
                        int there = adj[here][i];
                        if(discovered[there] && discovered[there] == discovered[here]) {
                                discovered[here] = ( (discovered[there]==WHITE) ? BLUE:WHITE );
                        }
                        if(!discovered[there]) {
                                q.push(there);
                                discovered[there] = ( (discovered[here]==WHITE) ? BLUE:WHITE );
                        }
                }
        }
}

void oneSided(void) {
        if(numWhite==n) {
                memBlue.push_back(memWhite[n-1]);
                memWhite.pop_back();
                numWhite--;
                numBlue++;
        }
}

void printResult(void) {
        cout << numWhite << endl;
        for(int i=0; i<memWhite.size(); i++) {
                cout << memWhite[i]+1 << ' ';
        }
        cout << endl;
        
        cout << numBlue << endl;
        for(int i=0; i<memBlue.size(); i++) {
                cout << memBlue[i]+1 << ' ';
        }
        cout << endl;
}

int main(void) {
        ios_base::sync_with_stdio(0);
        cin.tie(0);
        cin >> n;
 
        discovered.resize(n, 0);
        adj.resize(n, vector<int>(1,0));
        for(int i=0; i<n; i++) {
                int c;
                cin >> c;
                adj[i].resize(c,0);
                for(int j=0; j<c; j++) {
                        cin >> adj[i][j];
                        adj[i][j]--;
                }
        }

        for(int i=0; i<n; i++) {
                if(!discovered[i])
                        bfs(i);
        }       
        
        for(int i=0; i<n; i++) {
                if(discovered[i] == WHITE) {
                        numWhite++;
                        memWhite.push_back(i);
                }                       
                if(discovered[i] == BLUE) {
                        numBlue++;
                        memBlue.push_back(i);
                }
        }
        oneSided();
        printResult();

        return 0;
}
