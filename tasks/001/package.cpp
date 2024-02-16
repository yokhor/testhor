#include <bits/stdc++.h>

using namespace std;

const int SIZE = 2000000;
const int BASE = 2017;
const int MOD = 1000000009;
const int MOD2 = 1000000007;

int64_t ahash[SIZE];
int64_t bhash[SIZE];
int64_t ahash2[SIZE];
int64_t bhash2[SIZE];

int64_t powers[SIZE];
int64_t powers2[SIZE];

void init_powers(int64_t *p, int base, int mod){
    p[0] = 1;
    for(int i = 1; i <= SIZE; i++){
        p[i] = p[i-1] * base % mod;
    }
}

void init_hash(const string &line, int64_t *h, int base, int mod){
    h[0] = 0;
    for(int i = 1; i<=line.size(); i++){
        h[i] = h[i-1]*base%mod + (signed char)line[i-1] % mod;
    }
}

int64_t get_hash(int l, int r, int64_t *h, int64_t *p, int mod){
    return(h[r] - h[l] * p[r-l] % mod + mod)% mod;
}

int main()
{
    string a, b;
    cin >> a >> b;
    int k = a.size();
    int p = 0;
    for(int i = 0; i < b.size()-1; i++){
        a.push_back(a[p%a.size()]);
        p++;
    }
    init_hash(a, ahash, BASE, MOD);
    init_hash(b, bhash, BASE, MOD);
    init_powers(powers, BASE, MOD);
    init_hash(a, ahash2, BASE, MOD2);
    init_hash(b, bhash2, BASE, MOD2);
    init_powers(powers2, BASE, MOD2);
    int l = 0;
    int r = l+b.size();
    int e = 0;
    for(int i = r-1; i < a.size();i++){
        if(get_hash(l, i+1, ahash, powers, MOD) == get_hash(0, b.size(), bhash, powers, MOD) && get_hash(l, i+1, ahash2, powers2, MOD2) == get_hash(0, b.size(), bhash2, powers2, MOD2)){
            e++;
        }
        l++;
    }
    cout << e;
}