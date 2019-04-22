#include <thread>
#include <iostream>
#include <atomic>

const int  MAX_PASS  = 500000;

void ping(std::atomic<int>& flag) {
    int ctr = 0;
    while (ctr < MAX_PASS) {
        auto val = flag.load();
        if(val  % 2 == 0) {
            std::cout << "ping" << std::endl;
            ctr++;
            flag.store(val + 1);
        };
    };
};


void pong(std::atomic<int>& flag) {
    int ctr = 0;
    while (ctr < MAX_PASS) {
        auto val = flag.load();
        if(val  % 2 == 1) {
            std::cout << "pong" << std::endl;
            ctr++;
            flag.store(val + 1);
        };
    };
};


int main() {

    std::atomic<int> flag(0);

    std::thread thread_1(ping, std::ref(flag));
    std::thread thread_2(pong, std::ref(flag));


    thread_1.join();
    thread_2.join();
    return 0;
};
