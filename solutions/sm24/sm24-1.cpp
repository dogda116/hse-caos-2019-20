#include <iomanip>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

constexpr int ITERATIONS = 1000000;
constexpr int THREADS = 3;
volatile double arr[THREADS];


void process(std::mutex& m, int pos1, double add, int pos2, double subtract) {
    for (int i = 0; i != ITERATIONS; ++i) {
        std::lock_guard<std::mutex> lock(m);
        arr[pos1] += add;
        arr[pos2] -= subtract;
    }
}


int main() {
    std::mutex m;
    std::thread t1(process, std::ref(m), 0, 80., 1, 90.);
    std::thread t2(process, std::ref(m), 1, 100., 2, 110.);
    std::thread t3(process, std::ref(m), 2, 120., 0, 130.);
    t1.join();
    t2.join();
    t3.join();
    for (int i = 0; i != THREADS; ++i) {
        std::cout << std::setprecision(10) << arr[i] << std::endl;
    }
    return 0;
}
