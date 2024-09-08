#include <iostream>       // std::cout
#include <string>         // std::string
#include <queue>          // std::queue
#include <unordered_set>  // std::unordered_set
#include <stack>          // std::stack
#include <fstream>        // std::fstream


#ifndef HTMLCHECKER_H
#define HTMLCHECKER_H

using namespace std;

enum State {whitespace, word, tag, tag_attr};

class HTMLChecker {
public:
    HTMLChecker();
    bool load(const string &file_path);
    bool isValid();

private:

    queue<string> html_elements;
    unordered_set<string> self_closing_tags;

};


#endif //HTMLCHECKER_H