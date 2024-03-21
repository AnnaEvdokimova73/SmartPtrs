#include <iostream>
#include <ostream>

template<class T>
class SmartPtr {
public:
    SmartPtr(T* ptr) {
        _ptr = ptr;
        // ptr = nullptr;
    }
    SmartPtr(const SmartPtr& otherPtr) = delete;
    SmartPtr& operator=(const SmartPtr& otherPtr) = delete;

    T* release()
    {
        this->_ptr = nullptr;
        return this->_ptr;
    }

    T* operator->() const
    {
        return this->_ptr;
    }

    T& operator*() const
    {
        return *_ptr;
    }

    ~SmartPtr() {
        delete this->_ptr;
    }

    template<class T>
    friend std::ostream& operator<<(std::ostream& left, const SmartPtr<T>& right);

    T* getPtr() const
    {
        return this->_ptr;
    }

private:
    T* _ptr;
};

template<class T>
std::ostream& operator<<(std::ostream& left, const SmartPtr<T>& right)
{
    left << right.getPtr();
    return left;
}


int main()
{
    setlocale(LC_ALL, "Russian");
    int* arr = new int(3);
    for (int i = 0; i < 3; ++i)
        arr[i] = i + 5;
        
    SmartPtr<int> smrtPtr(arr);
    std::cout << smrtPtr << std::endl;
    std::cout << *smrtPtr << std::endl;
    auto emptyPtr = smrtPtr.release();
    std::cout << smrtPtr << std::endl;
    //std::cout << *smrtPtr << std::endl; // нельзя читать по адресу nullptr

    // std::cout << "Изначальное значение указателя (адрес): " << smrtPtr << std::endl;
    // std::cout << "Разыменованное значение: " << *smrtPtr << std::endl;
    // auto emptyPtr = smrtPtr.release();
    // std::cout << "Значение указателя (адрес) после вызова release(): " << smrtPtr << std::endl;

    delete emptyPtr;
}
