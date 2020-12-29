#include <algorithm>
#include <iostream>

struct equal_to_ignorecase : public std::equal_to<char> {
    bool operator()(const char &__x, const char &__y) const {
        return std::tolower(__x) == std::tolower(__y);
    }
};

int main(int argc, char *argv[]) {
    char buffer[5000] = {0};
    std::cin.getline(buffer, 5000);

    char c;
    std::cin >> c;

    std::string str(buffer);
    std::cout << std::count_if(str.begin(), str.end(), std::bind1st(equal_to_ignorecase(), c)) << std::endl;
    return 0;
}