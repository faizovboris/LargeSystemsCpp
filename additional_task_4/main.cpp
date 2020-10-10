#include <iostream>
#include <memory>

class A {
public:
// ...
    static void * operator new(size_t size) {
        std::cout << "operator new!" << std::endl;
        return ::operator new(size);
    }
    static void operator delete(void *p, size_t size) {
        std::cout << "operator delete!" << std::endl;
        return ::operator delete(p);
    }
};

template <typename Type, typename Ops>
class MyAllocator {
public:
    using value_type = Type;

    MyAllocator() = default;

    template <typename TypeOther, typename OpsOther>
    constexpr MyAllocator (const MyAllocator<TypeOther, OpsOther>&) noexcept {}

    Type* allocate (std::size_t n) {
        return static_cast<Type*> (Ops::operator new(n * sizeof(Type)));
    }
    void deallocate (Type* p, std::size_t n) {
        Ops::operator delete(p, n * sizeof(Type));
    }
};

int main() {
    //auto sp = std::make_shared<A>();
    auto sp = std::allocate_shared<A>(MyAllocator<A, A>());
}
