#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    int seed = stoi(argv[1]);
    mt19937 rnd(seed);
    uniform_int_distribution<int> string_length(1, 1e6);
    int n = string_length(rnd);
    int m = string_length(rnd);
    if (m > n) swap(n, m); // tmp
    uniform_int_distribution<int> char_range('a', 'z');
    string s = "", t = "";
    for (int i = 0; i < n; i++) s.push_back(char_range(rnd));
    for (int i = 0; i < m; i++) t.push_back(char_range(rnd));
    cout << s << endl << t;
    return 0;
}
