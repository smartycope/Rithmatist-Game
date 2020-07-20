#include "Arena.hpp"
// #include "Debug.hpp"

std::vector<float> Arena::getLineVertices(){
  std::vector<float> mainVertices;

    for (auto p: players){
      std::vector<float> tmp = p.getVertices();

            for (auto k: tmp)
                mainVertices.push_back(k);
    }

    g::printVector(mainVertices, 5);

    // for(auto i: mainVertices)
    //     g::logger(std::to_string(i), 5);

    g::log("mainVertices is has " + std::to_string(mainVertices.size()) + " items", 5);

    // auto result = mainVertices.data();
    // float result[mainVertices.size()];
    // std::copy(std::begin(mainVertices), std::end(mainVertices), result);
    return mainVertices;
}
