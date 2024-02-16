#include <iostream>
#include <random>
using namespace std;

int main(int argc, char** argv) {
    int seed = stoi(argv[1]);
    mt19937 rnd(seed);
    int N = rnd() % 1000 + 1;
    int X = rnd() % 1000 + 1;
    cout << N << " " << X << "\n";
    char signs[3] = {'>', '<', '='};
    while(--N) {
        int t = rnd() % 3;
        cout << signs[t];
    }
    return 0;
}