#include <array>
#include <iostream>


template <int N>
constexpr int det(const std::array<std::array<int, N>, N>& a) {
    if constexpr (N == 1) {
        return a[0][0];
    } else if constexpr (N == 0) {
        return 0;
    } else {
        std::array<std::array<int, N - 1>, N - 1> b{};
        int ans = 0, sign = 1;
        for (int i = 0; i < N; ++i) {
            for (int j = 1; j < N; ++j) {
                for (int k = 0; k < N; ++k) {
                    if (k == i) {
                        continue;
                    }
                    b[j - 1][k - (k > i)] = a[j][k];
                }
            }
            ans += sign * a[0][i] * det<N - 1>(b);
            sign = -sign;
        }
        return ans;
    }
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
