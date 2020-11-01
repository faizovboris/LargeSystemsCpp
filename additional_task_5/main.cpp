#include <iostream>
#include <cassert>
#include "intrusive_ptr.h"

class TDoc: public TRefCounter<TDoc> {
// ...
};

int main() {
    TIntrusivePtr<TDoc> ptr = nullptr;
    ptr = MakeIntrusive<TDoc>();
    assert(ptr.RefCount() == 1);

    TIntrusivePtr<TDoc> ptr2 = ptr;
    assert((ptr.RefCount() == 2) && (ptr.Get() == ptr2.Get()));

    TIntrusivePtr<TDoc> ptr3 = MakeIntrusive<TDoc>();
    ptr3.Reset(ptr2);
    assert((ptr.RefCount() == 3) && (ptr2.RefCount() == 3) && (ptr3.RefCount() == 3) && 
           (ptr.Get() == ptr2.Get()) && (ptr.Get() == ptr3.Get()));

    ptr3.Reset();
    assert((ptr.RefCount() == 2) && (ptr2.RefCount() == 2) && (ptr3.RefCount() == 0) && 
           (ptr.Get() == ptr2.Get()) && (ptr3.Get() == nullptr));

    ptr3.Reset(std::move(ptr2));
    assert((ptr.RefCount() == 2) && (ptr2.RefCount() == 0) && (ptr3.RefCount() == 2) && 
           (ptr.Get() == ptr3.Get()) && (ptr2.Get() == nullptr));

    TDoc* raw_ptr = ptr.Release();
    assert((ptr.RefCount() == 0) && (ptr2.RefCount() == 0) && (ptr3.RefCount() == 1) && 
           (ptr.Get() == nullptr) && (ptr2.Get() == nullptr));
    assert(raw_ptr == ptr3.Get());

    static_assert(sizeof(TDoc*) == sizeof(ptr));
}