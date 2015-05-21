#include "AiPlayer.hpp"

AiPlayer::AiPlayer() : Player(2), opponent_id(1) {
}

AiPlayer::AiPlayer(int id, int o_id) : Player(id), opponent_id(o_id) {
}

/**
 * Get the compuer's input using the Minimax algorithm
 *
 * @param sf::Event event the event that the computer should handle, here it is
 * useless since the computer doesn;t use the mouse/keyboard to make a move
 * @param Board b the current board of the game
 *
 * @return std::pair<unsigned int, unsigned int> a position (row, col)
 * on the board where the computer's move should be made
 */
ofVec2f AiPlayer::GetInput(ofVec2f coords, Board b){
    return Minimax(b);
}

/**
 * Calculate the score for the winner player
 *
 * This is used in minimax
 *
 * @param int winner the player whose score should be calculated
 *
 * @return int 1 for the maximizing player (the computer),
 * -1 for the minimizing player(the opponent) or 0 for a draw
 */
int AiPlayer::GetScore(int winner){
    if(winner == id){
        // the maximizing (AiPlayer) player won
        return  1;
    }

    if(winner == opponent_id){
        // the minimizing (the opponent) player won
        return -1;
    }

    // it's a draw
    return 0;
}

/**
 * Get the best move from the maximizing player's point of view
 *
 * @param Board b the current board that is to be analysed
 *
 * @return std::pair<int, std::pair<unsigned int, unsigned int> > a pair of
 * score and the starting move that leads to that score (the move is itself a
 * pair made of the row and column of the move)
 */
ofVec3f AiPlayer::Max(Board b){
    int best_score = -1;
    int score;
    ofVec2f best_move;

    vector<ofVec2f> moves = b.GetPossibleMoves();
    vector<ofVec2f>::iterator it;

    // iterate through the child nodes
    for(it = moves.begin(); it != moves.end(); ++it){
        b.Update(id, it->x, it->y);
        int winner = b.GetWinner();

        if(winner != 0){ //the gamne is over
            score = GetScore(winner);
        }
        else{ // the game continues and it's the minimizing player's turn
            score = Min(b).x;
        }

        // undo the move so we get the same board that was passed as argument
        b.Reset(it->x, it->y);

        // if the score from the current visited children is better, we
        // update both the score and the move to get to the first child
        if(score > best_score){
            best_score = score;
            best_move = ofVec2f(it->x, it->y);
        }
    }

    // after visiting all children return the best score and the move
    // that made the score possible
    return ofVec3f(best_score, best_move.x, best_move.y);
}

/**
 * Get the best move from the minimizing player's point of view
 *
 * @param Board b the current board that is to be analysed
 *
 * @return std::pair<int, std::pair<unsigned int, unsigned int> > a pair of
 * score and the starting move that leads to that score (the move is itself a
 * pair made of the row and column of the move)
 */
ofVec3f AiPlayer::Min(Board b){
    int best_score = 1;
    int score;
    ofVec2f best_move;

    vector<ofVec2f> moves = b.GetPossibleMoves();
    vector<ofVec2f>::iterator it;

    // iterate through the child nodes
    for(it = moves.begin(); it != moves.end(); ++it){
        b.Update(opponent_id, it->x, it->y);
        int winner = b.GetWinner();

        if(winner != 0){ //the game is over
            score = GetScore(winner);
        }
        else{ // the game continues and it's the maximizing player's turn
            score = Max(b).x;
        }

        // undo the move so we get the same board that was passed as argument
        b.Reset(it->x, it->y);

        // if the score from the current visited children is better, we
        // update both the score and the move to get to the first child
        if(score < best_score){
            best_score = score;
            best_move = ofVec2f(it->x, it->y);
        }
    }

    // after visiting all children return the best score and the move
    // that made the score possible
    return ofVec3f(best_score, best_move.x, best_move.y);
}

/**
 * Start the minimax algorithm from the maximizing (the computer) player's point
 * of view
 *
 * We are starting from the computer's point of view because the algorithm is
 * used when is computer's turn to move
 *
 * @param Board b the current board that should be analysed
 *
 * @return std::pair<unsigned int, unsigned int> the computer chosen move
 * composed of the row and the column
 */
ofVec2f AiPlayer::Minimax(Board b){
    ofVec3f maxed = Max(b);
    return ofVec2f(maxed.y, maxed.z);
}
