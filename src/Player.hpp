#pragma once
#include "Board.hpp"

class Player{
    public:
        Player(int i) : id(i) {}
        virtual ofVec2f GetInput(ofVec2f coords,
                Board b)=0;

        virtual int GetId(){
            return id;
        }

    protected:
        const int id;
};
