#include <array>
#include <iostream>
#include <vector>

constexpr bool Check_value(int value) {
    return false;
}

template <class... Args>
constexpr bool Check_value(int value, int first, Args... args) {
    return (value == first ? true : Check_value(value, args...));
}

constexpr int Get_Elem_Reverses(int elem) {
    return 0;
}

template <class... Args>
constexpr int Get_Elem_Reverses(int elem, int first, Args... current_permutations) {
    return Get_Elem_Reverses(elem, current_permutations...) + (elem > first);
}


template <int Row, int N, class... Args, typename std::enable_if<Row == -1, void>::type* = nullptr>
constexpr int Get_Permutations(const std::array<std::array<int, N>, N>& a, int reverses, int mult, Args... current_permutations) {
    int sign = ((reverses & 1) == 0 ? 1 : -1);
    return sign * mult;
}


template <int Row, int N, class... Args, typename std::enable_if<Row != -1, void>::type* = nullptr>
constexpr int Get_Permutations(const std::array<std::array<int, N>, N>& a, int reverses, int mult, Args... current_permutations) {
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        if (!Check_value(i, current_permutations...)) {
            ans += Get_Permutations<Row - 1, N>(a, reverses + Get_Elem_Reverses(i, current_permutations...), mult * a[Row][i], i, current_permutations...);
        }
    }
    return ans;
}


template <int N>
constexpr int det(const std::array<std::array<int, N>, N>& a) {
    return (N == 0 ? 0 : Get_Permutations<N - 1, N>(a, 0, 1));
}


int main() {
    constexpr std::array<std::array<int, 3>, 3> A = {{
                                                   {0, 1, 2}
                                                   ,{1, 2, 3}
                                                   ,{2, 3, 7}
                                           }};
    constexpr int res = det<3>(A);
    std::cout << res << std::endl;
}