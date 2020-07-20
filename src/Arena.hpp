#pragma once

// #include "Line.hpp"
// #include "Color.hpp"
#include "Player.hpp"
#include "Globals.hpp"

using std::vector;

class Arena{
private:
public:
    Color background;
    std::vector<Player> players;

    // : background(0.0f, 0.0f, 1.0f, 1.0f)
    Arena(): background(0.2f, 0.2f, 0.2f, 0.7f) {
        players.push_back(Player("User"));
    };

   std::vector<float> getLineVertices();
};
