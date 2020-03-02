#pragma once
#include <cstdlib>
#include <algorithm>
#include <utility>
#include <stdexcept>
#include <limits>
#include <iterator>

#include <iostream>

template <class T>
class Vector {
    public:
        
        class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
            public:
                Iterator(T* init_ptr = nullptr);

                Iterator(const Iterator& copy_iter);
                Iterator& operator=(const Iterator& copy_iter);

                Iterator(Iterator&& move_iter);
                Iterator& operator=(Iterator&& move_iter);

                inline T& operator*() const;
                inline T& operator[](ssize_t index) const;
                inline T* operator->() const;

                inline Iterator& operator++();
                inline Iterator operator++(int);

                inline Iterator& operator--();
                inline Iterator operator--(int);

                inline Iterator& operator+=(ssize_t diff);
                inline Iterator& operator-=(ssize_t diff);

                inline Iterator operator+(ssize_t shift) const;
                inline Iterator operator-(ssize_t shift) const;

                inline friend Iterator operator+(ssize_t shift, const Iterator& iter);
                inline friend Iterator operator-(ssize_t shift, const Iterator& iter);

                inline ssize_t operator-(const Iterator& iter) const;

                inline bool operator<(const Iterator& iter) const;
                inline bool operator<=(const Iterator& iter) const;
                inline bool operator>(const Iterator& iter) const;
                inline bool operator>=(const Iterator& iter) const;
                inline bool operator==(const Iterator& iter) const;
                inline bool operator!=(const Iterator& iter) const;

            private:
                T* ptr;
        };

        typedef std::reverse_iterator<Iterator> ReverseIterator;
        
        Vector();
        explicit Vector(size_t elem_count);
        Vector(size_t elem_count, const T& copy_obj);

        Vector(const Vector& copy_obj);
        Vector& operator=(const Vector& copy_obj);

        Vector(Vector&& move_obj);
        Vector& operator=(Vector&& move_obj);

        ~Vector();

        // Elements' access
        T& front();
        const T& front() const;
        T& back();
        const T& back() const;

        T& operator[](size_t elem_index);
        const T& operator[](size_t elem_index) const;

        T& at(size_t elem_index);
        const T& at(size_t elem_index) const;

        // Data operations
        void push_back(const T& obj);
        void push_back(T&& obj);
        void pop_back();
        
        template <class ... Args>
        void emplace_back(Args&& ... args);

        // Auxiliary methods
        size_t size() ;
        size_t capacity() ;
        bool empty() ;
        size_t max_size() ;

        void clear() ;
        void reserve(size_t next_capacity);
        void resize(size_t next_size);
        void resize(size_t next_size, const T& obj);
        void shrink_to_fit();

        void assign(size_t count, const T& obj);
        void assign(Iterator first_it, Iterator last_it);

        void erase(Iterator target_it, size_t positive_shift = 1);
        void erase(Iterator first_it, Iterator last_it);

        void insert(Iterator target_it, const T& copy_obj);
        void insert(Iterator target_it, T&& move_obj);

        // Iterators' methods
        Iterator begin() ;
        Iterator end() ;

        ReverseIterator rbegin() ;
        ReverseIterator rend() ;
 
    private:
        T* buff_;
        size_t capacity_;
        size_t size_;

        static const size_t _guaranteed_cap_ = 32;

        void destroy_constructed();

        void change_buff_volume(size_t next_capacity);

        void realloc_buff_by_capacity();

        void calloc_by_capacity();

        void copy_from_obj(const Vector& copy_obj);
};


// *** Constructors, destructor, operator='s ***

template <class T>
Vector<T>::Vector() :
    capacity_(_guaranteed_cap_),
    size_(0)
{
    calloc_by_capacity();
}

template <class T>
Vector<T>::Vector(size_t elem_count):
    capacity_(elem_count * 2),
    size_(elem_count)
{
    calloc_by_capacity();
    for (size_t elem_it = 0; elem_it < size_; ++elem_it) {
        new (buff_ + elem_it) T;
    }
}

