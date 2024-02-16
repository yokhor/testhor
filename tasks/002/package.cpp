//#pragma GCC optimize("O2")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")
//#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

//#define int long long
using ll = long long;
using unt = unsigned int;
using uli = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vint = vector<int>;
using vpii = vector<pii>;
using vli = vector<ll>;
using vvint = vector<vector<int>>;
using vvli = vector<vector<ll>>;
using db = double;
using ldb = long double;
using point = pair<ldb, ldb>;
//using lint = __int128;

#define X first
#define Y second
#define pb push_back
#define mp make_pair
#define eb emplace_back
#define heap priority_queue
//#define unmap unordered_map
#define unmap gp_hash_table
#define unset unordered_set

#define dbg(x) cerr << "===\t" << #x << " = " << x << "\t===\n";

//mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
//mt19937 rnd(42);

void solve() {
    int N, Q; cin >> N >> Q;
    vector<pii> events; events.reserve(Q);
    while(Q--) {
        int x, d; cin >> x >> d;
        int l = x - d; l = max(l, 0);
        int r = x + d; r = min(r, N);
        events.pb({l, r});
    }
    sort(events.begin(), events.end());
    int prev = 1;
    int sum = 0;
    for (int i = 0; i < events.size(); i++) {
        sum += max(events[i].X - prev, 0);
//        assert(events[i].Y + 1 >= prev);
        prev = max(prev, events[i].Y + 1);
    }
    sum += max(N + 1 - prev, 0);
    cout << sum;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    //cout.tie(nullptr);

//    freopen("/home/yokhor/CLionProjects/chor/input.txt", "r", stdin);
//    freopen("/home/yokhor/CLionProjects/chor/output.txt", "w", stdout);

    //chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    solve();

    //chrono::steady_clock::time_point end = chrono::steady_clock::now();
    //cerr << "\n\n";
    //cerr << "Execution time: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " [ms]\n";

    //fclose(fp);

    return 0;
}
