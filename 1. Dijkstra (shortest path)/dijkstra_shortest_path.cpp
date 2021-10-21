#include <iostream>
#include "heap_by_pointer.h"
#include "stack.h"
using namespace std;

#define INFINITY 10000

class Node {
public:
    int id, parent, dist;
    Node(){
        id = 0;
        parent = dist = -1;
    };
    print() {
        cout << id << " " << parent << " " << dist << ";";
    }
};

class Edge {
public:
    int to;
    float weight;
};

bool operator<(Node a, Node b) {
    return (a.dist < b.dist);
}

int main() {
    int n,m;
    cout << "Number of nodes: ";
    cin >> n;
    cout << "Number of edges: ";
    cin >> m;
    Trash<Node> node[n+1];
    Edge edge[n+1][n+1];
    for(int i = 1; i <= n; i++) {
        node[i].entry.id = i;
        node[i].entry.parent = 0;
        node[i].entry.dist = INFINITY;
        edge[i][0].to = 0;
    }
    cout << "Edges from, to & weight: " << endl;
    for(int i = 1; i <= m; i++) {
        int p,q,w;
        cin >> p >> q >> w;
        edge[p][0].to++;
        edge[p][edge[p][0].to].to = q;
        edge[p][edge[p][0].to].weight = w;
    }
    int start;
    cout << "Shortest path from: ";
    cin >> start;
    node[start].entry.dist = 0;
    MinHeap<Node> heap(n);
    for(int i = 1; i <= n; i++) {
        heap.throwIn(node+i);
    }
    while(!heap.isEmpty()) {
        Trash<Node>* now = heap.pickUp();
        int from = now->entry.id;
        for(int i = 1; i <= edge[from][0].to; i++) {
            int to = edge[from][i].to, wt = edge[from][i].weight;
            if(node[from].entry.dist + wt < node[to].entry.dist) {
                node[to].entry.dist = node[from].entry.dist + wt;
                node[to].entry.parent = from;
                heap.adjust(node[to]);
            }
        }
    }
    Stack<int> path;
    cout << "Shortest paths to..." << endl;
    for(int i = 1; i <= n; i++) {
        cout << i << ": ";
        int j = i;
        if(node[i].entry.dist < 10000) {
            do {
                path.push(j);
                j = node[j].entry.parent;
            } while(j != 0);
            while(!path.isEmpty()) {
                cout << path.pop() << " -> ";
            }
            cout << "\b\b\b   \b\b\b; " << node[i].entry.dist << endl;
        }
        else {
            cout << "None ; inf" << endl;
        }
    }
}
