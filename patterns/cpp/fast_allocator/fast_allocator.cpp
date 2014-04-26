#include <iostream>

using std::cout;
using std::endl;

template <class T>
class fast_allocator {
    // Interface class
public:
    fast_allocator() {}
    virtual ~fast_allocator() {}

private:
};

template <> 
class fast_allocator<void> {
public:
    typedef void* pointer;
    typedef const void* const_pointer;
    typedef void value_type;
    template <class U> struct rebind { typedef fast_allocator<U> other; };
};


template<size_t node_size>
class FastAllocator {
public:
    FastAllocator() 
        : buffers(new TBuffer),
          freeNodes(nullptr)
    {
        addBuffer(buffers);
    }

    virtual ~FastAllocator() {}

private:
    static const size_t NODE_NUMBER = 10;

    struct TNode {
        void* buffer;
        TNode* next;
        TNode()
            : buffer(new char[node_size]),
              next(nullptr)
        {}
    };

    struct TBuffer {
        TNode nodes[NODE_NUMBER];
        TBuffer* next;
    };

    TBuffer* buffers;
    TNode* freeNodes;

    void addBuffer(TBuffer* buffer) {
        buffer->next = buffers, buffers = buffer;

        for (TNode node : buffer->nodes)
            push(&node);
    }

    void pop() {

    }

    void push(TNode* freeNode) {
        freeNode->next = freeNodes;
        freeNodes = freeNode;
    }

    bool empty() {
        return freeNodes == nullptr;
    }
};

int main()
{
    fast_allocator<int> fa;
    FastAllocator<8> FA;

    return 0;
}
