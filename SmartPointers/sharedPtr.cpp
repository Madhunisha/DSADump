// Referecence - https://www.acodersjourney.com/implementing-smart-pointer-using-reference-counting/
// https://www.learncpp.com/cpp-tutorial/15-3-move-constructors-and-move-assignment/
#include <iostream>
#include <string>

using namespace std;

class RefCnt {
private:
    int refCnt;
public:
    RefCnt(){
        refCnt=0;
    }

    void increment(){
        refCnt++;
    }

    int decrement(){
        refCnt--;
        return refCnt;
    }

    int getCnt(){
        return refCnt;
    }
};

template<typename T>
class SmartPtr {
private:
    T* obj;
    RefCnt* cnt;
public:
    SmartPtr()
    :obj(nullptr)
    ,cnt(nullptr) 
    {}

    SmartPtr(T* objc)
    :obj{objc}
    ,cnt{new RefCnt()}
    {
        cnt->increment();
        cout << "Created smart_ptr! Ref count is " << cnt->getCnt() << endl;

    }
    virtual ~SmartPtr(){
        if(cnt){
            cnt->decrement();
            if(cnt->getCnt() <=0){
                delete obj;
                delete cnt;
                obj=nullptr;
                cnt = nullptr;
            }
        }
    }

    SmartPtr(SmartPtr<T>& obj2)
    :obj{obj2.obj},
    cnt{obj2.cnt}
    {
        cnt->increment();
        cout << "Copied smart_ptr! Ref count is " << cnt->getCnt() << endl;
    }

    SmartPtr<T>& operator=(const SmartPtr<T>& other){
        if(this != &other){
            if(cnt && cnt->decrement() == 0){
                delete obj;
                delete cnt;
            }
            obj = other.obj;
            cnt = other.cnt;
            cnt->increment();
        }
        cout << "Assigned smart_ptr! Ref count is " << cnt->getCnt() << endl;   
        return *this; 
    }

    T& operator* () {
        return *obj;
    }
    T* operator->(){
        return obj;
    }
};

class Car{
private:
    string model;
public:
    Car():model("generic") {
         cout << "Generic model car created" << endl;
    }

    Car(string modelName):model(modelName) {
         cout << modelName<< " model car created" << endl;
    }
    
    void setCarModel(const string& modelName)
    {
        cout << "Car model changed from  " << model << " to " << modelName << endl;
        model = modelName;
    }
    ~Car()
    {
        cout << "Destroying Car of model:" << model << "!" << endl;
    }
};

int main() {
    
    SmartPtr<Car> hPtr(new Car("Honda")); 
    hPtr->setCarModel("Godzilla");
    SmartPtr<Car> nPtr(new Car("Ferrari"));
    hPtr = nPtr;
    return 0;
}