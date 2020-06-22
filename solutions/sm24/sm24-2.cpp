#include <cmath>
#include <exception>
#include <future>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <stdint.h>
#include <thread>
#include <vector>

bool is_prime(uint64_t num) {
    if (num <= 1) return false;
    uint64_t sq = std::sqrt(num);
    for (uint64_t i = 2; i < sq + 1; ++i) {
        if (!(num % i)) {
            return false;
        }
    }
    return true;
}

void generate_primes(uint64_t low, uint64_t high, std::vector<std::promise<uint64_t>>& p) {
    size_t pos = 0;
    for (uint64_t i = low; i <= high; ++i) {
        if (is_prime(i)) {
            p[pos].set_value(i);
            if (++pos == p.size()) {
                return;
            }
        }
    }
    try {
        throw high;
    } catch (...) {
        p[pos].set_exception(std::current_exception());
    }
}


int main() {
    uint64_t low, high;
    uint32_t count;
    std::cin >> low >> high >> count;
    std::vector<std::promise<uint64_t>> p(count);
    std::thread t(generate_primes, low, high, std::ref(p));
    try {
        for (auto& prom : p) {
            auto value = prom.get_future().get();
            std::cout << value << std::endl;
        }
    } catch (uint64_t ex) {
        std::cout << ex << std::endl;
    }
    t.join();
    return 0;
}
