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
void async_launch(Function &&f, Callback &&c, Arguments &&... as) {
    std::async(std::launch::async, [](auto &&func, auto &&cb, auto &&... args) {
            return std::forward<decltype(cb)>(cb)(std::forward<decltype(func)>(func)(
                    std::forward<decltype(args)>(args)...));
        },
        std::forward<Function>(f), std::forward<Callback>(c), std::forward<Arguments>(as)...).get();
}
