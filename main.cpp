#include <iostream>
#include "machine.h"
#include "poland.h"

using uint = unsigned int;

int ask_mode() {
    while (true) {
        std::cout << "What do you whant to do?\n";
        std::cout << "\t0)exit\n";
        std::cout << "\t1)regex to minimal determined\n";
        std::cout << "\t2)regex to minimal full determined\n";
//        std::cout << "\t3)undetermined to determined\n";
        std::cout << "enter number\n";
        int command = 0;
        std::cin >> command;
        switch (command) {
            case 0:
            case 1:
            case 2:
                return command;
            default:
                continue;
        }
    }
}

void regexToDetermined(const std::string &regex, const std::vector<char> &alphabet = std::vector<char>()) {
    auto machine = fromPoland(regex).determine();
    if(alphabet.empty()) {
        machine = machine.minimise();
    } else {
        machine = machine.makeFull(alphabet).minimise();
    }
    std::cout << machine;
}

int runCommand(uint command) {
    switch (command) {
        case 0:
            return 1;
        case 1: {
            std::cout << "enter regex in Polish notation\n";
            std::string regex;
            std::cin >> regex;
            regexToDetermined(regex);
            break;
        }
        case 2:
            std::cout << "enter regex in Polish notation\n";
            std::string regex;
            std::cin >> regex;
            for (char& sign:regex) {
                if (sign == '0') {
                    sign = 0;
                }
            }
            std::cout << "enter alphabet whithout whitespaces\n";
            std::string alphabets;
            std::cin >> alphabets;
            std::vector<char> alphabet(alphabets.size());
            for(int i = 0; i < alphabet.size(); ++ i) {
                alphabet[i] = alphabets[i];
            }
            regexToDetermined(regex, alphabet);
            break;
    }
    return 0;
}

int main() {
    while (true) {
        int command = ask_mode();
        if(runCommand(command) != 0) {
            break;
        }
    }
    return 0;
}
