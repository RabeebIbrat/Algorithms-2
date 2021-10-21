#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "heap.h"
#include "disjoint_set.h"
#include "queue.h"
using namespace std;

class Edge {
public:
    int one, other, weight;
    bool operator<(Edge rhs) {
        return (weight < rhs.weight);
    }
    Edge(){}
    Edge(int n1, int n2, int w) {
        one = n1;
        other = n2;
        weight = w;
    }
    friend ostream& operator<<(ostream& os, const Edge& rhs);
};

ostream& operator<<(ostream& os, const Edge& rhs) {
    cout << rhs.one << " " << rhs.other << " " << rhs.weight;
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
    int nNode, nEdge;
    myIn >> nNode >> nEdge;
    SetLinker<bool> node[nNode];
    Edge edge[nEdge];
    MinHeap<Edge> pile;
    int p,q;
    int w;
    for(int i = 0; i < nEdge; i++) {
        myIn >> p >> q >> w;
        pile.throwIn(Edge(p,q,w));
    }
    //pile.print("", "; ");
    //cout << endl;
    Edge now;
    Queue<Edge> chosen;
    int cost = 0;
    for(int i = 0; i < nEdge; i++) {
        now = pile.pickUp();
        if(node[now.one].getHead() != node[now.other].getHead()) {
            chosen.enq(now);
            cost += now.weight;
            unionOf(node[now.one], node[now.other]);
        }
    }
    myIn.close();
    myOut.open(outFile.append(".txt").c_str());
    if(chosen.getSize() == nNode-1) {
        myOut << "Added edges: " << endl;
        while(!chosen.isEmpty()) {
            now = chosen.deq();
            myOut << "(" << now.one << "," << now.other << ")" <<  endl;
        }
        myOut << endl;
        myOut << "MST weight: " << cost << endl;
    }
    else {
        myOut << "MST doesn't exist." << endl;
    }
}
