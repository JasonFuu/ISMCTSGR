//
// Created by Jason Fu on 8/17/17.
//

#ifndef UNTITLED_GRGAMESTATE_H
#define UNTITLED_GRGAMESTATE_H
#include "meld.h"
#include "card.h"
#include "deck.h"
#include "DiscardPile.h"
#include "hand.h"
#include "Move.h"
#include <vector>

class GRGameState {
public:
    // init game state
    GRGameState();

    // creates determinized clone of the game state
    GRGameState(const GRGameState &determinize, int observer);

    // deals hands to players and starts the initial game state
    void deal();

    /* 3 "classes" of moves:
     *  draw (from deck or discard)
     *  discard (1 of 11 cards from hand)
     *  knock (if 10 or fewer deadwood)
     *  */

    std::vector<Move> getMoves();

    void doMove(Move &move);




private:
    std::vector<Hand> hands;
    Hand *player_one;
    Hand *player_two;
    DiscardPile *discards;
    deck *current_deck;
    int player_to_move;
    int score;

    // has a card been drawn in this round yet (used to differentiate between states)
    bool card_drawn;

    void deckDrawMove();

    void discardPileDrawMove();

    void discardMove(card &toDiscard);

    void knockMove();

    void noKnockMove();

    int getResult();
};

int getOtherPlayer(int player);

#endif //UNTITLED_GRGAMESTATE_H
