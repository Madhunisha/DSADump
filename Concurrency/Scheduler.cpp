#include <iostream>
#include <vector>
#include <thread>
#include <condition_variable>
#include <queue>
#include <chrono>
#include <ctime>

class Task {
public:
    virtual void run() = 0;
    virtual ~Task() {}
};

class Task1 : public Task {
    
    std::mutex mut; 
public:
    int id;
    Task1(int id) :id(id) {};
    void run() {
        std::lock_guard<std::mutex> lck(mut);
        std::cout << "Running task: "<< id << std::endl;
    }
};
class Scheduler {
    std::priority_queue<std::pair<std::chrono::system_clock::time_point, Task*>> pq;
    std::vector<std::thread> thPool;
    std::vector<Task *> tasksReadyToRunQueue;
    std::mutex workMut, timerMut;
    std:: condition_variable timerCv, workCv;
    int thPoolSize;
    std::atomic<bool> done;
    std::queue<Task*> tasksReadyToRunQ;
public:
Scheduler():done(false),thPoolSize(4) {
    for(int i = 0; i < thPoolSize; i++) {
        thPool.push_back(std::thread(&Scheduler::worker, this));
    }
    std::thread timerThread(&Scheduler::timer, this);
    timerThread.detach();
    for(auto& t : thPool)
        t.detach();
}
void setDone() {
    done = true;
} 

void worker() {
    for(;;) {
       if(done)  break;
       std::unique_lock<std::mutex> lck(workMut); 
       workCv.wait(lck, [this] { return !tasksReadyToRunQ.empty();});

       Task* task = tasksReadyToRunQ.front();
       tasksReadyToRunQ.pop();
        lck.unlock();
        task->run();
        delete task;
    }
}

void timer() {
    for(;;) {
        if(done)  break;
        std::unique_lock<std::mutex> lck(timerMut);
        if(pq.size() !=0) {
            auto now = std::chrono::system_clock::now();
            auto top = pq.top();
            
            auto task = top.second;
            auto duration = top.first - now;
            if(now >= top.first) {
                pq.pop();
                std::unique_lock<std::mutex> wlck(workMut);
                tasksReadyToRunQ.push(task);
                wlck.unlock();
                workCv.notify_one();
            }
            else {
                timerCv.wait_for(lck, duration);
            }
        }
        else {
            std::cout << "Waiting . . .\n";
            timerCv.wait_for(lck, std::chrono::seconds(1));

        }
    }

}

void addTask(Task* task, std::chrono::seconds after ){
    std::chrono::system_clock::time_point  time_now = std::chrono::system_clock::now();
    time_now+=after;
    std::lock_guard<std::mutex> lock(timerMut);
    pq.push(make_pair(time_now,task));
    std::cout << "Added task " << std::endl;
    timerCv.notify_one();
}
};

int main() {

    Scheduler sched;
    Task* t0 = new Task1(0);
    Task* t1 = new Task1(1);
    Task* t2 = new Task1(2);
    Task* t3 = new Task1(3);
    Task* t4 = new Task1(4);
    Task* t5 = new Task1(5);
    std::cout << "main\n";
    sched.addTask(std::move(t0), std::chrono::seconds(0));
    std::this_thread::sleep_for(std::chrono::seconds(3));
    sched.addTask(std::move(t1), std::chrono::seconds(2));
    std::this_thread::sleep_for(std::chrono::seconds(3));
    sched.addTask(std::move(t2), std::chrono::seconds(3));
    std::this_thread::sleep_for(std::chrono::seconds(3));
    sched.addTask(std::move(t3), std::chrono::seconds(4));
    std::this_thread::sleep_for(std::chrono::seconds(3));
    sched.addTask(std::move(t4), std::chrono::seconds(5));
    sched.addTask(std::move(t5), std::chrono::seconds(6));

    std::this_thread::sleep_for(std::chrono::seconds(15));
    sched.setDone();
    return 0;
}