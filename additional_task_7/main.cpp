#include <iostream>
#include <map>
#include <ctime>
#include <iomanip>

constexpr int REPEATS_CNT = 10;

inline std::map<int, int> insert_range_with_hint(int left, int right, std::map<int, int> mp, int hint_val) {
    std::map<int, int>::iterator hint_iter = mp.find(hint_val);
    if (left < right) {
        for (int i = left; i < right; ++i) {
            hint_iter = mp.insert(hint_iter, { left, left });
        }
    } else {
        for (int i = left - 1; i >= right; --i) {
            hint_iter = mp.insert(hint_iter, { left, left });
        }
    }
    return mp;
}

inline std::map<int, int> insert_range_without_hint(int left, int right, std::map<int, int> mp) {
    if (left < right) {
        for (int i = left; i < right; ++i) {
            mp.insert({ left, left });
        }
    } else {
        for (int i = left - 1; i >= right; --i) {
            mp.insert({ left, left });
        }
    }
    return mp;
}

inline double test_range_with_hint(int left, int right, std::map<int, int> mp, int hint_val) {
    double seconds = 0;
    for (int i = 0; i < REPEATS_CNT; ++i) {
        std::clock_t t_start = std::clock();
        insert_range_with_hint(left, right, mp, hint_val);
        std::clock_t t_end = std::clock();
        seconds += double((t_end - t_start)) / CLOCKS_PER_SEC;
    }
    return seconds / REPEATS_CNT;
}

inline double test_range_without_hint(int left, int right, std::map<int, int> mp) {
    double seconds = 0;
    for (int i = 0; i < REPEATS_CNT; ++i) {
        std::clock_t t_start = std::clock();
        insert_range_without_hint(left, right, mp);
        std::clock_t t_end = std::clock();
        seconds += double((t_end - t_start)) / CLOCKS_PER_SEC;
    }
    return seconds / REPEATS_CNT;
}

void test_beginning(int cur_part_size) {
    std::map<int, int> mp;
    mp = insert_range_without_hint(cur_part_size, cur_part_size * 3, mp);
    std::cout << "1-й тест:\nДобавление в начало отсортированного словаря\n";
    std::cout << "Тестирование без подсказки: " << std::fixed << std::setprecision(5) << test_range_without_hint(cur_part_size, 0, mp) << "\n";
    std::cout << "Тестирование c подсказкой:  " << std::fixed << std::setprecision(5) << test_range_with_hint(cur_part_size, 0, mp, cur_part_size) << "\n";
}

void test_middle(int cur_part_size) {
    std::map<int, int> mp;
    mp = insert_range_without_hint(0, cur_part_size, mp);
    mp = insert_range_without_hint(cur_part_size * 2, cur_part_size * 3, mp);
    std::cout << "1-й тест:\nДобавление в середину отсортированного словаря\n";
    std::cout << "Тестирование без подсказки: " << std::fixed << std::setprecision(5) << test_range_without_hint(cur_part_size, cur_part_size * 2, mp) << "\n";
    std::cout << "Тестирование c подсказкой:  " << std::fixed << std::setprecision(5) << test_range_with_hint(cur_part_size, cur_part_size * 2, mp, cur_part_size * 2) << "\n";
}

void test_end(int cur_part_size) {
    std::map<int, int> mp;
    mp = insert_range_without_hint(0, cur_part_size * 2, mp);
    std::cout << "1-й тест:\nДобавление в конец отсортированного словаря\n";
    std::cout << "Тестирование без подсказки: " << std::fixed << std::setprecision(5) << test_range_without_hint(cur_part_size * 2, cur_part_size * 3, mp) << "\n";
    std::cout << "Тестирование c подсказкой:  " << std::fixed << std::setprecision(5) << test_range_with_hint(cur_part_size * 2, cur_part_size * 3, mp, cur_part_size * 2) << "\n";
}

int main() {
    for (int cur_part_size = 1000'00; cur_part_size <= 1000'000'0; cur_part_size *= 10) {
        std::cout << "Размер блока чисел: " << cur_part_size << "\n";
        test_beginning(cur_part_size);
        test_middle(cur_part_size);
        test_end(cur_part_size);
        std::cout << "=================\n";
    }
    return 0;
}
