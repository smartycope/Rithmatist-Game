#include "Arena.hpp"
#include "Globals.hpp"
#include <string>
// #include "Debug.hpp"

/* 
    std::vector<float> Arena::getLineVertices(){
    std::vector<float> mainVertices;

        for (auto p: players){
            std::vector<float> tmp = p.getVertices();
            mainVertices.insert(mainVertices.end(), tmp.begin(), tmp.end());


                // for (auto k: tmp)
                //     mainVertices.push_back(k);
        }

    // float* Arena::getLineVertices(){
    //     std::vector<float> mainVertices;

        // for (auto p: players){ 
    //         std::vector<float> tmp = players.front().getVertices();

    //             for (auto k: tmp)
    //                 mainVertices.push_back(k);
        // }

        // g::printVector(mainVertices, 5);

        g::log("mainVertices is has " + std::to_string(mainVertices.size()) + " items", 5);

        // auto result = mainVertices.data();
        // float result[mainVertices.size()];
        // std::copy(std::begin(mainVertices), std::end(mainVertices), result);
        return mainVertices;
    }
 */


void Arena::update(){
    // logVal(players->size())
    for (auto p: *players){
        std::vector<float>* toAdd = p.second.update();
        if (not toAdd->empty()){
            appendHeapVector(vertices, toAdd);
        }
    }
    // #define __CLASS__ file = __FILE__; file
}

/* 
std::vector<float>* Arena::getVertices(){
    std::vector<float>* sum = new std::vector<float>;
    for (auto p: *players){

    }
}
 */
Arena::~Arena() {}