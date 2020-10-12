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
 
int main(void) {
        ios_base::sync_with_stdio(0);
        cin.tie(0);
        int K, C;
        cin >> K >> C;
 
        for(int i=0; i<C; i++) {
                int M, N;
                cin >> M >> N;
                if(M==N) 
                        cout << "1" << "\n";
                else if(M>N) {
                        if( K-M+1+N >= M-1 )
                                cout << "1" << "\n";
                        else cout << "0" << "\n";
                } else {
                        if( K-N+M >= N-1 )
                                cout << "1" << "\n";
                        else cout << "0" << "\n";
                }
        }
        return 0;
}
