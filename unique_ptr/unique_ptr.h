#include <iostream>

// Currently only supports pointer to non-array objects.
template <typename T>
class MyUniquePointer
{
public:
    MyUniquePointer() {}
    MyUniquePointer(T *ptr) : ptr_{ptr} {}
    MyUniquePointer(MyUniquePointer &other) = delete;
    MyUniquePointer &operator=(MyUniquePointer &other) = delete;

    MyUniquePointer(MyUniquePointer &&other)
        : ptr_(std::exchange(other.ptr_, nullptr))
    {
        std::cout << "move ctor\n";
    }

    ~MyUniquePointer()
    {
        if (ptr_)
            delete ptr_;
    }

    T *release()
    {
        T *temp = ptr_;
        ptr_ = nullptr;
        return temp;
    }

    // Only for testing purposes.
    T *const getPtr()
    {
        return ptr_;
    }

    // Todo: when array template is done.
    // template <typename U>
    // struct Deleter
    // {
    //     void operator()(U *ptr)
    //     {
    //         delete ptr;
    //     }
    // };

    // template <typename U>
    // struct Deleter<U[]>
    // {
    //     void operator()(U *ptr)
    //     {
    //         delete[] ptr;
    //     }
    // };

private:
    T *ptr_ = nullptr;
};

// Note: Cannot just specialize the destructor.
// template<typename T>
// MyUniquePointer<T[]>::~MyUniquePointer() {

// }

// template <typename T>
// class MyUniquePointer<T[]>
// {
//     MyUniquePointer(T arr) : arr_(arr) {}
//     ~MyUniquePointer()
//     {
//         std::cout << "array T destructor\n";
//     }

// private:
//     T arr_;
// };

class MyUniquePointerIntArray
{
public:
    // Constructs and takes ownership of a c-style int array.
    MyUniquePointerIntArray(int *arr) : arr_{arr}
    {
    }

private:
    int *arr_;
};