template <class T>
Vector<T>::Vector(size_t elem_count, const T& copy_obj) :
    capacity_(elem_count * 2),
    size_(elem_count)
{
    calloc_by_capacity();
    for (size_t elem_it = 0; elem_it < size_; ++elem_it) {
        buff_[elem_it] = copy_obj;
    }
}

template <class T>
Vector<T>::Vector(const Vector& copy_obj) :
    capacity_(copy_obj.size_ * 2),
    size_(copy_obj.size_)
{
    calloc_by_capacity();
    copy_from_obj(copy_obj);
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector& copy_obj) {
    destroy_constructed();

    if (capacity_ < copy_obj.size_ * 2) {
        capacity_ = copy_obj.size_ * 2;
        realloc_buff_by_capacity();
    }

    copy_from_obj(copy_obj);
    return *this;
}

template <class T>
Vector<T>::Vector(Vector<T>&& move_obj) :
    capacity_( std::move(move_obj.capacity_) ),
    size_( std::move(move_obj.size_) ),
    buff_( std::move(move_obj.buff_) ) {}

template <class T>
Vector<T>& Vector<T>::operator=(Vector<T>&& move_obj) {
    destroy_constructed();
    free(buff_);

    capacity_ = std::move(move_obj.capacity_);
    size_ = std::move(move_obj.size_);
    buff_ = std::move(move_obj.size_);

    return *this;
}

template <class T>
Vector<T>::~Vector() {
    destroy_constructed();
    free(buff_);
}


// *** Elements access methods ***

template <class T>
T& Vector<T>::front() {
    return buff_[0];
}

template <class T>
const T& Vector<T>::front() const {
    return buff_[0];
}

template <class T>
T& Vector<T>::back() {
    return buff_[size_ - 1];
}

template <class T>
const T& Vector<T>::back() const {
    return buff_[size_ - 1];
}

template <class T>
T& Vector<T>::operator[](size_t elem_index) {
    return buff_[elem_index];
}

template <class T>
const T& Vector<T>::operator[](size_t elem_index) const {
    return buff_[elem_index];
}

template <class T>
T& Vector<T>::at(size_t elem_index) {
    if (elem_index >= size_) {
        throw std::out_of_range("Vector at(): index must be less then size");
    }
    
    return buff_[elem_index];
}

template <class T>
const T& Vector<T>::at(size_t elem_index) const {
    if (elem_index >= size_) {
        throw std::out_of_range("Vector at(): index must be less then size");
    }

    return buff_[elem_index];
}


// ** Public utility methods ***

template <class T>
size_t Vector<T>::size()  {
    return size_;
}

template <class T>
size_t Vector<T>::capacity()  {
    return capacity_;
}

template <class T>
bool Vector<T>::empty()  {
    return size_ == 0;
}

template <class T>
size_t Vector<T>::max_size()  {
    return std::numeric_limits<size_t>::max();
}


// Data operations

template <class T>
void Vector<T>::push_back(const T& obj) {
    if (capacity_ == size_) {
        change_buff_volume(capacity_ * 2);
    }

    buff_[size_++] = obj;
}

template <class T>
void Vector<T>::push_back(T&& obj) {
    if (capacity_ == size_) {
        change_buff_volume(capacity_ * 2);
    }

    buff_[size_++] = std::move(obj);
}

template <class T>
void Vector<T>::pop_back() {
    if (size_ == 0) {
        throw std::out_of_range("Vector: Out of range during pop_back");
    }

    --size_;
}

template <class T>
template <class ... Args>
void Vector<T>::emplace_back(Args&& ... args) {
    if (capacity_ == size_) {
        change_buff_volume(capacity_ * 2);
    }

    new (buff_ + size_) T(std::forward<Args>(args) ...);
    ++size_;
}


// *** Random access iterator ***

template <class T>
Vector<T>::Iterator::Iterator(T* init_ptr) : ptr(init_ptr) {}

