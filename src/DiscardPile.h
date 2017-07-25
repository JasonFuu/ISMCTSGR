//
// Created by Jason Fu on 7/22/17.
//

#ifndef UNTITLED_DISCARDPILE_H
#define UNTITLED_DISCARDPILE_H

#include <array>
#include "card.h"


class DiscardPile {
public:
    // constructs empty discard pile
    DiscardPile();

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
private:
    std::array<card, 52> discards;
    int size;
};


#endif //UNTITLED_DISCARDPILE_H
