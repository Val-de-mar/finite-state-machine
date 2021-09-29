#include <iostream>
#include "machine.h"
#include "poland.h"

using uint = unsigned int;

int ask_mode() {
    while (true) {
        std::cout << "What do you whant to do?\n";
        std::cout << "\t0)exit 1)regex to determined\n";
//        std::cout <<"\t2)undetermined to determined\n";
        std::cout << "enter number\n";
        int command = 0;
        std::cin >> command;
        switch (command) {
            case 0:
            case 1:
//            case 2:
                return command;
            default:
                continue;
        }
    }
}

void regexToDetermined() {
    std::string regex;
    std::cin >> regex;
    auto machine = fromPoland(regex).determine().minimise();
    std::cout << machine;
}

int runCommand(uint command) {
    switch (command) {
        case 0:
            return 1;
        case 1:
            std::cout << "enter regex in Polish notation\n";
            regexToDetermined();
            break;
//        case 2:

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
