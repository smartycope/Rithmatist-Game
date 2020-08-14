#include "Line.hpp"
#include "Globals.hpp"

#include <cstdio>
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
    // if((start.x != -1) or (start.y != -1) or isFinished){
    //     ++len;
    //     if((end.x != -1) or (end.y != -1) or isFinished)
    //         ++len;
    // }

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
    hasUpdated = false;
    lineData->clear();
    vertices->clear();
}

std::vector<float>* Line::update(Color playersColor){
    this->lineColor = playersColor;

    int startSize = vertices->size();

    // Add start once, and at the beginning
    // if (not hasUpdated){
    //     addVertices(start.getVector());
    //     hasUpdated = true;
    // }

    if(!(isFinished) and (vertices->size() != ((lineData->size() + 1) * 6))){ // The +1 is for the start point
        // _log("---");
        for(auto it = lineData->begin() + (vertices->size() / 6); it != lineData->end(); ++it){
            addVertices(it->getVector());
        }
    }
    else if (isFinished){
        // _log("~~~");
        // addVertices(start.getVector());

        if (lineData->size()){
            for(auto it = lineData->begin() + (vertices->size() / 6); it != lineData->end(); ++it){
                addVertices(it->getVector());
            }
        }
        // addVertices(end.getVector());
    }

    // Create a new subvector of the stuff we just added
    // Cream: Just scraping the good stuff off the top
    std::vector<float>* cream = new std::vector<float>;

    // This loop was WAY harder than it should have been.
    for (int i = startSize; i < vertices->size(); ++i)
        cream->push_back((*vertices)[i]);

    return cream;
}

void Line::addVertices(std::pair<float, float> coord){
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