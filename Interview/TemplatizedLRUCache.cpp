#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;
template <typename T, typename U>
class LRUCache {
    int capacity;
    unordered_map<T, pair<U, typename std::list<T>::iterator>> cache;
    list<T> used;
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    
    void touch(typename unordered_map<T, pair<U, typename std::list<T>::iterator>>::iterator it) {
        auto key = it->first;
        auto val = it->second.first;
        used.erase(it->second.second);
        used.push_front(key);
        cache[key] = make_pair(val,used.begin());
        
    }
    U get(T key) {
         auto it = cache.find(key);
        if(it != cache.end()) {
            touch(it);
            return cache[key].first;
        }
        return U();
    }
    
    void put(T key, U value) {
        auto it = cache.find(key);
        if(it != cache.end())
            touch(it);
        else {
            if(used.size() == capacity) {
                cache.erase(used.back());
                used.pop_back();
            }
            used.push_front(key);
        }
        cache[key] = {value, used.begin()};
        
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
int main() {
    int capacity = 2;
    LRUCache<int,string>* obj = new LRUCache<int,string>(capacity);
    obj->put(1,"one");
    obj->put(2,"two");
    cout << obj->get(1)<<endl;
    obj->put(3,"three");
    cout << obj->get(2) <<endl;
    obj->put(4,"four");
    cout << obj->get(1) <<endl;
    cout << obj->get(3) <<endl;
    cout << obj->get(4) <<endl;
}