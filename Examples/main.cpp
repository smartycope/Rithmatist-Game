#include "Point.hpp"
#include "Line.hpp"
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

int main(){
    Point one(45, 257);
    Point two(0, 0);
    Point three(4, 300);
    Point four(300, 300);
    Point five(485, 300);
    Point six(300, 485);

    //std::vector<Point> testVector = {one, two, three, four, five, six};
    two.print();
    std::cout << "\n";
    two.convCenter().print();
    std::cout << "\n";
    std::cout << two.getVector()[0] << ", " << two.getVector()[1] << "\n";

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