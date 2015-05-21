#pragma once
#include "Player.hpp"

class HumanPlayer : public Player {
    public:
        HumanPlayer();
        HumanPlayer(int id);
        ofVec2f GetInput(ofVec2f coords, Board b);
};