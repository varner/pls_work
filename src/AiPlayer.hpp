#pragma once

#include "Player.hpp"

class AiPlayer : public Player {
    public:
        AiPlayer();
        AiPlayer(int id, int o_id);
        ofVec2f GetInput(ofVec2f coords, Board b);

    protected:
        int GetScore(int winner);
        ofVec3f Max(Board b);
        ofVec3f Min(Board b);
        ofVec2f Minimax(Board b);

    private:
        int opponent_id;
};
