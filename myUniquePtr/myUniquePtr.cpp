#include <iostream>
#include <ostream>

template<class T>
class SmartPtr {
public:
    SmartPtr(T ptr) {
        _ptr = ptr;
        ptr = nullptr;
        // delete ptr;
    }
    SmartPtr(const SmartPtr& otherPtr) = delete;
    SmartPtr& operator=(const SmartPtr& otherPtr) = delete;

    SmartPtr& release()
    {
        this->_ptr = nullptr;
        return *this;
    }

    T* operator->() const
    {
        return this->_ptr;
    }

    T& operator*() const
    {
        return *_ptr;
    }

    /*SmartPtr* operator->() const
    {
        return this;
    }

    /*SmartPtr& operator*() const
    {
        return *this;
    }*/

    ~SmartPtr() {
        delete _ptr;
    }

    template<class T>
    friend std::ostream& operator<<(std::ostream& left, const SmartPtr<T>& right);

    template<class T>
    friend std::ostream& operator<<(std::ostream& left, const SmartPtr<T>* right);

    T getPtr() const
    {
        return _ptr;
    }

private:
    T _ptr;
};

template<class T>
std::ostream& operator<<(std::ostream& left, const SmartPtr<T>& right)
{
    left << right.getPtr();
    return left;
}

template<class T>
std::ostream& operator<<(std::ostream& left, const SmartPtr<T>* right)
{
    left << *right;
    return left;
}

int main()
{
    int arr[3]{ 1, 2, 3 };
    SmartPtr<int*> smrtPtr(arr);
    std::cout << smrtPtr << std::endl;
    //std::cout << *smrtPtr << std::endl;
    smrtPtr.release();
    std::cout << smrtPtr << std::endl;
    //std::cout << *smrtPtr << std::endl;
}
