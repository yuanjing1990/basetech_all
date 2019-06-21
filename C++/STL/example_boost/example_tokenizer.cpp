#include <boost/tokenizer.hpp>
#include <iostream>
#include <string>
using namespace std;
int main(int argc, char *argv[]) {
    // 默认的分隔
    cout << "===Default===================" << endl;
    string str("He*l,lo,W*or,*ld");
    boost::tokenizer<> tok(str);
    for (boost::tokenizer<>::iterator it = tok.begin(); it != tok.end(); ++it) {
        cout << *it << endl;
    }
    cout << "===Default===================" << endl;

    // 字符分隔
    typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
    cout << "===Char_Sp1===================" << endl;
    boost::char_separator<char> cs("*l ");
    tokenizer tok_char(str, cs);
    for (tokenizer::iterator it = tok_char.begin(); it != tok_char.end();
         ++it) {
        cout << *it << endl;
    }
    cout << "===Char_Sp1===================" << endl;
    cout << "===Char_Sp2===================" << endl;
    // boost::keep_empty_tokens
    boost::char_separator<char> cs1("* ", "l", boost::drop_empty_tokens);
    tokenizer tok_char1(str, cs1);
    for (tokenizer::iterator it = tok_char1.begin(); it != tok_char1.end();
         ++it) {
        cout << *it << endl;
    }
    cout << "===Char_Sp2===================" << endl;

    // ,分隔
    cout << "===Char_Elp1===================" << endl;
    boost::tokenizer<boost::escaped_list_separator<char>> tok_elp(str);
    for (boost::tokenizer<boost::escaped_list_separator<char>>::iterator it =
             tok_elp.begin();
         it != tok_elp.end(); ++it) {
        cout << *it << endl;
    }
    cout << "===Char_Elp1===================" << endl;
    cout << "===Char_Elp2===================" << endl;
    boost::escaped_list_separator<char> elp('\\', '*', '\"');
    boost::tokenizer<boost::escaped_list_separator<char>> tok_elp1(str, elp);
    for (boost::tokenizer<boost::escaped_list_separator<char>>::iterator it =
             tok_elp1.begin();
         it != tok_elp1.end(); ++it) {
        cout << *it << endl;
    }
    cout << "===Char_Elp2===================" << endl;

    cout << "===Offset_Sp===================" << endl;
    int offset[] = {2, 2, 3};
    boost::offset_separator osp(offset, offset + 3);
    boost::tokenizer<boost::offset_separator> tok1(str, osp);
    for (boost::tokenizer<boost::offset_separator>::iterator it = tok1.begin();
         it != tok1.end(); ++it) {
        cout << *it << endl;
    }
    cout << "===Offset_Sp===================" << endl;

    return 0;
}
