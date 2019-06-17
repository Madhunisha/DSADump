#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
using namespace std;

template<typename T>
class ProducerConsumerQueue {
private:
    std::condition_variable cond;
    std::mutex mut;
    queue<T> q;
    int maxSize;
public:
    ProducerConsumerQueue(int sz):maxSize(sz){}
    bool isFull() const
    {
        return q.size() >= maxSize;
    }

    bool isEmpty() const
    {
        return q.size() == 0;
    }
    void add(T req){
        std::unique_lock<std::mutex> lock(mut);
        cond.wait(lock, [this](){
            return !isFull();
        });
        cout <<"Added "<<req<<" to Queue!"<<endl; 
        q.push(req);
        lock.unlock();
        cond.notify_all();
    }

    void consume(T &req){
        std::unique_lock<std::mutex> lock(mut);
        cond.wait(lock, [this]{
            return !isEmpty();
        });
        req = q.front();
        cout <<"Removed "<<req<<" from Queue!"<<endl; 
        q.pop();
        lock.unlock();
        cond.notify_all();
    }
    void produceWrapper(int cnt) {
        vector<std::thread> mthreads;
        for(int i=0;i<cnt;i++) {
            std::thread t1([this,i] {
                this->add(i);
            });
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            t1.join();
        }
    }
    void consumeWrapper(int cnt) {
        for(int i=0;i<cnt;i++){
            int ret;
            std::thread t1([this,&ret] {
                this->consume(ret);
                cout << "Consumed "<< ret << endl;
            });
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            t1.join();
            

        }
    }

};

int main() {
    int sz = 5;
    ProducerConsumerQueue<int> p(5);
    std::thread t1(&ProducerConsumerQueue<int>::produceWrapper,&p,10);
    std::thread t2(&ProducerConsumerQueue<int>::consumeWrapper,&p,10);
    t1.join();
    t2.join();
    return 0;
}
