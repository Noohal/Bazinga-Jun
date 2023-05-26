#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

/**
 * @brief All of the operations enumerated.
 */
enum OperationType {
    PUSH, PLUS, PRINT
};

/**
 * @brief Checks a string character by character
 *        to see if it is an integer.
 * 
 * @param str   The string to be tested
 * @return True/False if the string is a number
 */
bool is_number(const std::string &str) {
    for(const char &c : str) {
        if(std::isdigit(c) == 0) return false;
    }
    return true;
}

/**
 * @brief Creates an operation for pushing a value
 * 
 * @param x Value to be pushed
 * @return int* An array containing the OperationType and the value.
 */
int* push(int x) {
    int* command = new int[2];
    command[0] = static_cast<int>(PUSH);
    command[1] = x;
    return command;
}

/**
 * @brief Creates an operation for adding two values
 * 
 * @return int* An array containing the OperationType and an empty value.
 */
int* plus() {
    int* command = new int[2];
    command[0] = static_cast<int>(PLUS);
    command[1] = 0;
    return command;
}

/**
 * @brief Creates an operation for printing a value
 * 
 * @return int* An array containing the OperationType and an empty value.
 */
int* print() {
    int* command = new int[2];
    command[0] = static_cast<int>(PRINT);
    command[1] = 0;
    return command;
}

std::vector<int> theQueue; // A Vector holding the values on the stack.
std::vector<int*> theProgram; // A Vector holding the list of instructions

/**
 * @brief Add instructions to the program vector by parsing tokens.
 * 
 * @param aFile the file containing the instructions
 */
void create_program_from_file(std::ifstream &aFile) {
    std::string theLine;
    while(std::getline(aFile, theLine)) {
        std::string theWord;
        std::istringstream ss(theLine);
        while(ss >> theWord) {
            if(is_number(theWord)) {
                int wordAsNum = std::stoi(theWord);
                theProgram.push_back(push(wordAsNum));
            } else if(theWord == "plus") {
                theProgram.push_back(plus());
            } else if(theWord == "bazinga") {
                theProgram.push_back(print());
            } else {
                std::cout << "Unknown word: " << theWord << std::endl;
            }
        }
    }
}

/**
 * @brief Take each instruction from the program vector and run them accordingly.
 * 
 */
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
        } else if(*operation == PRINT) {
            auto thePop = theQueue.back();
            theQueue.pop_back();
            std::cout << thePop << std::endl;
        } else {
            std::cout << "Unknown command" << std::endl;
        }
    }
}

int main() {
    std::ifstream theFile("tests/math.baz");
    create_program_from_file(theFile);
    simulate_language();
    theFile.close();
    return 0;
}