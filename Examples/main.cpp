// #include "Point.hpp"
// #include "Line.hpp"
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <iomanip>

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


#define appendVector(main, append)                                        \
    switch(append.size()){                                                \
        case 0:                                                           \
            break;                                                        \
        case 1:                                                           \
            main.push_back(append[0]); break;                             \
        default:                                                          \
            main.insert(main.end(), append.begin(), append.end()); break; \
    }

#define logVal(var) std::cout << g::getDebugCount() << ": " << #var << " = " << var << std::endl;

// #define appendVector(main, append) \
//     for(auto iterator = append.begin(); iterator != append.end(); ++iterator) \
//         main.push_back(*iterator);
/* 
#define appendVector(main, append) \
    for(unsigned long notI = 0; notI < append.size(); ++notI) \
        main.push_back(append[notI]);
 */
int main(){

    std::vector<int> vector1 = { 1, 2, 3, 4, 5, 6 };
    std::vector<int> vector2 = { 7, 8, 9, 10, 11  };

    appendVector(vector1, vector2);

    printVector(vector1, -1, 2);

    std::vector<int> vector3 = { 1, 2, 3, 4, 5, 6 };
    std::vector<int> vector4 = { 7 };

    appendVector(vector3, vector4);

    printVector(vector3, -1, 2);

    

    
    // Point one(45, 257);
    // Point two(0, 0);
    // Point three(4, 300);
    // Point four(300, 300);
    // Point five(485, 300);
    // Point six(300, 485);

    // std::vector<Point> testVector = {one, two, three, four, five, six};
    // two.print();
    // std::cout << "\n";
    // two.convCenter().print();
    // std::cout << "\n";
    // std::cout << two.getVector()[0] << ", " << two.getVector()[1] << "\n";

    // one.convCenter().print();

    // Line l;
    // auto v = l.vertex(testVector);
    // for(auto i: v)
    //     std::cout << i << ' ';
    // float endArray[v.size()];
    // std::copy(std::begin(v), std::end(v), endArray);

    // for (int i = 0; i < v.size(); i += 2)
    //     std::cout << endArray[i] << ", " << endArray[i + 1] << std::endl;

    return 0;
}