#include <iostream>
#include <thread>
#include <condition_variable>
#include <vector>
#include <queue>

using namespace std;

template <typename T>
class ThreadSafeQ {
private:
    queue<T> q;
    mutex mtx;
    condition_variable cond;
    int capacity;
public:
    ThreadSafeQ(int capacity):capacity(capacity) {}
    bool isFull() {
        return q.size() >= capacity;
    }
    bool isEmpty() {
        return q.size() <= 0;
    }
    void push(T t) {
        std::unique_lock<std::mutex> lock(mtx);
        cond.wait(lock, [this](){return !isFull();});
        cout <<"Pushed "<<t<<" to Queue!"<<endl; 
        q.push(t);
        lock.unlock();
        cond.notify_all();
    }

    void pop() {
        std::unique_lock<std::mutex> lock(mtx);
        cond.wait(lock, [this](){return !isEmpty();});
        cout << "Popped "<<q.front() << " from the Queue by " << this_thread::get_id() <<endl;
        q.pop();
        lock.unlock();
        this_thread::sleep_for(std::chrono::seconds(5));
        cond.notify_one();
    }
};

void produce (ThreadSafeQ<int>& q) {
    for(int i=0;i<5;i++) {
        q.push(i);
        int sl = rand() % 5;
       // this_thread::sleep_for(std::chrono::seconds(sl));
    }
}
int main() {
    ThreadSafeQ<int> q(2);
    thread producer(std::bind(produce,std::ref(q)));
    vector<std::thread> consumers;
    for(int i=0;i<5; i++ ) {
        consumers.push_back(thread(&ThreadSafeQ<int>::pop, &q));
    }
    producer.join();
    for(auto& th : consumers) {
        th.join();
    }
}
