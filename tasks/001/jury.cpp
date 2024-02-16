//#pragma optimize("O2");
//#pragma optimize("unroll-loops");

//#pragma target("avx2,bmi,bmi2,popcnt,lzcnt");

//#define _CRT_SECURE_NO_WARNINGS
//#define _GLIBCXX_DEBUG

//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <cassert>
#include <iomanip>
#include <chrono>
#include <random>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

//#include <ext/pb_ds/assoc_container.hpp>
//using namespace __gnu_pbds;
//#define unmap gp_hash_table

using namespace std;
using li = long long int;
using unt = unsigned int;
using uli = unsigned long long;
using pii = pair<int, int>;
using pll = pair<li, li>;
using vint = vector<int>;
using vli = vector<li>;
using vvint = vector<vector<int>>;
using vvli = vector<vector<li>>;
using sint = set<int>;
using db = double;
using ldb = long double;
using point = pair<ldb, ldb>;
//using lint = __int128;

#define X first
#define Y second
#define pb push_back
#define eb emplace_back
#define heap priority_queue
#define unmap unordered_map
#define unset unordered_set

#define dbg(x) cerr << "===\t" << #x << " = " << x << "\t===\n";
//#define int long long

//mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
mt19937 rnd(42);

const int INF = 2e9 + 1e7;
const li P = 2;
const li MOD = 1e9 + 9;
const int P2 = 3;
const li MOD2 = 1e9 + 9;
//const ldb PI = acos(-1);
//const ldb EPS = 1e-2;
const uli MAXINT = 2147483647;
const int MAX = 1e6;

li qp(li a, int n, int mod) {
    li res = 1;
    while (n > 0) {
        if (n & 1) {
            res = res * a % mod;
            n--;
        }
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

uli qp(uli a, int n) {
    uli res = 1;
    while (n > 0) {
        if (n & 1) {
            res = res * a;
            n--;
        }
        a = a * a;
        n >>= 1;
    }
    return res;
}

void solve() {
    string s, t; cin >> s >> t;
    int init = s.size();
    do {
        s += s;
    } while (s.size() - init < t.size());
    static pair<li, uli> p_hash_s[2 * MAX + 1];
    static pair<li, uli> hash_t = { 0, 0 };
    p_hash_s[0] = { 0, 0 };
    for (int i = 0; i < s.size(); i++) {
        p_hash_s[i + 1].X = (p_hash_s[i].X * P + s[i]) % MOD;
        p_hash_s[i + 1].Y = (p_hash_s[i].Y * P2 + s[i]);
    }
    for (int i = 0; i < t.size(); i++) {
        hash_t.X = (hash_t.X * P + t[i]) % MOD;
        hash_t.Y = hash_t.Y * P2 + t[i];
    }
    int l = t.size();
    int cnt = 0;
    li Pl = qp(P, l, MOD);
    uli P2l = qp(P2, l);
    for (int i = 0; i < init; i++) {
        pair<li, uli> hash_s;
        hash_s.X = (p_hash_s[i + l].X - (p_hash_s[i].X * Pl) % MOD + MOD) % MOD;
        hash_s.Y = p_hash_s[i + l].Y - p_hash_s[i].Y * P2l;
        if (hash_s == hash_t) cnt++;
    }
    cout << cnt;
}

signed main()
{
    //cout.tie(nullptr);

    //FILE* fpi = freopen("9.txt.csv", "r", stdin);
    //FILE* fpo = freopen("OUTPUT.TXT", "w", stdout);

    //chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    solve();


    //chrono::steady_clock::time_point end = chrono::steady_clock::now();
    //cerr << "\n\n";
    //cerr << "Execution time: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " [ms]\n";

    //fclose(fp);

    return 0;
}


