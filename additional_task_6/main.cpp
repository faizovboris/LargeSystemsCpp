#include <iostream>
#include <memory>


class Any {
public:
    Any() : valueStorage(nullptr) {}

    template <typename T, typename = std::enable_if_t<!std::is_same<Any, std::decay_t<T>>::value>>
    Any(T&& val) : valueStorage(std::make_unique<Holder<std::decay_t<T>>> (std::forward<T>(val))) { }

    Any(const Any& other) {
        valueStorage = other.valueStorage->copy();
    }

    Any(Any&& other) : valueStorage(std::move(other.valueStorage)) {
        other.valueStorage = nullptr;
    }

    Any& operator=(Any other) {
        std::swap(valueStorage, other.valueStorage);
        return *this;
    }

    template<typename T>
    void emplace(T&& val) {
        valueStorage = std::make_unique<Holder<std::decay_t<T>>> (std::forward<T>(val));
    }

    template <typename T>
    T& get() {
        auto holdered_value = dynamic_cast<Holder<std::decay_t<T>>*>(valueStorage.get());
        if (!holdered_value) {
            throw std::bad_cast();
        }
        return holdered_value->value;
    }

    void reset() {
        valueStorage = nullptr;
    }

    bool has_value() const {
        return valueStorage != nullptr;
    }

private:
    class BaseHolderInterface {
    public:
        virtual ~BaseHolderInterface() = default;
        virtual std::unique_ptr<BaseHolderInterface> copy() = 0;
    };

    template <typename T>
    class Holder : public BaseHolderInterface {
    public:
        T value;

        template <typename U>
        Holder(U&& val): value(std::forward<U>(val)) {}

        std::unique_ptr<BaseHolderInterface> copy() override {
            return std::make_unique<Holder<T>>(value);
        }
    };

    std::unique_ptr<BaseHolderInterface> valueStorage = nullptr;
};


int main() {
    Any a(5);
    a.get<int>(); // 5
    Any b = a;
    b.get<int>() = 6;
    Any c;
    c = b;
    c.get<int>() = 7;
    std::cerr << a.get<int>() << " " << b.get<int>() << " " << c.get<int>() << "\n"; // 5 6 7
    c = Any("Hello");
    std::cerr << a.get<int>() << " " << b.get<int>() << " " << c.get<const char *>() << "\n"; // 5 6 Hello
    c.emplace(std::string(c.get<const char *>()));
    std::cerr << a.get<int>() << " " << b.get<int>() << " " << c.get<std::string>() << "\n"; // 5 6 Hello
    try {
        a.get<std::string>();
        std::cout << "FAILED - no exception\n";
    } catch(...) {
        std::cout << "OK - has exception\n";
    }
}
