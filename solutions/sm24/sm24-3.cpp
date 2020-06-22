#include <cmath>
#include <exception>
#include <future>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <stdlib.h>
#include <stdint.h>
#include <string>
#include <thread>
#include <vector>

constexpr int side_length = 5000;
constexpr int circle_radius = 2500;

std::vector<size_t> points(unsigned int seed, size_t iterations) {
    size_t in = 0;
    for (size_t i = 0; i != iterations; ++i) {
        int x = rand_r(&seed) % side_length;
        int y = rand_r(&seed) % side_length;
        if (std::pow(x - circle_radius, 2) + std::pow(y - circle_radius, 2) <= std::pow(circle_radius, 2)) {
            ++in;
        }
    }
    return { in, iterations };
}


int main(int argc, char * argv[]) {
    unsigned int threads = std::stoul(argv[1]);
    size_t iterations = std::stoul(argv[2]);
    std::vector<std::future<std::vector<size_t>>> fut;
    fut.reserve(threads);
    for (unsigned int i = 0; i != threads; ++i) {
        fut.emplace_back(std::async(std::launch::async, points, i, iterations));
    }
    double ratio = 0;
    for (auto& fu : fut) {
        std::vector<size_t> res = fu.get();
        ratio += (res[0] * 1.) / res[1];
    }
    std::cout << std::setprecision(10) << 4 * ratio / threads << std::endl;
    return 0;
}
