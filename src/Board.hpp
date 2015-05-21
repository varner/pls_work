#pragma once
#include "ofMain.h"

class Board{
    public:
        Board();
        Board(unsigned int w, unsigned int h, int e=0);
        bool Update(int id, unsigned int row, unsigned int col);
        int GetWinner();
        void Reset();
        bool Reset(unsigned int row, unsigned int col);
        vector<ofVec2f> GetPossibleMoves();
        ofVec2f CoordToPos(unsigned int x,
                unsigned int y) const;

        unsigned int GetWidth(){
            return width;
        }

        unsigned int GetHeight(){
            return height;
        }
    
        void DrawBoard(int top, int left, int square);

    protected:
        bool IsValidRowCol(unsigned int row, unsigned int col);
        bool IsValidMove(unsigned int row, unsigned int col);

    private:
        unsigned int width, height;
        int empty;
        vector< vector <int> > board;
        ofImage aiMarker;
        ofImage humanMarker;
};
