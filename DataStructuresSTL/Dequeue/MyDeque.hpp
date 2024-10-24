//
//  MyDeque.hpp
//  DataStructuresSTL
//
//  Created by Sahil Waghmode on 20/10/24.
//

#ifndef MyDeque_hpp
#define MyDeque_hpp

#include <stdio.h>

#include <memory>
#include <iterator>
#include <vector>

template <typename T, typename Allocator = std::allocator<T>>
class MyDeque
{
public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
//    using pointer = typename std::allocator_traits<Allocator>::pointer;
//    using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
    using pointer = std::vector<value_type, Allocator>::iterator;
    using const_pointer = std::vector<value_type, Allocator>::const_pointer;
    using record_pointer =  std::vector<std::vector<value_type, Allocator>>::iterator;

    class iterator
    {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator(pointer ptr = nullptr) : m_ptr(ptr) {}

        reference operator*() { return *m_ptr; }
        const_reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }
        const_pointer operator->() const { return m_ptr; }

        iterator& operator++()
        {
            ++m_ptr;
            return *this;
        }

        iterator operator++(int)
        {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        iterator& operator--()
        {
            --m_ptr;
            return *this;
        }

        iterator operator--(int)
        {
            iterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const iterator& other) const { return m_ptr == other.m_ptr; }
        bool operator!=(const iterator& other) const { return m_ptr != other.m_ptr; }

    private:
        pointer m_ptr;
    };

    // Add constructor, destructor, and other member functions here
    MyDeque():_size(0)
    {
    }
    
    explicit MyDeque( size_type count ): _allocator(Allocator())
    {
        allocate_block(_size);
    }
    
    template< class InputIt >
    MyDeque( InputIt first, InputIt last)
    {
        auto num_elements_to_allocate = std::distance(first, last);
        allocate_block(num_elements_to_allocate);
        
        auto num_records_to_allocate = num_elements_to_allocate/_elements_per_book;

        for(auto i = 0; i < num_records_to_allocate; ++i)
        {
            auto record = _book_records[i];
            auto allocated_elements = num_elements_to_allocate > _elements_per_book ? _elements_per_book : num_elements_to_allocate;
            std::copy(first, first + allocated_elements, record.begin());
            first += _elements_per_book;
            num_elements_to_allocate -= allocated_elements;
        }
        
    }
    MyDeque( const MyDeque& other )
    {
        allocate_block(other._size);
        for(auto i = 0; i < _book_records.size(); ++i)
        {
            std::copy(other._book_records[i].begin(), other._book_records[i].end(), _book_records[i].begin());
        }
    }
    MyDeque( MyDeque&& other )
    {
        _begin_ind = other._begin_ind;
        _end_ind = other._end_ind;
        _size = other._size;
        _book_records = std::move(other._book_records);
    }
    MyDeque( std::initializer_list<T> init ) : MyDeque(init.begin(), init.end()) {}

    iterator begin() { return iterator(_book_records.front()); }
    iterator end() { return iterator(_book_records.back() + _size); }
    
    //Modifires
    void push_back( const T& value )
    {
        auto end_record = _end_record->back();
        auto elements = std::distance(_end_ind, end_record.end());
        if(elements > 0)
        {
            ++_end_ind;
            *_end_ind = value;
        }
        else
        {
            allocate_block(_elements_per_book);
            _end_record = &_book_records.back();
            _end_ind = _end_record->begin();
            *_end_ind = value;
        }
    }
    
    void pop_back()
    {
        auto elements = std::distance(_end_ind, _end_record->end())+1;
        if(elements  <= _elements_per_book)
        {
            //*_end_ind = T();
            if(_book_records.size() > 1)
            {
                _end_record--;
                _end_ind = _end_record->back();
            }
            else //meaning record will be empty
            {
                _end_ind = _end_record->begin();
                _begin_ind = _end_record->begin();
                _begin_record = _end_record;
            }
        }
        else
        {
            //*_end_ind = T();
            --_end_ind;
        }
    }
    
    void push_front( const T& value)
    {
        auto elements = std::distance(_begin_ind, _begin_record->begin());
        if(elements > 0)
        {
            --_begin_ind;
            *_begin_ind = value;
        }
        else
        {
            allocate_block(_elements_per_book,false);
            _begin_record = &_book_records.front();
            _begin_ind = _begin_record->end() - 1;
            *_begin_ind = value;
        }
    }
    
    void pop_front()
    {
        auto elements = std::distance(_begin_ind, _begin_record->end());
        if(elements > 0)
        {
            ++_begin_ind;
        }
        else
        {
            if(_book_records.size() > 1) // hop to next record
            {
                _begin_record++;
                _begin_ind = _begin_record->begin();
            }
            else//meaning record will be empty
            {
                _begin_ind = _begin_record->begin();
                _end_record =  _begin_record;
                _end_ind = _end_record->end();
            }
        }
        
    }
    
    reference operator[]( size_type pos )
    {
        auto dist_in_first_block = std::distance(_begin_ind, _begin_record->end());
        if(pos < dist_in_first_block)
        {
            return *(_begin_ind + pos);
        }
        else
        {
            auto dist_in_other_block = pos - dist_in_first_block;
            auto block_num = dist_in_other_block / _elements_per_book;
            auto index = dist_in_other_block % _elements_per_book;
            return _begin_record+block_num[index];
        }
    }
    
    void shrink_to_fit()
    {
        auto num_records = std::distance(_begin_record, _end_record);
        if(num_records == _book_records.capacity()) return;
        
        auto dist_from_begin = std::distance(_book_records.begin(), _begin_record);
        auto dist_from_end = std::distance(_end_record, _book_records->end());
        if(dist_from_begin > 0)// we have a gap
        {
            auto book_record_itr = _book_records.begin();
            for(auto itr = _begin_record; itr != _end_record; itr++ , book_record_itr++)
            {
                *book_record_itr = std::move(*itr);
            }
        }
        //i have moved the vectors here , will this invalidate thebegin and end indx
        _book_records.resize(num_records);
        _begin_record = _book_records.begin();
        _end_record = _begin_record + num_records - 1;
        
    }

private:
    allocator_type _allocator;
    pointer _begin_ind;
    pointer _end_ind;
    std::vector<value_type, Allocator>* _end_record;
    record_pointer _begin_record;
    size_type _size;
    std::vector<std::vector<value_type,Allocator>> _book_records;
    int _elements_per_book = 4096/sizeof(value_type);
    
    void allocate_block(size_type n, bool atEnd = true)
    {
        auto record_size =_book_records.size();
        unsigned int to_allocate = (n / _elements_per_book) + 1;
        if(atEnd)
        {
            if(to_allocate > record_size)
            {
                _book_records.resize(to_allocate);
            }
        }
        else
        {
            _book_records.insert(_book_records.begin()).resize(_elements_per_book);
            //all the reference has invalidated now // refresh them
        }
        _size = _elements_per_book * _book_records.size();
        
        
        for(auto i = record_size; i < to_allocate; ++i)
        {
            _book_records[i].resize(_elements_per_book);
        }
        
        
    }

    // Add helper functions here
};



#endif /* MyDeque_hpp */
