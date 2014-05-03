#include <iostream>
#include <vector>
#include <memory>

using std::cerr;
using std::endl;
using std::allocator;

template < class T, class Alloc = allocator<T> >
class TVector
{
private:
    static const size_t MAX_SIZE = 1073741823;

    template < bool isConst = false >
    class MyIterator : public std::iterator<std::random_access_iterator_tag, T>
    {
    public:
        typedef typename 
            std::conditional<isConst, const T&, T&>::type reference;
        typedef typename
            std::conditional<isConst, const T*, T*>::type pointer;

        MyIterator() {}
        MyIterator(pointer elem) : p(elem) {}
        MyIterator(const MyIterator& it) : p(it.p) {}
        bool operator==(const MyIterator& rhs) const { return p == rhs.p; }
        bool operator!=(const MyIterator& rhs) const { return p != rhs.p; }
        bool operator<(const MyIterator& rhs) const { return p < rhs.p; }
        bool operator>(const MyIterator& rhs) const { return p > rhs.p; }
        bool operator<=(const MyIterator& rhs) const { return !operator>(rhs); }
        bool operator>=(const MyIterator& rhs) const { return !operator<(rhs); }

        MyIterator& operator++() { ++p; return *this; }
        MyIterator& operator--() { --p; return *this; }
        MyIterator operator++(int) { MyIterator t(*this); operator++(); return t; }
        MyIterator operator--(int) { MyIterator t(*this); operator--(); return t; }
        int operator-(const MyIterator& rhs) const { return p - rhs.p; }
        MyIterator& operator-=(size_t n) { p -= n; return *this; }
        MyIterator& operator+=(size_t n) { p += n; return *this; }
        MyIterator operator-(size_t n) const { return MyIterator(*this) -= n; }
        MyIterator operator+(size_t n) const { return MyIterator(*this) += n; }
        friend MyIterator operator+(size_t n, const MyIterator& rhs) {
            return MyIterator(rhs) += n;
        }

        reference operator[](size_t index) { return *(*this + index); }
        reference operator*() { return *p; }

        virtual ~MyIterator() {}

    private:
        pointer p;
    };

    typedef size_t size_type;

    T* data;
    size_type vectorSize, vectorCapacity;

public:
    typedef T value_type;
    typedef allocator<T> allocator_type;
    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef MyIterator<false> iterator;
    typedef MyIterator<true> const_iterator;
    typedef typename
        std::iterator_traits<iterator>::difference_type difference_type;


    TVector()
    {}

    TVector(size_type, T = T())
    {}

    TVector(iterator, iterator)
    {}

    TVector(const TVector&)
    {}

    TVector(TVector &&)
    {}

    TVector(std::initializer_list<T>)
    {}

    size_type size() {
        return vectorSize;
    }

    size_type capacity() {
        return vectorCapacity;
    }

    bool empty() {
        return vectorSize == 0;
    }

    void resize(size_type n);
    virtual ~TVector();
};


int main()
{
    //TVector<int> vec;
    TVector<int>::value_type t[3];
    t[0] = 5;
    t[1] = 3;
    TVector<int>::iterator it;
    it = &t[1];
    //TVector<int>::const_iterator cit = it;
    //std::vector<int>::iterator itt;
    //std::vector<int>::const_iterator cit = itt;

    //std::swap(it, it2);
    it[1] = 7;
    cerr << it[1];

    return 0;
}
