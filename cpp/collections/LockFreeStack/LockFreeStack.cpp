#include <iostream>
#include <memory>
#include <atomic>

using std::shared_ptr;
template <typename T>
class LockFreeStack
{
private:
    struct TNode
    {
        T data;
        TNode* next;
        TNode(const T& data)
            : data(data)
        {}
    };
    std::atomic< shared_ptr<TNode> > head;

public:
    LockFreeStack() {}

    void push(const T& data) {
        shared_ptr<TNode> t = new TNode(data);
        t->next = head.load();
        while (!head.compare_exchange_weak(t->next, t)) ;
    }

    bool pop(T& data) {
        shared_ptr<TNode> t = head.load();
        while(t && !head.compare_exchange_weak(t, t->next)) ;
        if (t) {
            data = t->data;
            return true;
        } else {
            return false;
        }
    }

};

int main()
{

    return 0;
}
