#include <cstdio>
#include <iostream>
#include "linked_list.h"
#include "stack.h"
#include "queue.h"
using namespace std;

#define INFINITY 30000

class Edge {
public:
    int to, weight;
    Edge(){};
    Edge(int to, int wt) {
        this->to = to;
        weight = wt;
    }
};

int main() {
    bool directed = true;
    char ch;
    do {
        printf("directed?(y/n) ");
        cin >> ch;
    } while(ch != 'y' && ch != 'n');
    if(ch == 'n')  directed = false;
    int n, m;
    printf("Number of nodes: ");
    scanf("%d", &n);
    printf("Number of edges: ");
    scanf("%d", &m);
    int dist[n+1], prev[n+1];
    bool inq[n+1];
    LinkedList<Edge> adjList[n+1];
    for(int i = 1; i <= n; i++) {
        dist[i] = INFINITY;
        prev[i] = 0;
        inq[i] = false;
    }
    printf("Edges from, to & weight...\n");
    for(int i = 1; i <= m; i++) {
        int p, q, w;
        scanf("%d%d%d", &p, &q, &w);
        adjList[p].pushBack(Edge(q,w));
        if(!directed)  adjList[q].pushBack(Edge(p,w));
    }
    printf("Starting node? ");
    int start;
    scanf("%d", &start);
    Queue<int> nList;
    dist[start] = 0;
    nList.enq(start);
    inq[start] = true;
    while(!nList.isEmpty()) {
        int from = nList.deq();
        inq[from] = false;
        for(Linker<Edge>* it = adjList[from].getHead()->getNext(); it != adjList[from].getTail(); it = it->getNext()) {
            int to = it->getValue().to, wt = it->getValue().weight;
            if(dist[to] > dist[from] + wt) {
                dist[to] = dist[from] + wt;
                prev[to] = from;
                if(inq[to] == false) {
                    nList.enq(to);
                    inq[to] = true;
                }
            }
        }
    }
    printf("Shortest path to...\n");
    for(int i = 1; i <= n; i++) {
        printf("%d: ", i);
        if(dist[i] == INFINITY) {
            printf("None ; inf\n");
            continue;
        }
        Stack<int> path;
        int now = i;
        while(now) {
            path.push(now);
            now = prev[now];
        }
        while(!path.isEmpty()) {
            printf("%d -> ", path.pop());
        }
        printf("\b\b\b   \b\b\b; %d\n", dist[i]);
    }
}
