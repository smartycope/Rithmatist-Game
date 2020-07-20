#include "Arena.hpp"
// #include "Debug.hpp"

vector<float> Arena::getLineVertices(){
    vector<float> mainVertices;

    for (auto p: players){
        vector<float> tmp = p.getVertices();

            for (auto k: tmp)
                mainVertices.push_back(k);
    }

    d.printVector(mainVertices, 5);

    // for(auto i: mainVertices)
    //     d.logger(std::to_string(i), 5);

    d.logger("mainVertices is has " + std::to_string(mainVertices.size()) + " items", 5);

    // auto result = mainVertices.data();
    // float result[mainVertices.size()];
    // std::copy(std::begin(mainVertices), std::end(mainVertices), result);
    return mainVertices;
}