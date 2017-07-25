//
// Created by Jason Fu on 7/22/17.
//

#ifndef UNTITLED_DECK_H
#define UNTITLED_DECK_H

#include "card.h"

class deck {
public:
    // 52 card deck constructor
    deck();

    card draw();

    void shuffle();

    int remainingCards();

    bool isEmpty();

    // for debugging purposes
    void print();

private:
    card deckarray[52];
    int size;
};


#endif //UNTITLED_DECK_H
