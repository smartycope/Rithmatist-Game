#include "Line.hpp"


void Line::draw(){
    // glDrawArrays(GL_LINES, 0, lineData.size() * 2 + 4);
}

// Line Line::identifyLine(Line line){
    
// }

int Line::getDataLen(){
    assert(lineData.size() % 6 == 0);
    return lineData.size() / 6;
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

    // g::printVector(lineData);
    // g::printVector(tmp);
    
    // lineData.insert(lineData.begin(), start);
    // lineData.push_back(end);
    return lineData;
}