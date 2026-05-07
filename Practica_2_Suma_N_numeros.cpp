#include <iostream>
#include <chrono>
#include <vector>
#include <iomanip>
using namespace std;
using namespace std::chrono;

long long sumaBucle(int n) {
    long long suma = 0;
    for (int i = 1; i <= n; i++) {
        suma += i;
    }
    return suma;
}

long long sumaFormula(int n) {
    return 1LL * n * (n + 1) / 2;
}

double tiempoEnMicros(auto&& fn) {
    auto start = high_resolution_clock::now();
    fn();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    return duration.count();
}

int main() {
    vector<int> ns = {1000, 10000, 100000, 1000000};

    cout << setw(12) << "n"
         << setw(12) << "Bucle (μs)"
         << setw(12) << "Formula (μs)" << endl;
    cout << string(36, '-') << endl;

    for (int n : ns) {
        double tBucle = tiempoEnMicros([&]{
            volatile long long x = sumaBucle(n);
        });
        double tFormula = tiempoEnMicros([&]{
            volatile long long x = sumaFormula(n);
        });

        cout << setw(12) << n
             << setw(12) << tBucle
             << setw(12) << tFormula << endl;
    }

    return 0;
}
