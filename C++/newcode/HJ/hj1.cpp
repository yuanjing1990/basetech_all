#include <iostream>

int main(int argc, char *argv[]) {
    char buffer[5000] = {0};
    std::cin.getline(buffer, 5000);

    std::string str(buffer);
    bool bFind = false;
    for (auto it = str.rbegin(); it != str.rend(); ++it) {
        if (*it == ' ') {
            bFind = true;
            std::cout << str.end() - it.base() << std::endl;
            break;
        }
    }
    if (!bFind) {
        std::cout << str.length() << std::endl;
    }
    return 0;
}