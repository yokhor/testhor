#include <iostream>
#include <random>
using namespace std;

int main(int argc, char** argv) {
    int seed = stoi(argv[1]);
    mt19937 rnd(seed);
    int N = rnd() % (int)1e9 + 1;
    int Q = rnd() % (int)1e5 + 1;
    cout << N << " " << Q << "\n";
    while(Q--) {
        int x = rnd() % N + 1;
        int d = rnd() % N;
        cout << x << " " << d << "\n";
    }
    return 0;
}
