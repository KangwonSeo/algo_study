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
#define MAX_V 501
using namespace std;

int V,M;
vector<pair<int,int> > adj[MAX_V];
vector<long long> bellmanFord(int src) {
        vector<long long> upper(V, INF);
        upper[src] = 0;
        bool updated;
        for(int iter=0; iter < V; ++iter) {
                updated = false;
                for(int here = 0; here < V; ++here) {
                        if(upper[here] == INF) continue;
                        for(int i=0; i<adj[here].size(); i++) {
                                int there = adj[here][i].first;
                                int cost = adj[here][i].second;
                                if(upper[there] > upper[here] + cost) {
                                        upper[there] = upper[here] + cost;
                                        updated = true;
                                }
                        }
                }
                        
                if(!updated) break;
        }
        if(updated) upper.clear();
        return upper;
}

int main(void) {
        ios_base::sync_with_stdio(0);
        cin.tie(0);
        cin >> V >> M;
        vector<long long> upper;
        for(int i=0; i<M; i++) {
                int src, dst, cost;
                cin >> src >> dst >> cost;
                adj[src-1].push_back(make_pair(dst-1, cost));
        }
        upper = bellmanFord(0);
        if(upper.size()) {
                for(int i=1; i<V; i++) {
                        if(upper[i] == INF) 
                                cout << -1 << endl;
                        else cout << upper[i] << endl;
                }
        } else cout << -1 << endl;
        
        return 0;
}
