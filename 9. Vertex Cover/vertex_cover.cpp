#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
#include "linked_list.h"
#include "queue.h"
using namespace std;

struct Edge {
    int from, to;
};

struct EdgePlus {
    int to;
    Linker<EdgePlus*> *opposite;
    int index;
    EdgePlus(int to, int index) {
        this->to = to;
        this->index = index;
    }
};

void clearVertex(int i, LinkedList<EdgePlus*> *adjList, Edge *edge) {
    for(Linker<EdgePlus*> *it = adjList[i].getHead()->getNext(); it != adjList[i].getTail(); it = it->getNext()) {
        edge[it->getValue()->index].from = 0;
        adjList[it->getValue()->to].deletes(it->getValue()->opposite);
        adjList[i].deletes(it);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int n,m;
    cin >> n >> m;

    int serial[m];
    for(int i = 0; i < m; i++) {
        serial[i] = i+1;
    }
    srand(time(0));
    random_shuffle(serial, serial+m);

    LinkedList<EdgePlus*> adjList[n+1];
    Edge edge[m+1];

    for(int i = 0; i < m; i++) {
        int from, to, index = serial[i];
        cin >> from >> to;
        edge[index].from = from;
        edge[index].to = to;
        EdgePlus *one = new EdgePlus(to,index), *other = new EdgePlus(from,index);
        adjList[from].pushBack(one);
        adjList[to].pushBack(other);
        one->opposite = adjList[to].getTail()->getPrev();
        if(from == to) {
            other->opposite = adjList[from].getTail()->getPrev()->getPrev();
        }
        else  {
            other->opposite = adjList[from].getTail()->getPrev();
        }
    }

    Queue<int> chosen;
    for(int i = 1; i <= m; i++) {
        if(edge[i].from == 0)  continue;
        int u = edge[i].from, v = edge[i].to;
        chosen.enq(u);
        if(u != v) {
            chosen.enq(v);
        }
        clearVertex(u, adjList, edge);
        clearVertex(v, adjList, edge);
    }
    cout << "{ ";
    chosen.print("", ", ");
    cout << "\b\b }" << endl;
    cout << "Size: " << chosen.getSize() << endl;
    chosen.clear();

    string str;
    getline(cin,str);
    getline(cin,str);
    return 0;
}
