#include <iostream>
#include <vector>

using namespace std;

class Test {
private:
    int dummy;
public:
    
    Test() {
        cout << "Constructor . . . "<<endl;
    }
    Test (Test const& test) {
        cout << "Copy Constructor . . ."<<endl;
        dummy = test.dummy;
    }
    Test (Test const&& test) {
        cout << "Move Constructor . . ."<<endl;
        dummy = test.dummy;
    }

    ~Test() {
        cout <<"Destructor . . ."<<endl;
    }
};
int main() {
    vector<Test> vec;
    vec.emplace_back(Test()); 
    return 0;

}