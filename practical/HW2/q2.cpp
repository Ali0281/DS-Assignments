#include <iostream>

using namespace std;

int main() {
    long long ans = 1, table, serial, control = 2, ansCounter = 0, save;
    cin >> serial;
    table = serial << 4;
    bool *prime = new bool[table];
    for (int i ; i < table ; i++) prime[i] = true;
    while (control<table) {
        if (prime[control] == true) {
            ans *= control;
            ans %= 1000000007;
            ansCounter++;
            if (ansCounter >= serial) break;
            for (long long i = control * 2; i<table; i+=control) prime[i] = false;
            save = control * control;
            if (save < table) prime[save] = true;
        }
        control++;
    }
    cout << ans << endl;
}


