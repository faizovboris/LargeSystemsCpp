#include <iostream>
#include <vector>


int main() {
    std::vector<bool> v(3, true);
    for (auto& x: v) {
    	x = true;
    }
    for (auto&& x: v) {
    	x = true;
    }
}
