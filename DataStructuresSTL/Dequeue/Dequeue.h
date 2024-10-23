//
//  Dequeue.h
//  DataStructuresSTL
//
//  Created by Sahil Waghmode on 03/02/24.
//

#ifndef Dequeue_h
#define Dequeue_h
#include <iostream>
#include <deque>

#define LOG(msg, flag)  if (flag) std::cout << msg << std::endl;

using namespace std;
class testD
{
public:
    testD() { LOG("Constructor", false)}
    
    testD(int i) :i(i) { LOG("Constructor" , false)}
    
    testD(const testD& rhs)
    {
        this->i = rhs.i;
        LOG("Copy Constructor", false);
    }
    
    testD(const testD&& rhs)
    {
        this->i = rhs.i;
        LOG("Move Constructor", false);
    }
    
    testD& operator=(const testD& rhs)
    {
        this->i = rhs.i;
        LOG("Copy Assignment operator", false);
        return *this;
    }
    
    testD& operator=(const testD&& rhs)
    {
        this->i = rhs.i;
        LOG("Move Assignment operator", false);
        return *this;
    }
    
    friend ostream & operator << (ostream &out, const testD &c);
private:
    int i = 0;
};

template<class Tp>
struct NAlloc
{
    typedef Tp value_type;
 
    NAlloc() = default;
 
    template<class T> NAlloc(const NAlloc<T>&) {}
 
    Tp* allocate(std::size_t n)
    {
        std::cout << "allocating " << n << " elements\n";
        n *= sizeof(Tp);
        std::cout << "allocating " << n << " bytes\n";
        return static_cast<Tp*>(::operator new(n));
    }
 
    void deallocate(Tp* p, std::size_t n)
    {
        std::cout << "deallocating " << n*sizeof*p << " bytes\n";
        ::operator delete(p);
    }
};

namespace Dequeue
{
    void Run();
}
#endif /* Dequeue_h */
