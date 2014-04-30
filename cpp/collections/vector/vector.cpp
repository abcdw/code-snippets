#include <iostream>
#include <memory>

using std::cerr;
using std::endl;
using std::allocator;

template < class T, class Alloc = allocator<T> >
class TVector
{
public:
    typedef T value_type;
    typedef allocator<T> allocator_type;
    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;

    class iterator : public std::iterator<std::random_access_iterator_tag, T>
    {
        T* p;
    public:
        iterator() {}
        iterator(T* elem) : p(elem) {}
        iterator(const iterator& it) : p(it.p) {}

        bool operator==(const iterator& rhs) const { return p == rhs.p; }
        bool operator!=(const iterator& rhs) const { return p != rhs.p; }
        bool operator<(const iterator& rhs) const { return p < rhs.p; }
        bool operator>(const iterator& rhs) const { return p > rhs.p; }
        bool operator<=(const iterator& rhs) const { return !operator>(rhs); }
        bool operator>=(const iterator& rhs) const { return !operator<(rhs); }

        iterator& operator++() { ++p; return *this; }
        iterator& operator--() { --p; return *this; }
        iterator operator++(int) { iterator t(*this); operator++(); return t; }
        iterator operator--(int) { iterator t(*this); operator--(); return t; }
        int operator-(const iterator& rhs) const { return p - rhs.p; }
        iterator& operator-=(size_t n) { p -= n; return *this; }
        iterator& operator+=(size_t n) { p += n; return *this; }
        iterator operator-(size_t n) { return iterator(*this) -= n; }
        iterator operator+(size_t n) { return iterator(*this) += n; }
        friend iterator operator+(size_t n, const iterator& rhs) {
            return n + rhs.p;
        }

        T& operator[](size_t index) { return *(*this + index); }
        T& operator*() { return *p; }

        virtual ~iterator() {}
    };

    TVector()
    {}

    TVector(size_t, T = T())
    {}

    TVector(iterator, iterator)
    {}

    TVector(const TVector&)
    {}

    TVector(TVector &&)
    {}

    TVector(std::initializer_list<T>)
    {}

    virtual ~TVector();

private:
    T* data;
    size_t vectorSize, elementCount;
};


int main()
{
    //TVector<int> vec;
    TVector<int>::value_type t[3];
    t[0] = 5;
    t[1] = 3;
    TVector<int>::iterator it;
    it = &t[1];
    auto it2 = it - 1;
    std::swap(it, it2);
    cerr << it[1];

    return 0;
}
