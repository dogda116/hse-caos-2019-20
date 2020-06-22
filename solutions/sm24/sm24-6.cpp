#include <chrono>
#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <stdint.h>
#include <thread>
#include <vector>
#include <utility>


template <typename Function, typename Callback, typename... Arguments>
void async_launch2(Function &&f, Callback &&c, Arguments &&... as) {
    std::async(std::launch::async, [](auto &&func, auto &&cb, auto &&... args) {
            return std::forward<decltype(cb)>(cb)(std::forward<decltype(func)>(func)(
                    std::forward<decltype(args)>(args)...));
        },
        std::forward<Function>(f), std::forward<Callback>(c), std::forward<Arguments>(as)...).get();
}


template<class Input, class Output, class Function, class Callback>
void async_vector(const std::vector<Input> ins, Function &&f, Callback &&c) {
    std::vector<Output> outs;
    for (auto elem : ins) {
        async_launch2(std::ref(f), [&](auto v) { outs.emplace_back(v); }, elem);
    }
    c(outs);
}
