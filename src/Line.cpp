#include "Line.hpp"
#include "Globals.hpp"

#include <ctime>


void Line::draw(){
    // glDrawArrays(GL_LINES, 0, lineData.size() * 2 + 4);
}

Line Line::identifyLine(Line* line){
    Line tmp;
    return tmp;
}

int Line::getDataLen(){
    int len = lineData->size();

    // check if start/end are empty, if so, add them
    if((start.x != -1) or (start.y != -1) or isFinished){
        ++len;
        if((end.x != -1) or (end.y != -1) or isFinished)
            ++len;
    }
    return len;
}

void Line::finish(Point end){
    this->end = end;
    isFinished = true;
}

void Line::finish(Point end, const std::vector<Point>& data){
    this->end = end;
    lineData = new std::vector<Point>(data);
    isFinished = true;
}

std::vector<Point>* Line::getData(){
    std::vector<Point>* tmp = new std::vector<Point>;
    tmp = lineData;

    // check if start/end are empty, if so, add them
    if((start.x != -1) or (start.y != -1) or isFinished){
        tmp->insert(tmp->begin(), start);
        if((end.x != -1) or (end.y != -1) or isFinished)
            tmp->push_back(end);
    }
    return tmp;
}

void Line::erase(){
    start = Point();
    end = Point();
    accuracy = 0;
    unidentified = false;
    isFinished = false;
    lineData->clear();
    vertices->clear();
}

std::vector<float>* Line::update(Color playersColor){
    this->lineColor = playersColor;

    // if this is the current line, and there's points added that aren't in vertices...
    // logVal(isFinished);
    // _print(----------------------------------------------------------------------------1-) _endl
    // logVal(this->vertices->size() / 6);
    // _print((from Line)) _endl
    // logVal(this->lineData->size());
    // _print((from Line)) _endl
    
    if(!(isFinished) and (vertices->size() != (lineData->size() * 6))){
        // logVal()
        // for(int i = (vertices->size() / 6) - 1; i > lineData->size(); ++i)
            // addVertices((*lineData)[i].getVector());
            
        for(auto it = lineData->begin() + (vertices->size() / 6); it != lineData->end(); ++it){
            addVertices(it->getVector());
        }
    }
    else if (isFinished){
        addVertices(start.getVector());
        // for(int i = (vertices->size() / 6) - 1; i > lineData->size(); ++i)
            // addVertices((*lineData)[i].getVector());
        if (lineData->size()){
            for(auto it = lineData->begin() + (vertices->size() / 6); it != lineData->end(); ++it){
                addVertices(it->getVector());
            }
        }
        addVertices(end.getVector());
    }
    // logVal(vertices->size());
    return vertices; // because nothing makes sense anymore.
}

void Line::addVertices(std::pair<float, float> coord){
    //// I shouldn't have to do this (pun intended), but for some reason it won't work without it.
    vertices->push_back(coord.first);
    vertices->push_back(coord.second);
    vertices->push_back(lineColor.r);
    vertices->push_back(lineColor.g);
    vertices->push_back(lineColor.b);
    vertices->push_back(lineColor.a);
}

void Line::init() {}

Line::~Line(){
    // delete lineData;
    // delete vertices;
    // erase();
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