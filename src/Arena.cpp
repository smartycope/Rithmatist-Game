#include "Arena.hpp"

float* Arena::getLineVertices(){
    vector<float> mainVertices;

    for (auto p: players){ 
        vector<float> tmp = arena.players.front().getVertices();

            for (auto k: tmp)
                mainVertices.push_back(k);
        }
    }

    d.printVector(mainVertices, 6);

    // for(auto i: mainVertices)
    //     d.logger(std::to_string(i), 5);

    d.logger("mainVertices is has " + std::to_string(mainVertices.size()) + " items", 5);

    // auto result = mainVertices.data();
    float result[mainVertices.size()];
    std::copy(std::begin(mainVertices), std::end(mainVertices), result);
}