#include <iostream>
#include <string>
#include <string.h>

using namespace std;

#define ll long long
const ll PRIME = 53;
const ll MOD = 1e9 + 7;
const ll MAX = 500000;
ll allTrees[10][MAX * 2];
ll lens[10];
ll allPrimes[MAX];

ll getPower(int i){
    if (allPrimes[i]==0){
        allPrimes[i] = getPower(i-1) * PRIME % MOD;
        return allPrimes[i];
    }else {
        return allPrimes[i];
    }
}

ll custom_hash(char chr , ll index){
    ll powerOfIndex = getPower(index);
    return ((chr - 'A' + 1) * (powerOfIndex % MOD)) % MOD;
}

void creatAndAddTree(string arr, ll tree_index)
{
    ll n = lens[tree_index];
    for (ll i=0; i<n; i++)
        allTrees[tree_index][n+i] = custom_hash(arr[i],i);
    for (ll i = n - 1; i > 0; --i)
         allTrees[tree_index][i] = allTrees[tree_index][i<<1] + allTrees[tree_index][i<<1 | 1];
}
void updateTreeNode(ll* tree,ll p, ll value, ll treeIndex)
{
    ll n = lens[treeIndex];
    tree[p+n] = value;
    p = p+n;
    for (ll i=p; i > 1; i >>= 1)
        tree[i>>1] = tree[i] + tree[i^1];
}

ll query(ll* tree,ll l ,ll r ,ll treeIndex) // [l,r)
{
    ll n = lens[treeIndex];
    ll res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1)
    {
        if (l&1)
            res += tree[l++];
        if (r&1)
            res += tree[--r];
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    allPrimes[0] = 1;
    allPrimes[1] = PRIME;
    ll input_count , command_count;
    ll commandMode ,treeIndex1 , treeIndex2 , startIndex1 , startIndex2 ,wordSize ;
    char chr;
    string input ;
    cin >> input_count >> command_count;
    for (ll i = 0; i < input_count; i++)
    {
        cin >> input;
        lens[i]= input.length();
        creatAndAddTree(input , i);
    }
    for (ll i = 0; i < command_count; i++)
    {
        cin >> commandMode;
        if (commandMode){
           cin >> treeIndex1 >> startIndex1 >> chr;
           updateTreeNode(allTrees[treeIndex1-1] ,startIndex1 ,custom_hash(chr , startIndex1),treeIndex1-1);
        }else {
            cin >> treeIndex1 >> treeIndex2 >> startIndex1 >> startIndex2 >> wordSize;
            ll hash1 = query(allTrees[treeIndex1-1] ,startIndex1-1 ,startIndex1 + wordSize - 1 , treeIndex1-1) % MOD;
            ll hash2 = query(allTrees[treeIndex2-1] ,startIndex2-1 ,startIndex2 + wordSize - 1 , treeIndex2-1) % MOD;
            if (startIndex1 > startIndex2 ){
                hash2 *= getPower(startIndex1 - startIndex2) % MOD;
            }else {
                hash1 *= getPower(startIndex2 - startIndex1) % MOD;
            }
            if (hash1% MOD == hash2 % MOD){
                cout << "YES" << endl;
            }else{
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}
