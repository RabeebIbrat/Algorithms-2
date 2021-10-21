#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "linked_list.h"
#include "queue.h"
using namespace std;

#define INFINITY 50000

class Edge {
public:
    int id, from, to, capacity, flow;
    Edge* opposite;
    Edge() {
        id = -1, from = -1, to = -1, capacity = -1, flow = -1;
    }
    Edge(int id, int from, int to, int capacity, int flow = 0) {
        this->id = id;
        this->from = from;
        this->to = to;
        this->capacity = capacity;
        this->flow = flow;
    }
};

class FlowGraph {
public:
    LinkedList<Edge*> *adjList;
    int n, src, trg;
    FlowGraph(int nNode, int source, int target) {
        adjList = new LinkedList<Edge*>[nNode];
        n = nNode;
        src = source;
        trg = target;
    }
    void addEdge(int id, int nEdge, int from, int to, int capacity, int flow = 0) {
        Edge *one, *other;
        one = new Edge(id, from, to, capacity, flow), other = new Edge(id+nEdge, from, to, 0, -flow);
        one->opposite = other;
        other->opposite = one;
        adjList[from].pushBack(one);
        adjList[to].pushBack(other);
    }
};


int augPath(FlowGraph &g) {
    int flow = INFINITY, n = g.n, src = g.src, trg = g.trg;
    Edge* parEdge[n];
    int parNode[n];
    bool visited[n];
    for(int i = 0; i < n; i++) {
        parNode[i] = -1;
        visited[i] = false;
    }
    Queue<int> bfs;
    bfs.enq(src);
    visited[src] = true;
    while(!bfs.isEmpty()) {
        int from = bfs.deq();
        for(Linker<Edge*> *it = g.adjList[from].getHead()->getNext(); it != g.adjList[from].getTail(); it = it->getNext()) {
            Edge* edge = it->getValue();
            if(visited[edge->to] == false && edge->flow < edge->capacity) {
                bfs.enq(edge->to);
                parNode[edge->to] = from;
                parEdge[edge->to] = edge;
                visited[edge->to] = true;
            }
        }
    }
    if(parNode[trg] == -1) {  ///No augmenting path
        return 0;
    }
    int now = trg;
    while(parNode[now] != -1) {
        int flowCap = parEdge[now]->capacity - parEdge[now]->flow;
        if(flowCap < flow) {
            flow = flowCap;
        }
        now = parNode[now];
    }
    ///CHECK
    if(flow <= 0 || flow >= INFINITY) {
        cout << "ERROR: Augmenting path of non-positive/infinite flow." << endl;
        return 0;
    }
    ///END-CHECK
    now = trg;
    while(parNode[now] != -1) {
        parEdge[now]->flow += flow;
        parEdge[now]->opposite->flow -= flow;
        now = parNode[now];
    }
    return flow;
}

int fordFulkerson(FlowGraph &g) {
    int maxFlow = 0, flow = INFINITY;
    while(flow > 0) {
        flow = augPath(g);
        maxFlow += flow;
    }
    return maxFlow;
}

void reachable(const FlowGraph &g, bool *reach) {
    int n = g.n, src = g.src;
    for(int i = 0; i < n; i++) {
        reach[i] = false;
    }
    Queue<int> bfs;
    bfs.enq(src);
    reach[src] = true;
    while(!bfs.isEmpty()) {
        int from = bfs.deq();
        for(Linker<Edge*> *it = g.adjList[from].getHead()->getNext(); it != g.adjList[from].getTail(); it = it->getNext()) {
            Edge* edge = it->getValue();
            if(reach[edge->to] == false && edge->flow < edge->capacity) {
                bfs.enq(edge->to);
                reach[edge->to] = true;
            }
        }
    }
    ///CHECK
    if(reach[g.trg] == true) {
        cout << "ERROR: Node reachable in residual graph.";
    }
    ///END-CHECK
}

int main() {
    ifstream myIn;
    ofstream myOut;
    string inFile, outFile;
    printf("Enter input file name: ");
    cin >> inFile;
    outFile = inFile;
    outFile.append("_out");
    myIn.open(inFile.append(".txt").c_str());
    if(!myIn) {
        cout << "Input file not found." << endl;
        exit(1);
    }
    int n,m,s,t;
    myIn >> n >> m >> s >> t;
    FlowGraph g(n,s,t);
    Edge edge[m];
    for(int i = 0; i < m; i++) {
        int p,q,c;
        myIn >> p >> q >> c;
        edge[i] = Edge(i,p,q,c);
        g.addEdge(i,m,p,q,c);
    }
    myIn.close();
    cout << endl;
    myOut.open(outFile.append(".txt").c_str());
    int maxFlow = fordFulkerson(g);
    for(int i = 0; i < n; i++) {
        for(Linker<Edge*> *iter = g.adjList[i].getHead()->getNext(); iter != g.adjList[i].getTail(); iter = iter->getNext()) {
            Edge *now = iter->getValue();
            if(now->id < m) {
                edge[now->id].flow = now->flow;
            }
        }
    }
    bool reach[n], cut[m];
    int minCut = 0;
    reachable(g, reach);
    for(int i = 0; i < m; i++) {
        cut[i] = false;
    }
    myOut << "MaxFlow: " << maxFlow << endl << endl;
    myOut << "Flow along edges: " << endl;
    for(int i = 0; i < m; i++) {
        int from = edge[i].from, to = edge[i].to;
        myOut << from << "->" << to << ": " << edge[i].flow << endl;
        if(reach[from] == true && reach[to] == false) {
            cut[i] = true;
            minCut += edge[i].capacity;
        }
    }
    myOut << endl;
    myOut << "Edges of minCut: " << endl;
    for(int i = 0; i < m; i++) {
        if(cut[i]) {
           myOut << edge[i].from << "->" << edge[i].to << endl;
        }
    }
    myOut << endl;
    ///CHECK
    cout << "minCut: " << minCut << endl;
    ///END-CHECK
    myOut.close();
}
