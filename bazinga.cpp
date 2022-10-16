#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

enum OperationType {
    PUSH, PLUS, PRINT
};

int* push(int x) {
    int* command = new int[2];
    command[0] = static_cast<int>(PUSH);
    command[1] = x;
    return command;
}

int* plus() {
    int* command = new int[2];
    command[0] = static_cast<int>(PLUS);
    command[1] = 0;
    return command;
}

int* print() {
    int* command = new int[2];
    command[0] = static_cast<int>(PRINT);
    command[1] = 0;
    return command;
}

std::vector<int> theQueue;
std::vector<int*> theProgram{ push(34), push(35), plus(), print() };

void simulate_language() {
    for(int* operation : theProgram) {
        if(*operation == PUSH) {
            theQueue.push_back(*(operation+1));
        } else if(*operation == PLUS) {
            auto b = theQueue.back();
            theQueue.pop_back();
            auto a = theQueue.back();
            theQueue.pop_back();
            theQueue.push_back(a + b);
        } 
        else if(*operation == PRINT) {
            auto thePop = theQueue.back();
            theQueue.pop_back();
            std::cout << thePop << std::endl;
        } else {
            std::cout << "Unknown command" << std::endl;
        }
    }
}

int main() {
    simulate_language();
    return 0;
}