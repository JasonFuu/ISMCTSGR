//
// Created by Jason Fu on 8/17/17.
//

#include "GRGameState.h"
#include "deck.h"
#include "Move.h"
#include "meld.h"
#include <assert.h>

GRGameState::GRGameState() {
    deck current_deck{};
    Hand player_one{};
    Hand player_two{};
    DiscardPile discards{};
    hands.reserve(2);
    hands[0] = player_one;
    hands[1] = player_two;
    card_drawn = false;
    player_to_move = 0;
    score = 0;
    deal();
}

GRGameState::GRGameState(const GRGameState &determinize, int observer) {
    assert(observer == 0 || observer == 1);
    hands.reserve(2);

    hands[observer] = determinize.hands[observer];
    DiscardPile discards(*determinize.discards);

    int opponent;
    if (observer == 0) opponent = 1;
    else opponent = 0;

    std::vector<card> deck_copy = determinize.current_deck->allCards();
    std::vector<card> opponent_hand_copy = determinize.hands[opponent].cardsInHand();
    deck_copy.insert(deck_copy.end(), opponent_hand_copy.begin(), opponent_hand_copy.end());

    // unseenCards has contents of deck and opponents hand
    std::vector<card> unseenCards = deck_copy;

    // shuffle unseenCards

    // seeding
    srand (time(0));

    for (int k = 0; k < unseenCards.size(); k++)
    {
        // Pick a random index from 0 to i
        int i = rand() % 52;
        int j = rand() % 52;

        // Swap arr[i] with the element at random index
        card temp = unseenCards[i];
        unseenCards[i] = unseenCards[j];
        unseenCards[j] = temp;
    }

    deck current_deck(unseenCards);
    Hand player_two{};

    for (int i = 0; i < 10; i++) {
        player_two.addToHand(current_deck.draw());
    }
    hands[opponent] = player_two;
    card_drawn = determinize.card_drawn;
    player_to_move = determinize.player_to_move;
}


// shuffles deck and deals initial hand
void GRGameState::deal() {
    current_deck->shuffle();

    for (int i = 0; i < 10; i++) {
        player_one->addToHand(current_deck->draw());
        player_two->addToHand(current_deck->draw());
    }
    discards->discard(current_deck->draw());
    card_drawn = false;
}

// gets moves from 1 of 3 possible states (before draw, after draw, after discard)
// depending on which state we are currently in
std::vector<Move> GRGameState::getMoves() {
    std::vector<Move> moves;
    moves.reserve(2);

    // card has not been drawn yet
    if (!card_drawn) {
        card_drawn = true;
        Move deck_draw(static_cast<TYPE >(1));
        moves.push_back(deck_draw);

        if (discards->cardsInPile() > 0) {
            Move discard_draw(static_cast<TYPE >(2));
            moves.push_back(discard_draw);
        }

        return moves;
    }

    // card has been drawn but not discarded
    if (hands[player_to_move].cardNumber() == 11) {
        std::vector<card> hand = hands[player_to_move].cardsInHand();
        for (int i = 0; i < hand.size(); i++) {
            Move next(static_cast<TYPE >(0), hand[i]);
            moves.push_back(next);
        }

        return moves;
    }

    // card has been discarded - can we knock now?
    if (hands[player_to_move].cardNumber() == 10) {
        Move knock(static_cast<TYPE>(3));
        Move no_knock(static_cast<TYPE>(4));
        moves.push_back(knock);
        moves.push_back(no_knock);
        return moves;
    }
}

void GRGameState::doMove(Move &move) {
    switch (move.type) {
        case CARD:
            discardMove(move.stored_card);
            break;
        case DECK_DRAW:
            deckDrawMove();
            break;
        case DISCARD_DRAW:
            discardPileDrawMove();
            break;
        case KNOCK:
            knockMove();
            break;
        case NOKNOCK:
            noKnockMove();
            break;
    }
}

void GRGameState::deckDrawMove() {
    card drawn = current_deck->draw();
    hands[player_to_move].addToHand(drawn);
}

void GRGameState::discardPileDrawMove() {
    card drawn = discards->draw();
    hands[player_to_move].addToHand(drawn);
}

void GRGameState::discardMove(card &input) {
    discards->discard(input);
    player_to_move = getOtherPlayer(player_to_move);
}

void GRGameState::knockMove() {
    std::vector<card> knocker_hand = hands[player_to_move].cardsInHand();
    std::vector<card> other_hand = hands[getOtherPlayer(player_to_move)].cardsInHand();
    meld knocker(knocker_hand);
    meld other(other_hand);
    int knocker_deadwood = knocker.deadwoodValue();
    int other_deadwood = other.deadwoodValue();
    int ginConstant;

    // going GIN; no chance to play off melds
    if (knocker_deadwood == 0) {
        if (knocker_hand.size() == 11) ginConstant = 31;
        else ginConstant = 25;

        score = ginConstant + other_deadwood;
    }

        // no GIN, see which melds non-knocker can play off of and see if an undercut occurred
    else {
        std::vector<int> toBeRemoved(10);
        std::vector<card> other_non_meld = other.nonMeldCards();
        // can be played off numbers meld if card has value equal to any members
        for (int i = 0; i < other_non_meld.size(); i++) {
            for (card member : other.numbersMeldCards()) {
                if (member.getValue() == other_non_meld[i].getValue()) toBeRemoved.push_back(i);
            }
        }

        // recalc deadwood and remove cards that can be played off
        for (int i : toBeRemoved) {
            other_deadwood -= other_non_meld[i].getDeadwood();
            other_non_meld[i] = other_non_meld.back();
            other_non_meld.pop_back();
        }

        toBeRemoved.clear();
        toBeRemoved.reserve(10);

        for (int i = 0; i < other_non_meld.size(); i++) {
            for (card member : other.SFMeldCards()) {
                // if card has same suit and consecutive value of any member cards, it can be played off the meld
                if ((member.getValue() - 1 == other_non_meld[i].getValue() || member.getValue() + 1 == other_non_meld[i].getValue())
                    && member.getSuit() == other_non_meld[i].getSuit())
                    toBeRemoved.push_back(i);
            }
        }

        // recalc deadwood and remove cards that can be played off
        for (int i : toBeRemoved) {
            other_deadwood -= other_non_meld[i].getDeadwood();
            other_non_meld[i] = other_non_meld.back();
            other_non_meld.pop_back();
        }

        // if undercut occurred
        if (other_deadwood < knocker_deadwood) {
            score = -25 + (knocker_deadwood - other_deadwood);
        }

        else score = knocker_deadwood - other_deadwood;
    }
}

void GRGameState::noKnockMove() {
    player_to_move = getOtherPlayer(player_to_move);
}

int GRGameState::getResult() {
    return score;
}

// helper method that returns other player
int getOtherPlayer(int player) {
    if (player == 0) return 1;
    return 0;
}
