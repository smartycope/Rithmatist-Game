#include "Line.hpp"


void Line::draw(){
    // glDrawArrays(GL_LINES, 0, lineData.size() * 2 + 4);
}

Line Line::identifyLine(Line* line){
    Line tmp;
    return tmp;
}

int Line::getDataLen(){
    // g::printVector(lineData, 6);
    // assert(lineData.size() % 6 == 0);
    // return lineData.size() / 6;
    return lineData.size();
    // return lineData.size() * 6;
}

void Line::finish(Point end){
    this->end = end;
}

void Line::finish(Point end, const std::vector<Point>& data){
    this->end = end;
    lineData = data;
}

std::vector<Point> Line::getData(){
    //std::vector<Point> tmp = lineData;
    
    // tmp.insert(lineData.begin(), start)lineData;
    // lineData.push_back(end);
    return lineData;
}

void Line::erase(){
    start = Point();
    end = Point();
    accuracy = 0;
    unidentified = false;
    isFinished = false;
    lineData.clear();
    vertices.clear();
}

std::vector<float> Line::update(Color playersColor){
    this->lineColor = playersColor;
    // if (/* !isFinished and  */(vertices.size() != (lineData.size() * 6))){ // if we've added some lines since we've last checked
        // assert(dataLen < lineData.size());

        for(int i = vertices.size() / 6; i < lineData.size(); ++i){
            std::pair<float, float> coord = lineData[i].getVector();
            // I shouldn't have to do this (pun intended), but for some reason it won't work without it.
            this->vertices.push_back(coord.first);
            this->vertices.push_back(coord.second);
            this->vertices.push_back(lineColor.r);
            this->vertices.push_back(lineColor.g);
            this->vertices.push_back(lineColor.b);
            this->vertices.push_back(lineColor.a);
        }
    // }

    return this->vertices; // because nothing makes sense anymore.
}



/* 
std::vector<float> Player::update(){
    if (needsUpdate()){ // if we've added some lines since we've last checked
        g::log("Player is updating their lines");
        assert(numLines < lines.size());

        for(auto it = lines.begin() + numLines; it != lines.end(); ++it){
            std::vector<Point> data = it->getData();
            //    data.insert(data.end(), currentLine.begin(), currentLine.end());
            std::vector<Point> tmp = currentLine.getData();
            appendVector(data, tmp);
            
            for (int i = 0; i < data.size(); ++i){
                std::array<float, 2> pointArray = data[i].getVector();
                // std::cout << pointArray[0] << ", " << pointArray[1] << "\n";
                vertices.push_back(pointArray[0]);
                vertices.push_back(pointArray[1]);
                vertices.push_back(lineColor.r);
                vertices.push_back(lineColor.g);
                vertices.push_back(lineColor.b);
                vertices.push_back(lineColor.a);
            }
        }
    }
    // return what you just added, so we can add it to Arena's buffer vector as well
    std::vector<float> tmp2;
    tmp2.insert(tmp2.begin(), vertices.begin() + ((lines.size() - numLines) * 6), vertices.end());
    numLines = lines.size();
    // g::printVector(tmp2, 6);
    g::log("added " + std::to_string((lines.size() - numLines) * 6) + " points to the buffer vector", 4);
    logVal(lines.size());
    logVal(vertices.size());
    logVal(numLines);
    
    return tmp2;
}
 */