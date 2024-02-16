//#pragma GCC optimize("O2")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")
//#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

#define int long long
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

//#define X first
//#define Y second
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

int MAXN = 1000;
int MAXX = 1000;
int MOD = 1e9 + 7;

void solve() {
    int N, X; cin >> N >> X;
    string s; cin >> s;
    ll dp[MAXN][MAXX];
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < X; j++) {
            dp[i][j] = 0;
        }
    }
    for (int j = 0; j < X; j++) {
        dp[N - 1][j] = 1;
    }
    for (int i = N - 2; i >= 0; i--) {
        if (s[i] == '=') {
            for (int j = 0; j < X; j++) {
                dp[i][j] = dp[i + 1][j]; dp[i][j] %= MOD;
            }
        } else if (s[i] == '>') {
            for (int j = X - 1; j >= 0; j--) {
                dp[i][X - 1] += dp[i + 1][j]; dp[i][X - 1] %= MOD;
            }
            dp[i][X - 1] -= dp[i + 1][X - 1];
            for (int j = X - 2; j >= 0; j--) {
                dp[i][j] = dp[i][j + 1] - dp[i + 1][j]; dp[i][j] %= MOD;
            }
        } else { // <
            for (int j = 0; j < X; j++) {
                dp[i][0] += dp[i + 1][j]; dp[i][0] %= MOD;
            }
            dp[i][0] -= dp[i + 1][0];
            for (int j = 1; j < X; j++) {
                dp[i][j] = dp[i][j - 1] - dp[i + 1][j]; dp[i][j] %= MOD;
            }
        }
    }
    int ans = 0;
    for (int j = 0; j < X; j++) {
        ans += dp[0][j]; ans %= MOD;
    }
    ans = (ans + MOD) % MOD;
//    assert(ans > 0);
    cout << ans;
}

signed main() {
//    ios_base::sync_with_stdio(false);
//    cin.tie(nullptr);
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
