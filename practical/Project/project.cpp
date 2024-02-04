//with help of :
// https://usaco.guide/adv/treaps?lang=cpp#cut-and-paste---solution
// https://cp-algorithms.com/data_structures/treap.html#implicit-treaps
// geekforgeeks

#include <bits/stdc++.h>
#include <climits>
#include <cstdlib>
#include <iostream>

using namespace std;
// tree from first source
unordered_map<int, int> custom_map;

int custom_hash(int key) {
    if (custom_map.find(key) == custom_map.end())
        custom_map[key] = rand();
    return custom_map[key];
}

struct Node {
    int odd, size, value, savedMax;
    double priority;
    Node *l, *r;

    explicit Node(int c, double random) : odd(custom_hash(c)), value(c), savedMax(value),
                                          priority(random), size(1), l(NULL), r(NULL) {}
} *root;

inline int size(Node *t) {
    return t ? t->size : 0;
}

inline int savedMax(Node *&t) {
    return !t ? INT_MIN : t->savedMax;
}

inline int odd(Node *&t) {
    return !t ? 0 : t->odd;
}

void upd_savedMax(Node *&t) {
    if (t) t->savedMax = max(t->value, max(savedMax(t->l), savedMax(t->r)));
}

void upd_odd(Node *&t) {
    if (t) t->odd = odd(t->r) ^ odd(t->l) ^ custom_map[t->value];
}

void split(Node *t, Node *&l, Node *&r, int value) {
    if (!t) return void(l = r = nullptr);
    else if (size(t->l) < value)
        split(t->r, t->r, r, value - size(t->l) - 1), l = t;
    else
        split(t->l, l, t->l, value), r = t;
    t->size = 1 + size(t->l) + size(t->r);
    upd_savedMax(t);
    upd_odd(t);
}

void merge(Node *&t, Node *l, Node *r) {
    if (!l || !r) return void(t = l ? l : r);
    else if (l->priority < r->priority)
        merge(l->r, l->r, r), t = l;
    else
        merge(r->l, l, r->l), t = r;
    t->size = 1 + size(t->l) + size(t->r);
    upd_savedMax(t);
    upd_odd(t);
}

int calculateMax(Node *&t, int s, int e) {
    // if (e-s == 1) {}
    Node *tr, *tm, *tl;
    split(t, tl, tr, e);
    split(tl, tl, tm, s);
    int temp = savedMax(tm);
    merge(tl, tl, tm);
    merge(t, tl, tr);
    return temp;
}

void customShift(Node *&t, int s, int e, int count) {
    if (e - s == 1) return;
    count %= e - s;
    Node *tl, *tmm, *tml, *tmr, *tr;
    split(t, tl, tr, e);
    split(tl, tl, tmm, s);
    split(tmm, tml, tmr, e - s - count);
    merge(tmm, tmr, tml);
    merge(tl, tl, tmm);
    merge(t, tl, tr);
}

void output(Node *t) {
    if (!t) return;
    output(t->l);
    printf("%d ", t->value);
    output(t->r);
}

void inputMax() {
    int s, e;
    cin >> s >> e;
    cout << calculateMax(root, s - 1, e - 1) << endl;
}

void inputShift() {
    int s, e, c;
    cin >> s >> e >> c;
    customShift(root, s - 1, e - 1, c);
}

string checkEven(Node *&t, int s, int e) {
    Node *l, *m, *r;
    split(t, l, m, s);
    split(m, m, r, e - s + 1);
    int temp = odd(m);
    merge(t, l, m);
    merge(t, t, r);
    if (temp != 0) return "Yes";
    return "No";
}

void inputEven() {
    int s, e;
    cin >> s >> e;
    cout << checkEven(root, s - 1, e - 2) << endl;
}

int main() {
    int n, q, input;
    string mode;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> input;
        merge(root, root, new Node(input, rand()));
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> mode;
        if (mode == "max") inputMax();
        else if (mode == "shift") inputShift();
        else if (mode == "even") inputEven();
    }
    return 0;
}
