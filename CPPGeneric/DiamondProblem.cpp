#include <iostream>
using namespace std;

class A                     { 
public: 
    /*A(){
        cout << "A is called!\n";
    }*/
    A(int i) {
        cout << "Parametrized A is called!\n";
    }
    virtual ~A(){ } 
    virtual void eat(){ 
        std::cout<<"EAT=>A";
    }    
}; 
class B: virtual public A   { 
public:
   /* B(){
        cout << "B is called!\n";
    }*/
    B(int i):A(i) {
        cout << "Parametrized B is called!\n";
    }
    virtual ~B(){ }
    virtual void eat(){ 
        std::cout<<"EAT=>B";
    } 
}; 
class C: virtual public A {
public:
    /*C(){
        cout << "C is called!\n";
    }*/
    C(int i): A(i) {
        cout << "Parametrized C is called!\n";
    }
    virtual ~C(){ }
    virtual void eat(){ 
        std::cout<<"EAT=>C";
    }
}; 
class D: public B,C { 
    int i;
public: 
    D(int i):C(i), B(i), A(i){
       cout << "D is called!\n"; 
    }
    virtual ~D(){ } 
    virtual void eat(){ 
        std::cout<<"EAT=>D";
    }    
}; 

int main(int argc, char ** argv){
    A *a = new D(4); 
    a->eat(); 
    cout << endl;
    delete a;
}