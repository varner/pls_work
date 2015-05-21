#pragma once

#include "ofMain.h"
#include "Board.hpp"
#include "Player.hpp"
#include "HumanPlayer.hpp"
#include "AiPlayer.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        // ---------------------------------------
    
        void updateMouse();
        void drawMouse();
    
        bool withinBounds(int x, int y, int left, int top, unsigned int width, unsigned int height);
    
        int miceX;
        int miceY;
    
        int idealWidth = 1024;
        int idealHeight = 768;
    
        // game
        unsigned int square = 150;
        unsigned int boardMargin = 125;
        Player *current_player;
        Board * board;
        HumanPlayer human;
        AiPlayer ai;
        bool playing;
        bool pressed;
        void gameStart();
        void CheckGameOver();
        float timer;
        float delay;
    
        ofImage mosquito;
        ofImage mice;
        ofImage micePress;
        ofImage logo;
        ofImage click;
        ofImage grid;
};
