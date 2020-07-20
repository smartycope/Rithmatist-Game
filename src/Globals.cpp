#include "Globals.hpp"

namespace g{

unsigned long debugCount = 0;

void log(std::string message, unsigned int verbosity){
    if(verbosity <= verbose)
        std::cout << ++debugCount << ": " << message << std::endl;
}

void printVector(const std::vector<float>& v, int itemsPerLine, int spacing){
    std::cout << "\n";
    int count = 1;
    for (auto i: v){
        if ((count % itemsPerLine) or itemsPerLine == -1){
            std::cout << std::setw(spacing) << i << ", ";
            ++count;
        }
        else{
            std::cout << std::setw(spacing) << i << "\n";
            ++count;
        }
    }
    std::cout << "\n";
}

void printVector(const std::vector<int>& v, int itemsPerLine, int spacing){
    std::cout << "\n";
    int count = 1;
    for (auto i: v){
        if ((count % itemsPerLine) or itemsPerLine == -1){
            std::cout << std::setw(spacing) << i << ", ";
            ++count;
        }
        else{
            std::cout << std::setw(spacing) << i << "\n";
            ++count;
        }
    }
    std::cout << "\n";
}

void printVector(const std::vector<Point>& v, int itemsPerLine, int spacing){
    std::cout << "\n";
    int count = 1;
    for (auto i: v){
        if ((count % itemsPerLine) or itemsPerLine == -1){
            std::cout << '(' << i.x << ", " << i.y << "), ";
            ++count;
        }
        else{
            std::cout << '(' << i.x << ", " << i.y << ")\n";
            ++count;
        }
    }
    std::cout << "\n";
}
} // namespace g
