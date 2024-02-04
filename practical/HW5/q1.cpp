// with help of geek for geeks - disjoint set implementation
#include <bits/stdc++.h>

using namespace std;

class DisjSet {
    int *parent, *values, n;

public:
    DisjSet(int n, int inp[]) {
        parent = new int[n];
        values = inp;
        this->n = n;
        makeSet();
    }

    void makeSet() {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    int getMax(int x) {
        return values[find(x)];
    }

    void Union(int x, int y) {
        int xset = find(x);
        int yset = find(y);
        if (xset == yset)
            return;
        if (values[xset] < values[yset]) {
            parent[xset] = yset;
        } else {
            parent[yset] = xset;
        }
    }
};

int main() {
    int objCount, commandCount;
    cin >> objCount >> commandCount;
    int values[objCount];
    for (int i = 0; i < objCount; ++i) {
        cin >> values[i];
    }
    DisjSet obj(objCount, values);
    int inp1, inp2, inp3;
    for (int i = 0; i < commandCount; ++i) {
        cin >> inp1;
        switch (inp1) {
            case 1:
                cin >> inp2;
                cout << obj.getMax(inp2 - 1) << endl;
                break;
            case 2:
                cin >> inp2 >> inp3;
                obj.Union(inp2 - 1, inp3 - 1);
                break;
        }
    }
    return 0;
}