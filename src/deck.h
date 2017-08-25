//
// Created by Jason Fu on 7/22/17.
//

#ifndef UNTITLED_DECK_H
#define UNTITLED_DECK_H

#include "card.h"
#include <vector>

using namespace std;

class deck {
public:
    // 52 card deck constructor
    deck();

    // construct deck from vector of cards
    deck(std::vector<card> cards);

    // copy constructor
    deck(const deck &copy);

    card draw();

    void shuffle();

    int remainingCards();

    bool isEmpty();

    // for debugging purposes
    void print();

    std::vector<card> allCards();

private:
    std::vector<card> deckarray;
    int size;
};


#endif //UNTITLED_DECK_H
