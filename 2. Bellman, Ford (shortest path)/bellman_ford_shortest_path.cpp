#include <iostream>
using namespace std;

#define INFINITY 10000

class Node {
public:
    int parent, dist;
};

class Edge {
public:
    int from, to, weight;
};

int main() {
    int n,m;
    cout << "Number of nodes: ";
    cin >> n;
    cout << "Number of edges: ";
    cin >> m;
    static Node* node;
    node = new Node[n+1];
    Edge edge[m+1];
    for(int i = 1; i <= m; i++) {
        int p,q,w;
        cin >> p >> q >> w;
        edge[i].from = p;
        edge[i].to = q;
        edge[i].weight = w;
    }
    for(int i = 1; i <= n; i++) {
        node[i].parent = 0;
        node[i].dist = INFINITY;
    }
    int start;
    cout << "Shortest path from: ";
    cin >> start;
    node[start].dist = 0;
    bool update = true;
    for(int i = 1; update == true && i <= n; i++) {
        update = false;
        for(int j = 1; j <= m; j++) {
            int from = edge[j].from, to = edge[j].to;
            //cout << "Loop no.: " << i << "," << j << endl;
            if(node[from].dist != INFINITY && node[to].dist > node[from].dist + edge[j].weight) {
                node[to].dist = node[from].dist + edge[j].weight;
                node[to].parent = from;
                //cout << "Updated: " << from << " -> " << to  << ", " << node[from].dist << " -> " << node[to].dist << endl;
                update = true;
            }
        }
    }
    class Function {
    public:
        static void findPath(int n) {
        if(node[n].parent == 0) {
            cout << n;
            return;
        }
        findPath(node[n].parent);
        cout << " -> " << n;
        }
    };
    if(update == true) {
        cout << "Degenerate graph. Negative cycle exists in the graph." << endl;
    }
    else {
        cout << "Shortest paths to..." << endl;
        for(int i = 1; i <= 5; i++) {
            cout << i << ": ";
            if(node[i].dist == INFINITY) {
                cout << "None ; " << i << endl;
            }
            else {
                Function::findPath(i);
                cout << " ; " << node[i].dist << endl;
            }
        }
    }
}
