#include <iostream>
#include <thread>
#include <mutex>

std::mutex m;

void DoSomething(int k) {

    for (;k > 0; --k) {
        std::lock_guard<std::mutex> lk(m);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "DoSomething function" << std::endl;
    }
}

struct TDoSomething {
    void operator()(int k) const {
        for (;k > 0; --k) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "TDoSomething functor" << std::endl;
        }
    }
};


int main() {
    std::thread t(DoSomething, 5);
    t.detach();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout.flush();

    return 0;
}
