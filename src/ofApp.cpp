#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // mouse shit
    ofSetFrameRate(0);
    ofSetVerticalSync(true);
    ofHideCursor();
    pressed = false;
    
    board = new Board();
    
    // load all the fucking images
    logo.loadImage("logo.png");
    mice.loadImage("mouse.png");
    micePress.loadImage("mouse-press.png");
    mosquito.loadImage("mosquito.png");
    click.loadImage("click.png");
    grid.loadImage("grid.png");
    gameStart();
}

//--------------------------------------------------------------
void ofApp::update(){
    updateMouse();
    CheckGameOver();
    if ( (ofGetElapsedTimef() - timer > delay) && (current_player == &ai)) {
         printf("time: %f | current: %f\n", timer, ofGetElapsedTimef());
        ofVec2f position = ai.GetInput(ofVec2f(0,0), *board);
        board->Update(ai.GetId(), position.x, position.y);
        current_player = &human;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    logo.draw(idealWidth - logo.width - 150, idealHeight - logo.height - 150);
    board->DrawBoard(boardMargin, boardMargin, square);
    grid.draw(boardMargin, boardMargin);
    if (!playing) {
        click.draw(boardMargin, boardMargin);
    }
    
    mosquito.draw(400, 400);
    
    drawMouse();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    pressed = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    pressed = false;
    if (withinBounds(x, y, boardMargin, boardMargin, square * 3, square * 3)) {
        if (playing && (current_player == &human)) {
            ofVec2f position = human.GetInput(ofVec2f(x - boardMargin, y - boardMargin), *board);
            if (board->Update(human.GetId(), position.x, position.y)) {
                current_player = &ai;
                timer = ofGetElapsedTimef();
                delay = ofRandom(0.5, 1.0);
            };
        } else if (!playing) {
            gameStart();
            printf("bleeee\n");
        }
    }
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::updateMouse() {
    if (mouseX < 0) {
        miceX = 0;
    } else if (mouseX > idealWidth - mice.width) {
        miceX = idealWidth - mice.width;
    } else {
        miceX = mouseX;
    }
    
    if (mouseY < 0) {
        miceY = 0;
    } else if (mouseY > idealHeight - mice.height) {
        miceY = idealHeight - mice.height;
    } else {
        miceY = mouseY;
    }
}

void ofApp::drawMouse() {
    if (pressed) {
        micePress.draw(miceX, miceY);
    } else {
        mice.draw(miceX, miceY);
    }
}

bool ofApp::withinBounds(int x, int y, int left, int top, unsigned int width, unsigned int height) {
    if ( (x < left) || (y < top) || (x > left + width) || (y > top + height)) {
        return false;
    } else {
        return true;
    }
}

void ofApp::gameStart() {
    board->Reset();
    timer = ofGetElapsedTimef();
    delay = ofRandom(0.5, 1.0);
    
    if (ofRandom(100) < 50) {
        current_player = &human;
    } else {
        current_player = &ai;
    }
    
    playing = true;
    
}

void ofApp::CheckGameOver() {
    if(!playing){
        return;
    }
    
    int winner_id = board->GetWinner();
   
    if (winner_id == ai.GetId()) {
        printf("u won!!!! Press r to play again!");
        playing = false;
    } else if (winner_id == ai.GetId()) {
        printf("the computer won!!!! Press r to play again!");
        playing = false;
    } else if (winner_id == -1) {
        printf("draw!!!!\n");
        playing = false;
    }
    
}