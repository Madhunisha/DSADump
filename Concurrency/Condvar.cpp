#include <iostream>
#include <vector>
#include <mutex>
#include <thread>

using namespace std;

vector<int> sharedWork;
mutex _mut;
condition_variable condVar;

bool dataReady;

void waitingForWork(){
    unique_lock<mutex> lck(_mut);
    condVar.wait(lck, []{return dataReady; });
    sharedWork[1] = 2;
    std::cout << "Work done " << std::endl;
}

void setReady() {
    sharedWork = {1,0,3};
    {
        std::lock_guard<std::mutex> lck(_mut);
        dataReady = true;
    }
    std::cout << "Data prepared" << std::endl;
    condVar.notify_one();
}

int main() {
    thread t1(waitingForWork);
    thread t2(setReady);

    t1.join();
    t2.join();
    for(auto const& val: sharedWork) 
        cout << val <<"|";
    cout << endl;

    return 0;
}