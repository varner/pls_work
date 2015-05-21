#include "HumanPlayer.hpp"

HumanPlayer::HumanPlayer() : Player(1) {

}

HumanPlayer::HumanPlayer(int id) : Player(id) {
}

/**
 * Get input from the user using the mouse
 *
 * @param sf::Event event the event that is checked for the user's click
 * @param Board b the current board of the game
 *
 * @return std::pair<unsigned int, unsigned int> a position (row, col)
 * on the board if the user clicked, else some default position (0, 0)
 */
ofVec2f HumanPlayer::GetInput(ofVec2f coords,
        Board b){
    return b.CoordToPos(coords.x, coords.y);
}