template <class T>
Vector<T>::Iterator::Iterator(const Iterator& copy_iter) :
    ptr(copy_iter.ptr) {}

template <class T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator=(const Iterator& copy_iter) {
    ptr = copy_iter.ptr;
    return *this;
}

template <class T>
Vector<T>::Iterator::Iterator(Iterator&& move_iter) :
    ptr(std::move(move_iter.ptr)) {}

template <class T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator=(Iterator&& move_iter) {
    ptr = std::move(move_iter.ptr);
    return *this;
}

template <class T>
T& Vector<T>::Iterator::operator*() const {return *ptr;}

template <class T>
T* Vector<T>::Iterator::operator->() const {return ptr;}

template <class T>
T& Vector<T>::Iterator::operator[](ssize_t index) const {return ptr[index];}

template <class T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator++() {
    ++ptr;
    return *this;
}

template <class T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int) {
    Iterator prev_iter(ptr);
    ++ptr;
    return prev_iter;
}

template <class T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator--() {
    --ptr;
    return *this;
}

template <class T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator--(int) {
    Iterator prev_iter(ptr);
    --ptr;
    return prev_iter;
}

template <class T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator+=(ssize_t diff) {
    ptr += diff;
    return *this;
}

template <class T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator-=(ssize_t diff) {
    ptr -= diff;
    return *this;
}

template <class T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator+(ssize_t shift) const {
    return Iterator(ptr + shift);
}

template <class T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator-(ssize_t shift) const {
    return Iterator(ptr - shift);
}

template <class T>
inline typename Vector<T>::Iterator operator+(ssize_t shift, const typename Vector<T>::Iterator& iter) {
    return Vector<T>::Iterator(shift + iter.ptr);
}

template <class T>
inline typename Vector<T>::Iterator operator-(ssize_t shift, const typename Vector<T>::Iterator& iter) {
    return Vector<T>::Iterator(shift - iter.ptr);
}

template <class T>
ssize_t Vector<T>::Iterator::operator-(const Vector<T>::Iterator& iter) const {
    return ptr - iter.ptr;
}

template <class T>
bool Vector<T>::Iterator::operator<(const Vector<T>::Iterator& iter) const {
    return ptr < iter.ptr;
}

template <class T>
bool Vector<T>::Iterator::operator<=(const Vector<T>::Iterator& iter) const {
    return ptr <= iter.ptr;
}

template <class T>
bool Vector<T>::Iterator::operator>(const Vector<T>::Iterator& iter) const {
    return ptr > iter.ptr;
}

template <class T>
bool Vector<T>::Iterator::operator>=(const Vector<T>::Iterator& iter) const {
    return ptr >= iter.ptr;
}

template <class T>
bool Vector<T>::Iterator::operator==(const Vector<T>::Iterator& iter) const {
    return ptr == iter.ptr;
}

template <class T>
bool Vector<T>::Iterator::operator!=(const Vector<T>::Iterator& iter) const {
    return ptr != iter.ptr;
}


// *** Iterator methods ***

template <class T>
typename Vector<T>::Iterator Vector<T>::begin()  {
    return Iterator(buff_);
}

template <class T>
typename Vector<T>::Iterator Vector<T>::end()  {
    return Iterator(buff_ + size_);
}

template <class T>
typename Vector<T>::ReverseIterator Vector<T>::rbegin()  {
    return ReverseIterator(buff_ + size_);
}

template <class T>
typename Vector<T>::ReverseIterator Vector<T>::rend()  {
    return ReversesIterator(buff_);
}


// *** Private utility methods ***

template <class T>
void Vector<T>::change_buff_volume(size_t next_capacity) {
    if (next_capacity > max_size()) {
        throw std::length_error("Vector increase capacity: new capacity larger then MAX_SIZE");
    }

    T* next_buff = (T*)calloc(next_capacity, sizeof(T));
    
    size_t next_size = std::min(next_capacity, size_);
    for (size_t elem_index = 0; elem_index < next_size; ++elem_index) {
        next_buff[elem_index] = std::move(buff_[elem_index]);
    }

    destroy_constructed();
    capacity_ = next_capacity;
    size_ = next_size;

    free(buff_);
    buff_ = next_buff;
}

