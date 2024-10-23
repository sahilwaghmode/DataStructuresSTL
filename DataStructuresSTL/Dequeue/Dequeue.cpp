//
//  Dequeue.cpp
//  DataStructuresSTL
//
//  Created by Sahil Waghmode on 03/02/24.
//
#include "Dequeue.h"
#include <deque>

ostream & operator << (ostream &out, const testD &c)
{
    out << c.i;
    return out;
}

namespace Dequeue {
using namespace std;
    std::deque<testD , NAlloc<testD>> dq ;/*= {testD(7), testD(5), testD(16), testD(8), testD(11), testD(17), testD(19)}*/;
    void PrintContainer(bool shouldPrintAddress = true)
    {
        for(const auto & i : dq)
            cout << i << "\t";
        cout << endl;
        
        if(!shouldPrintAddress) return;
        
        /*for(int i = 0; i < 7 ; i++)
        {
            cout << &d[i] << "\t";
        }
        cout << endl;*/
    }
    void push_back()
    {
        for (int i = 0; i < 1024; ++i)
        {
            dq.emplace_back(testD(i));
        }
    }

    void PushBackTest(int times = 1)
    {
        for(int i = 0 ; i < times ; ++i)
        {
            LOG("size = " << dq.size(), true);
            LOG("---> " << i+1 << "  Adding 1024 elements", true);
            push_back();
            LOG("size = " << dq.size(), true);
            LOG("-------------- " << __func__ << " -------------------", true);
        }
    }

    void pop_back()
    {
        for (int i = 0; i < 1024; ++i)
        {
            dq.pop_back();
        }
    }

    void PopBackTest(int times = 1)
    {
        for(int i = 0 ; i < times ; ++i)
        {
            LOG("size = " << dq.size(), true);
            LOG("---> " << i+1 << "  Popping 1024 elements", true);
            pop_back();
            LOG("size = " << dq.size(), true);
            LOG("-------------- " << __func__ << " -------------------", true);
        }
    }

    void push_front()
    {
        for (int i = 0; i < 1024; ++i)
        {
            dq.emplace_front(testD(i));
        }
    }

    void pop_front()
    {
        for (int i = 0; i < 1024; ++i)
        {
            dq.pop_front();
        }
    }

    void PushFrontTest(int times = 1)
    {
        for(int i = 0 ; i < times ; ++i)
        {
            LOG("size = " << dq.size(), true);
            LOG("---> " << i+1 << " Adding to front 1024 elements", true);
            push_front();
            LOG("size = " << dq.size(), true);
            LOG("-------------- " << __func__ << " -------------------", true);
        }
    }

    void PopFrontTest(int times = 1)
    {
        for(int i = 0 ; i < times ; ++i)
        {
            LOG("size = " << dq.size(), true);
            LOG("---> " << i+1 << "  Popping at front 1024 elements", true);
            pop_front();
            LOG("size = " << dq.size(), true);
            LOG("-------------- " << __func__ << " -------------------", true);
        }
    }

    void erase()
    {
        cout << "Max Size of Dequeue : " << dq.max_size()<< endl;
        PrintContainer();
        auto itr = dq.begin()+2;
        cout << "Before : " << *itr << endl;
        dq.erase(dq.begin()+3, dq.begin()+5);
        for(int i = 0; i < 7 ; i++)
        {
            cout << dq[i] << "\t";
        }
        cout << endl;
        PrintContainer();
        cout << "Max Size of Dequeue : " << dq.max_size()<< endl;
        cout << "after : " << *itr << endl;
    }

    void add_both_side_then_pop_both(int iterations = 1)
    {
        LOG("-------------- " << __func__ << " -------------------", true);
        // push back -> push front -> pop back -> pop front
        PushBackTest(iterations);
        PushFrontTest(iterations);
        PopBackTest(iterations);
        PopFrontTest(iterations);
        LOG("-------------- " << __func__ << " -------------------", true);
    }

    

    void Run()
    {
        add_both_side_then_pop_both(1);
        add_both_side_then_pop_both(2);
    }
}
