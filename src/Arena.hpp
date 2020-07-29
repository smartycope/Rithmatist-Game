#pragma once

#include "Line.hpp"
#include "Color.hpp"
#include "Player.hpp"
#include "Globals.hpp"

// using std::vector;

class Arena{
private:
public:
    Color background;
    std::vector<Player> players;
    std::vector<float> vertices;

    Arena(): background(0.2f, 0.2f, 0.2f, 0.7f){     // the nice gray "breeze dark" background color 
        players.push_back(Player("User"));
    };

   void update();
};