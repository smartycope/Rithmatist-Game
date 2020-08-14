#pragma once

#include "Player.hpp"
#include "Globals.hpp"
#include <map>

// using std::vector;

class Arena{
private:
public:
    Color background;
    // std::vector<Player> players; // TODO: This needs to be a map, not a vector.
    std::map<std::string, Player>* players;
    std::vector<float>* vertices;

    Arena(): 
        background(0.2f, 0.2f, 0.2f, 0.7f),     // nice gray "breeze dark" background color 
        players(new std::map<std::string, Player>),
        vertices(new std::vector<float>)
        { (*players)["user"] = Player("user"); };
    Arena(Player player): 
        background(0.2f, 0.2f, 0.2f, 0.7f),     // nice gray "breeze dark" background color 
        players(new std::map<std::string, Player>),
        vertices(new std::vector<float>)
        { (*players)[player.name] = player; };
    ~Arena();

   void update();
   std::vector<float>* getVertices();
};