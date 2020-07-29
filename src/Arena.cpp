#include "Arena.hpp"
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
    for (auto p: players){
        std::vector<float> toAdd = p.update();
        if (not toAdd.empty())
            appendVector(vertices, toAdd)
    }
}