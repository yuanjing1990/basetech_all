#include <cmath>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
string color_str[10] = {"black", "brown", "red",    "orange", "yellow",
                        "green", "blue",  "violet", "grey",   "white"};
class ColorCode {
  public:
    ColorCode();
    long getOhms(vector<string> code);
};
ColorCode::ColorCode() {}
long ColorCode::getOhms(vector<string> code) {
    long ret = 0;
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 10; i++) {
            if (j != 2) {
                if (0 == color_str[i].compare(code[j]))
                    ret = ret * 10 + i;
            } else {
                if (0 == color_str[i].compare(code[j]))
                    ret = ret * pow(10.0f, i);
            }
        }
    return ret;
}

int main(int argc, char *argv[]) {
    ColorCode cc;
    vector<string> code;
    if (argc < 4)
        return -1;
    code.push_back(argv[1]);
    code.push_back(argv[2]);
    code.push_back(argv[3]);
    long t = cc.getOhms(code);
    cout << t << endl;
    return 0;
}