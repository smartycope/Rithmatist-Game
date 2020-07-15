#include "Player.hpp"
// #include "Debug.hpp"

vector<float> Player::getVertices(){
    vector<float> returnArray;
    int i = 0;

    for(auto l: lines){
        vector<Point> = l.getData()
        for (i = 0; i < data.size(); ++i){
            auto pointArray = data[i].getVector();
            // std::cout << pointArray[0] << ", " << pointArray[1] << "\n";
            returnArray.push_back(pointArray[0]);
            returnArray.push_back(pointArray[1]);
            returnArray.push_back(lineColor.r);
            returnArray.push_back(lineColor.g);
            returnArray.push_back(lineColor.b);
            returnArray.push_back(lineColor.a);
        }
    }    
    return returnArray;
}