#include <cmath>

#include <iostream>
#include <random>
#include <chrono>

using namespace std;

int main(int argc, char* argv[]) {
    std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);

    int n = atoi(argv[1]);
    std::cout << n << '\n';

    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::normal_distribution<double> dist(0., sqrt(n));

    for (int rep = 1; rep <= n; ++rep) {
        int v = dist(rng);
        if (v < 0) v = -v;
        v = std::min(v, n);
        std::cout << v << " \n"[rep == n];
    }
    
    return 0;
}
