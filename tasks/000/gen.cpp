#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    int seed = stoi(argv[1]);
    mt19937 rnd(seed);
    int a = rnd() % int(1e9);
    int b = rnd() % int(1e9);
    cout << a << " " << b;
    return 0;
}
