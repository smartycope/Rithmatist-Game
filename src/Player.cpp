#include "Player.hpp"
#include <string>

// calculate vertices every time, instead of storing them (less efficent)
/*
    std::vector<float> Player::getVertices(){
        if (numLines != lines.size()){ // if we've added some lines since we've last checked
            std::vector<float> returnArray;
            int i = 0;

            for(auto l: lines){
            std::vector<Point> data = l.getData();
            //    data.insert(data.end(), currentLine.begin(), currentLine.end());
            appendVector(data, currentLine);
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
*/


std::vector<float> Player::update(){
    // for (auto i: lines){
        // i.lineColor = drawColor;
        // i.update();
    // }
        
    std::vector<float> updated;
    if (vertices.size() != lines.size() * 6){


        // for (auto it = lines.begin() + ((lines.size() - (vertices.size() / 6)) - 1); it != lines.end(); ++it){
        //     appendVector(vertices, it->vertices);
        //     appendVector(updated,  it->vertices);
        // }

        for(int i = vertices.size() / 6; i < lines.size(); ++i){
            // std::vector<float> tmp = lines[i].vertices;
            std::vector<float> tmp = lines[i].update(drawColor);
            appendVector(vertices, tmp);
            appendVector(updated,  tmp);
        }
    }
    return updated;
}


void Player::init() { }