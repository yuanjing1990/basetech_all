#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
    int n = 0;
    std::cin >> n;

    std::vector<std::string> str_vec;
    for (size_t i = 0; i < n; i++) {
        std::string tmp;
        std::cin >> tmp;
        str_vec.push_back(tmp);
    }

    try {
        for (int i = 0; i < n; i++) {
            std::string &tmp = str_vec[i];
            for (int j = 2; j < tmp.length(); ) {
                if (tmp.at(j - 1) == tmp.at(j - 2) && tmp.at(j) == tmp.at(j - 1)) {
                    tmp.erase(j, 1);
                }
                if (j - 3 >= 0 && tmp.at(j - 3) == tmp.at(j - 2) && tmp.at(j - 1) == tmp.at(j)) {
                    tmp.erase(j, 1);
                }
            }
            std::cout << tmp << std::endl;
        }
    }catch(std::exception e) {
        std::cout << e.what() << std::endl;
    }
}