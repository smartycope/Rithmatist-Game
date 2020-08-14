// #include "Point.hpp"
// #include "Line.hpp"
// #include "Player.hpp"
// #include "Arena.hpp"
#include "Globals.hpp"
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_shape.h>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <iomanip>




/* 
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
 */

// #define appendVector(main, append) \
//     for(auto iterator = append.begin(); iterator != append.end(); ++iterator) \
//         main.push_back(*iterator);
/* 
#define appendVector(main, append) \
    for(unsigned long notI = 0; notI < append.size(); ++notI) \
        main.push_back(append[notI]);
 */


namespace g{ extern unsigned int windowWidth, windowHeight; }

int main(){
    START_CLOCK
    g::log(std::to_string(float(CLOCKS_PER_SEC)));
/* 
    std::vector<int> vector1 = { 1, 2, 3, 4, 5, 6 };
    std::vector<int> vector2 = { 7, 8, 9, 10, 11  };

    appendVector(vector1, vector2);

    printVector(vector1, -1, 2);

    std::vector<int> vector3 = { 1, 2, 3, 4, 5, 6 };
    std::vector<int> vector4 = { 7 };

    appendVector(vector3, vector4);

    printVector(vector3, -1, 2);
 */

/*
    Player player("cope");
    Arena arena(player);


    Point start1(0, 0);
    Point end1(5, 5);

    Point data1A(1, 1);
    Point data1B(2, 2);
    Point data1C(3, 3);
    Point data1D(4, 4);

    std::vector<Point> data1 = { data1A, data1B, data1C, data1D };


    Line line1(start1, end1, &data1);


    Point start2(0, 0);
    Point end2(-5, -5);

    Point data2A(-1, -1);
    Point data2B(-2, -2);
    Point data2C(-3, -3);
    Point data2D(-4, -4);

    std::vector<Point> data2 = { data2A, data2B, data2C, data2D };


    Line line2(start2, end2, &data2);


    std::vector<Point> data3 = { data1A, data2A, data1B, data2B, data1C, data2C, data1D, data2D };
    
    Line line3(start2, end1, &data3);

   
    // logVal(sizeof(data1A))
    // logVal(sizeof(Point))
    // logVal(data1.size())
    // logVal(sizeof(data1A) * data1.size())


    (*arena.players)["cope"].lines->push_back(line1);
    


    // logVal(sizeof(data1A))
    // logVal(sizeof(Point))
    // logVal(data1.size())
    // logVal(sizeof(data1A) * data1.size())

    // logVal(&data1)
    // logVal(sizeof(data1))
    // logVal(line1.lineData)
    // logVal(sizeof(*(line1.lineData)))
    // logVal((*arena.players)["cope"].lines->front().lineData)
    // logVal(sizeof(*((*arena.players)["cope"].lines->front().lineData)))
    
    
    arena.update();

    // g::printVector(*arena.vertices, 6);

    for (auto i: *(*arena.players)["cope"].lines){
        logVal(i.getDataLen());
        logVal(i.vertices->size());
    }


    (*arena.players)["cope"].lines->push_back(line2);
    (*arena.players)["cope"].lines->push_back(line3);


    arena.update();

    for (auto i: *(*arena.players)["cope"].lines){
        logVal(i.getDataLen());
        logVal(i.vertices->size());
    }
    

    // arena.players.front().lines.push_back(line2);

    // g::printVector(*arena.vertices, 6);
    

    
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

    */

    short i = 1;
    while(i > 0){
        i++;
    }
    
    LOG_CLOCK

    return 0;
}