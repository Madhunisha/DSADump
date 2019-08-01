#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>

using namespace std;
// Implementation with Conditional Variables
class RWLock {
public:
    void readLock() {
        std::unique_lock<mutex> lock(mut);
        waitingReaders.wait(lock, [&](){return !writer && queuedWriters == 0;});
        ++readers;
    }
    void readUnlock() {
        std::unique_lock<std::mutex> lock(mut);
        --readers;
        if (readers == 0 && queuedWriters > 0) {
            lock.unlock();
            waitingWriters.notify_one();
        }
    }

    void writeLock() {
        std::unique_lock<std::mutex> lock(mut);
        ++queuedWriters;
        waitingWriters.wait(lock, [&]{return !writer && readers == 0;});
        --queuedWriters;
        writer = true;
    }
    void writeUnlock() {
        std::unique_lock<std::mutex> lock(mut);
        if(queuedWriters > 0) {
            writer = false;
            lock.unlock();
            waitingWriters.notify_all();
        } else {
            writer = false;
            lock.unlock();
            waitingReaders.notify_all();
        }
    }

private:
    mutex mut;
    condition_variable waitingReaders;
    condition_variable waitingWriters;
    int readers = 0;
    int queuedWriters = 0;
    bool writer = false;
};

void read(RWLock& lock) {
    lock.readLock();
    int i = 2;
    while(i>=0) {
        cout << "Reading "<<i--<<" by thread "<< this_thread::get_id() <<endl;
        this_thread::sleep_for(chrono::duration(1s));
    }
    lock.readUnlock();
}
void write(RWLock& lock) {
    lock.writeLock();
    int i = 2;
    while(i>=0) {
        cout << "Writing "<<i--<<" by thread "<< this_thread::get_id() <<endl;
        this_thread::sleep_for(chrono::duration(1s));
    }
    lock.writeUnlock();
}

int main() {
    RWLock lock;
    thread t1(read, std::ref(lock));
    thread t2(read, std::ref(lock));
    thread t3(write, std::ref(lock));
    thread t4(write, std::ref(lock));
    thread t5(read,std::ref(lock));
    thread t6(read, std::ref(lock));
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    return 0;
}