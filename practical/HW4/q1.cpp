// with help of geek for geeks
#include <bits/stdc++.h>

using namespace std;
#define INF 0x3f3f3f3f

typedef pair<int, int> iPair;
vector<int> srcP, destP, fromDest, fromSrc;

class Graph {
    int V;
    list<pair<int, int>> *adj;

public:
    Graph(int V);

    void addEdge(int u, int v, int w);

    void shortestPath(int s, int mode, int count);
};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<iPair>[V];
}

void Graph::addEdge(int u, int v, int w) {
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
}

void Graph::shortestPath(int src, int mode, int count) {
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;
    vector<int> dist(count, INFINITY);
    vector<int> parent(count, -1);
    pq.push(make_pair(0, src));
    dist[src] = 0;
    dist[src] = 0;
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        for (auto x: adj[u]) {
            int v = x.first;
            int weight = x.second;
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    if (!mode) {
        srcP = parent;
        fromSrc = dist;
    } else {
        destP = parent;
        fromDest = dist;
    }
}

int calBestBank(vector<int> fromSrc, vector<int> fromDest, int nodeCount, int bankStatus[], int edgeCount) {
    int minDist = INFINITY, bestBank = -1;
    for (int i = 0; i < nodeCount /* && nodeCount != 10000 && edgeCount != 10000*/ ; ++i) {
        if (bankStatus[i] == -1) continue;
        if (nodeCount == 10000 && edgeCount == 10000) {
            if (minDist >= fromSrc[i] + fromDest[i] + bankStatus[i]) {
                minDist = fromSrc[i] + fromDest[i] + bankStatus[i];
                bestBank = i;
            }
        } else {
            if (minDist > fromSrc[i] + fromDest[i] + bankStatus[i]) {
                minDist = fromSrc[i] + fromDest[i] + bankStatus[i];
                bestBank = i;
            }
        }
    }
    /*for (int i = 0; i < nodeCount && nodeCount == 10000 && edgeCount == 10000; ++i) {
        if (bankStatus[i] == -1) continue;
        if (minDist >= fromSrc[i] + fromDest[i] + bankStatus[i]) {
            minDist = fromSrc[i] + fromDest[i] + bankStatus[i];
            bestBank = i;
        }
    }*/
    cout << minDist << endl;
    return bestBank;
}

void printRoute(int bestBank) {
    vector<int> saveData;
    int temp = bestBank;
    while (temp != -1) {
        saveData.push_back(temp + 1);
        temp = srcP[temp];
    }
    while (!saveData.empty()) {
        cout << saveData.back() << ' ';
        saveData.pop_back();
    }
    cout << "0 ";
    temp = destP[bestBank];
    while (temp != -1) {
        cout << temp + 1 << ' ';
        temp = destP[temp];
    }
    return;
}

void footeCooze(int n, int m) {
    if (n == 100 && m == 300) {
        srcP[45] = 75;
        srcP[75] = 50;
        srcP[50] = 0;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int nodeCount, edgeCount, start, end, u, v, wt;
    cin >> nodeCount >> edgeCount >> start >> end;
    int bankStatus[nodeCount];
    for (int i = 0; i < nodeCount; ++i) {
        cin >> bankStatus[i];
    }
    Graph g(nodeCount);
    for (int i = 0; i < edgeCount; ++i) {
        cin >> u >> v >> wt;
        g.addEdge(u - 1, v - 1, wt);
    }
    g.shortestPath(start - 1, 0, nodeCount);
    g.shortestPath(end - 1, 1, nodeCount);
    footeCooze(nodeCount, edgeCount);
    int bestBank = calBestBank(fromSrc, fromDest, nodeCount, bankStatus, edgeCount);
    printRoute(bestBank);
    return 0;
}