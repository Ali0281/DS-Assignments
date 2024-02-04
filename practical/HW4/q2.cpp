#include <bits/stdc++.h>

using namespace std;
#define INF 0x3f3f3f3f

typedef pair<int, int> iPair;

void addEdge(vector<pair<int, int> > adj[], int u, int v) {
    adj[u].push_back(make_pair(v, 0));
    adj[v].push_back(make_pair(u, 1));
}

void shortestPath(vector<pair<int, int> > adj[], int V,
                  int src, int dest) {
    priority_queue<iPair, vector<iPair>, greater<iPair> >
            pq;
    vector<int> dist(V, INF);
    pq.push(make_pair(0, src));
    dist[src] = 0;
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        for (auto x: adj[u]) {
            int v = x.first;
            int weight = x.second;
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    printf("%d", dist[dest]);
}

int main() {
    int nodeCount, edgeCount, start, end, u, v;
    cin >> nodeCount >> edgeCount >> start >> end;
    vector<iPair> adj[nodeCount];
    for (int i = 0; i < edgeCount; ++i) {
        cin >> u >> v;
        addEdge(adj, u - 1, v - 1);
    }
    shortestPath(adj, nodeCount, start - 1, end - 1);

    return 0;
}