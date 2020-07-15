#include "Line.hpp"
#include "Debug.hpp"
Debug de;

void Line::draw(){
    // glDrawArrays(GL_LINES, 0, lineData.size() * 2 + 4);
}

// Line Line::identifyLine(Line line){
    
// }

int Line::getDataLen(){
    assert(lineData.size() % 6 == 0);
    return lineData.size / 6;
}

void Line::finish(Point end){
    this->end = end;
}

void Line::finish(Point end, const vector<Point>& data){
    this->end = end;
    lineData = data;
}

vector<Point> Line::getData(){
    // vector<Point> tmp = lineData;

    // de.printVector(lineData);
    // de.printVector(tmp);
    
    // lineData.insert(lineData.begin(), start);
    // lineData.push_back(end);
    return lineData;
}