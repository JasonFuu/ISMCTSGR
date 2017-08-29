//
// Created by Jason Fu on 7/22/17.

#ifndef UNTITLED_HAND_H
#define UNTITLED_HAND_H

#include "card.h"
#include <vector>

using namespace std;

class Hand {
public:
    // constructs empty hand (to be filled)
    Hand();

    // constructs hand from std::vector of 10 cards (for monte carlo sims)
    Hand(std::vector<card> input);

    // copy constructor
    Hand(const Hand &copy);

    // adds card to hand
    void addToHand(card input);

    // removes card from hard
    bool discard(card input);

    // returns cards in hand
    std::vector<card> cardsInHand() const;

    // returns number of cards in hand
    int cardNumber() const;

private:
    std::vector<card> cards;
    int size_index;

};

std::ostream& operator<< (std::ostream &out, const card &card);


#endif //UNTITLED_HAND_H
