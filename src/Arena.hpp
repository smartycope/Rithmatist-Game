#pragma once

// #include "Line.hpp"
// #include "Color.hpp"
#include "Player.hpp"
#include "Globals.cpp"

class Arena{
private:
public:
    Color background;
    std::vector<Player> players;

    // : background(0.0f, 0.0f, 1.0f, 1.0f)
    Arena(): background(0.2f, 0.2f, 0.2f, 0.7f) {
        Player defualtPlayer("User");
        players.push_back(defualtPlayer); 
    };

    vector<float> getLineVertices();
};