#include <iostream>
#include <thread>
#include <queue>

using namespace std;
template <typename T>
class ThreadSafeQ {
private:
    queue<T> q;
    std::mutex mtx;
public:
    //ThreadSafeQ(){}
     void push(T t) {
         {
            std::lock_guard<std:: mutex> lck(mtx);
            cout << this_thread::get_id() << endl;
            q.push(t);
         }
     }

     void pop() {
         {
            std::lock_guard<std:: mutex> lck(mtx);
            q.pop();
         }
     }

     T top() {
         T top;
         {  
             std::lock_guard<std:: mutex> lck(mtx);
             top = q.top();
         }
         return top;
     }

     int size() {
         int sz = 0;
        {  
             std::lock_guard<std:: mutex> lck(mtx);
             sz = q.size();
         }
         return sz; 
     }
};
int main () {
    ThreadSafeQ<int> q;
    for(int i=0,j=i;i<10;i++) { 
        j = i+1;
        thread t1(&ThreadSafeQ<int>::push, &q, i);
        thread t2(&ThreadSafeQ<int>::push, &q, j);
        t1.join();
        t2.join();
    }
    cout << "Q size is "<< q.size() <<endl;



}