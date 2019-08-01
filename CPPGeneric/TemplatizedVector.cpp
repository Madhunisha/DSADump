#include <iostream>

using namespace std;
template <typename T>
class Vector{
public:
    explicit Vector() {
        arr = new T[reserve_sz];
    };

    Vector(const int sz) {
        reserve_sz = 2 * sz;
        msize = sz;
        arr = new T[msize]; 
    }

    Vector (const Vector<T>& rhs) 
    : msize(rhs.size)
    , arr(new T[msize])
    , reserve_sz(rhs.reserve_sz)
    {
        std::copy(rhs.arr, rhs.arr + rhs.msize, arr);
    }

    Vector<T>& operator=(const Vector<T>& other) {
        if (this != &other)
        {
            delete[] arr;
            msize = other.size;
            reserve_sz = other.reserve_sz;
            arr = new T[msize];
            std::copy(other.arr, other.arr + other.msize, arr);
        }
      return *this;
    }

    Vector(Vector<T>&& other)  noexcept    
    : msize(0),
     arr(nullptr)
    {
        arr = other.arr;
        msize = other.msize;
        reserve_sz = other.reserve_sz;
        other.arr = nullptr;
        other.size = 0;
        other.reserve_sz = 4;
    }

    Vector<T>& operator=(const Vector<T>&& other) {
        if (this != &other)
        {
            delete[] arr;
            msize = other.size;
            reserve_sz = other.reserve_sz;
            arr = other.arr;
            other.arr = nullptr;
            other.size = 0;
            other.reserve_sz = 4;
        }
      return *this;
    }
    void push_back(T const&& val) {
        if(msize == reserve_sz) {
            reserve_sz *=2; 
            reallocate();
        }
        arr[msize++] = move(val);
    }
    void pop_back() {
        --msize;
        arr[msize].~T();
    }
    bool empty() {
        return msize == 0;
    }
    int size() {
        return msize;
    }
    T operator[](int idx) {
        if(idx < msize)
            return arr[idx];
        else
        {
            throw std::out_of_range ("Cannot Access.");
        }
        
    }
private:
    void reallocate() {
        T *tarr = new T[reserve_sz];
		memcpy(tarr, arr, msize * sizeof(T));
		delete [] arr;
		arr = tarr;
    }
    int reserve_sz = 4;
    int msize = 0;
    T* arr;
    
};

int main() {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    cout << v[1] <<endl;

    return 0;
}