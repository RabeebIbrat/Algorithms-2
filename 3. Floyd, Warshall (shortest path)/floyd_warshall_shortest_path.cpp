#include <cstdio>
#include "stack.h"
using namespace std;
#define INFINITY 30000

int main() {
    int n, m;
    printf("Number of nodes: ");
    scanf("%d", &n);
    printf("Number of edges: ");
    scanf("%d", &m);
    int parent[n+1][n+1], dp[n+1][n+1];
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            dp[i][j] = INFINITY;
            parent[i][j] = 0;
        }
        dp[i][i] = 0;
    }
    printf("Edges from, to & weight...\n");
    for(int i = 1; i <= m; i++) {
        int p,q,w;
        scanf("%d%d%d", &p, &q, &w);
        dp[p][q] = w;
        parent[p][q] = p;
    }
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(dp[i][j] > dp[i][k] + dp[k][j]) {
                    dp[i][j] = dp[i][k] + dp[k][j];
                    parent[i][j] = parent[k][j];
                }
            }
        }
    }
    printf("Shortest paths...\n");
    Stack<int> path;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            printf("[%d -> %d]: ", i, j);
            if(dp[i][j] == INFINITY) {
                printf("None ; inf\n");
                continue;
            }
            int now = j;
            while(now) {
                path.push(now);
                now = parent[i][now];
            }
            while(!path.isEmpty()) {
                printf("%d -> ", path.pop());
            }
            printf("\b\b\b   \b\b\b; %d\n", dp[i][j]);
        }
    }
    return 0;
}