template <class T>
void Vector<T>::realloc_buff_by_capacity() {
    free(buff_);
    calloc_by_capacity();
}

template <class T>
void Vector<T>::destroy_constructed() {
    for (size_t elem_index = 0; elem_index < size_; ++elem_index) {
        buff_[elem_index].~T();
    }
    size_ = 0;
}

template <class T>
void Vector<T>::calloc_by_capacity() {
    buff_ = (T*)calloc(capacity_, sizeof(T));
}

template <class T>
void Vector<T>::copy_from_obj(const Vector<T>& copy_obj) {
    for (size_t elem_index = 0; elem_index < copy_obj.size_; ++elem_index) {
        buff_[elem_index] = copy_obj.buff_[elem_index];
    }
}

template <class T>
void Vector<T>::clear() {
    destroy_constructed();
}

template <class T>
void Vector<T>::reserve(size_t next_capacity) {
    if (next_capacity > capacity_) {
        change_buff_volume(next_capacity);
    }
}

template <class T>
void Vector<T>::resize(size_t next_size) {
    reserve(next_size);

    // Create new elements
    for (size_t elem_index = size_ - 1; elem_index < next_size; ++elem_index) {
        new (buff_ + elem_index) T;
    }

    // Destroy garbage elements
    for (size_t elem_index = next_size - 1; elem_index < size_; ++elem_index) {
        buff_[elem_index].~T();
    }

    size_ = next_size;
}

template <class T>
void Vector<T>::resize(size_t next_size, const T& obj) {
    reserve(next_size);

    // Create new elements
    for (size_t elem_index = size_ - 1; elem_index < next_size; ++elem_index) {
        buff_[elem_index] = obj;
    }

    // Destroy garbage elements
    for (size_t elem_index = next_size - 1; elem_index < size_; ++elem_index) {
        buff_[elem_index].~T();
    }

    size_ = next_size;
}

template <class T>
void Vector<T>::shrink_to_fit() {
    change_buff_volume(size_);
}

template <class T>
void Vector<T>::assign(size_t count, const T& obj) {
    if (size_ < count) {
        resize(count);
    }

    for (size_t elem_index = 0; elem_index < count; ++elem_index) {
        buff_[elem_index] = obj;
    }
}

template <class T>
void Vector<T>::assign(Vector<T>::Iterator first_it, Vector<T>::Iterator last_it) {
    for (Iterator it = first_it + 1; it != last_it; ++it) {
        *it = *first_it;
    }
}

template <class T>
void Vector<T>::erase(Vector<T>::Iterator target_it, size_t positive_shift) {
    for (Iterator it = target_it; it + positive_shift != end(); ++it) {
        *it = *(it + positive_shift);
    }

    for (size_t count = 1; count <= positive_shift; ++count) {
        (end() - count)->~T();
    }

    size_ -= positive_shift;
}

template <class T>
void Vector<T>::erase(Vector<T>::Iterator first_it, Vector<T>::Iterator last_it) {
    erase(first_it, last_it - first_it);
}

template <class T>
void Vector<T>::insert(Vector<T>::Iterator target_it, const T& copy_obj) {
    if (capacity_ < size_ + 1) {
        change_buff_volume(capacity_ * 2);
    }

    for (Iterator it = end(); it >= target_it; --it) {
        *it = *(it - 1);
    }

    *target_it = copy_obj;
    ++size_;
}

template <class T>
void Vector<T>::insert(Vector<T>::Iterator target_it, T&& move_obj) {
    if (capacity_ < size_ + 1) {
        change_buff_volume(capacity_ * 2);
    }

    for (Iterator it = end(); it >= target_it; --it) {
        *it = *(it - 1);
    }

    *target_it = std::move(move_obj);
    ++size_;
}