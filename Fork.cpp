#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

class Fork {
private:
    mutable std::mutex mutex_;

public:
    Fork() {}

    Fork(Fork const &other) {
        std::unique_lock<std::mutex> lock_other(other.mutex_);
    }

    void lock() {
        mutex_.lock();
    }

    void unlock() {
        mutex_.unlock();
    }
};