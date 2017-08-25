//
// Created by Jason Fu on 7/22/17.
//

#ifndef UNTITLED_DISCARDPILE_H
#define UNTITLED_DISCARDPILE_H

#include <vector>
#include "card.h"


class DiscardPile {
public:
    // constructs empty discard pile
    DiscardPile();

    // copy constructor
    DiscardPile(const DiscardPile &copy);

    // draw from discard pile
    card draw();

    // discard onto pile
    void discard(card input);

    // current size of pile
    int cardsInPile();

    // discard pile is empty
    bool isEmpty();

    // returns the card currently on top of the discard pile
    card cardOnTop();

    // returns all cards in discard pile
    std::vector<card> allCards();

private:
    std::vector<card> discards;
    int size;
};


#endif //UNTITLED_DISCARDPILE_H
