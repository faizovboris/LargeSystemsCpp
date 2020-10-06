#include <cassert>
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <set>
#include <sstream>

struct Printer {
    std::string str() const {
        return my_stream.str();
    }

    template<typename T>
    Printer& format(const std::set<T>& elem) {
        my_stream << "{";
        print_iterable<T>(elem);
        my_stream << " }";
        return *this;
    }

    template<typename T>
    Printer& format(const std::vector<T>& elem) {
        my_stream << "[";
        print_iterable<T>(elem);
        my_stream << " ]";
        return *this;
    }

    template<typename T, typename U>
    Printer& format(const std::pair<T, U>& elem) {
        my_stream << "(";
        format(elem.first);
        my_stream << ", ";
        format(elem.second);
        my_stream << ")";
        return *this;
    }

    template<typename... Tp>
    Printer& format(const std::tuple<Tp...>& t) {
        my_stream << "( ";
        print_tuple(t);
        my_stream << " )";
        return *this;
    }

    template<typename T>
    Printer& format(const T& elem) {
        my_stream << elem;
        return *this;
    }

private:
    template<typename U, typename T>
    void print_iterable(const T& elem) {
        bool is_first = true;
        std::for_each(elem.begin(), elem.end(), [this, &is_first](const U& value) {
            if (!is_first) {
                format(",");
            }
            is_first = false;
            format(" ");
            format(value);
        });
    }

    template<size_t Position = 0, typename... T>
    void print_tuple(const std::tuple<T...>& t) {
        if constexpr(Position != 0) {
            format(", ");
        }
        format(std::get<Position>(t));
        if constexpr(Position + 1 != sizeof...(T)) {
            print_tuple<Position + 1>(t);
        }
    }
    std::stringstream my_stream{};
};

template<typename T>
std::string format(const T& t) {
    return Printer().format(t).str();
}

int main() {
    std::tuple<std::string, int, int> t = {"xyz", 1, 2};
    std::vector<std::pair<int, int> > v = {{1, 4}, {5, 6}};
    std::string s1 = Printer().format(" vector: ").format(v).str();
// " vector: [ (1, 4), (5, 6) ]"
    std::string s2 = Printer().format(t).format(" ! ").format(0).str();
// "( xyz, 1, 2 ) ! 0"
    assert(s1 == " vector: [ (1, 4), (5, 6) ]");
    assert(s2 == "( xyz, 1, 2 ) ! 0");
    std::cout << s1 << "\n";
    std::cout << s2 << "\n";

    std::set<std::pair<int, int> > s = {{1, 4}, {5, 6}};
    std::cout << format(s) << "\n";
    std::vector<std::pair<std::set<int>, std::vector<int>> > sv = {{{6, 7, 11}, {6, 17, 14}}, {{5, 9, 13}, {16, 27, 11}}};
    std::cout << format(sv) << "\n";
}
